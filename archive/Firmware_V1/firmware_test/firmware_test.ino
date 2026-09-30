#include <TFT_eSPI.h>
#include <WiFi.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define PWM_OUT_PIN 12
#define TEMP_IN_PIN 32
#define CURR_IN_PIN 33
#define BUTTON_PIN 22
#define PWM_FREQ 10000
#define PWM_CHANNEL 0
#define PWM_RES 8
#define ORDER 66
#define XTMIN 500 //touch
#define XTMAX 3500
#define YTMIN 500
#define YTMAX 3500
#define E_PERIOD 20000
#define XMIN 0
#define XMAX 240
#define YMIN 0
#define YMAX 320

#define XBOXMIN 100
#define XBOXMAX 140
#define YBOXMIN 30
#define YBOXMAX 290
#define TIMEDELAY 200
#define ZTHRESHOLD 100 //try to use a stylus

OneWire oneWire(TEMP_IN_PIN); 
DallasTemperature sensors(&oneWire);

enum safety_states {INIT, OPERATIONAL, E_STOP, };
safety_states safety_state;



float MAX_TEMP = 32; // *C
float MAX_CURR = 2;  // Amps


int power = 0;
int index1;
float values[101];

char network[] = "StataCenter";
char password[] = "";

uint32_t posting_timer;
uint32_t e_timer;

TFT_eSPI tft = TFT_eSPI();

uint16_t x, y;
int z;
int xs, ys, zs;

float percentage = -1.0;
int lasttime = 0;

float getCurrent(){
  float in = analogRead(CURR_IN_PIN)/4095.0;
  float current = map(in, 0.0, 1.0, -2.8, 27.7);
  float avg_current = averaging_filter(current, values, 5, &index1);
  return avg_current;
} 

float getTemperature(){
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void safety_fsm(float current, float temperature, int *power) {   
    switch(safety_state) { 
        case INIT:
        *power = 0;
        if (current < MAX_CURR && temperature < MAX_TEMP) {
            safety_state = OPERATIONAL;
        }
        break;
        case OPERATIONAL:
        if (current > MAX_CURR || temperature > MAX_TEMP) {
            safety_state = E_STOP;
            e_timer = millis();
            *power = 0;
        }
        break;
        case E_STOP: 
        *power = 0;
        if (current < MAX_CURR && temperature < MAX_TEMP  && (millis() - e_timer > E_PERIOD)  ) {
            safety_state = OPERATIONAL;
            e_timer = millis(); 
        }
        
        break;
    
    }
}

void setup() {
  safety_state = INIT;
  Serial.begin(115200);
  
  Serial.println("Starting...");
  delay(200);
  power = 0;
  pinMode(PWM_OUT_PIN, OUTPUT);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_OUT_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, 0);
  Serial.println("PWM SETUP DONE");

  
  
  delay(200);
  sensors.begin(); 
  Serial.println("TEMPERATURE SETUP DONE");
  
  delay(200);
  pinMode(CURR_IN_PIN, INPUT);
  analogReadResolution(12);
  Serial.println("CURRENT SETUP DONE");

  delay(200);
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  Serial.println("TFT SETUP DONE");

  delay(200);
  //wifi_setup(network, password);
  posting_timer = millis();
  Serial.println("WIFI SETUP DONE");
}

void update_display(){
  lasttime = millis();
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  if (z > ZTHRESHOLD) {
    if (XBOXMIN < xs && xs < XBOXMAX && YBOXMIN < ys && ys < YBOXMAX) {
      tft.fillScreen(TFT_BLACK);
      tft.fillRect(100, 30, 40, ys - 30, TFT_RED);
      power = map((float) ys,(float) YBOXMIN, (float) YBOXMAX, 0.0, 255.0);
      tft.setCursor(0, 0);
      tft.printf("x:%i\ny:%i\nz:%i\nxs:%i\nys:%i", x, y, z, xs, ys);
    }
  }
  while (millis() - lasttime < TIMEDELAY);
}

void loop() {
  float current = getCurrent();
  float temperature = getTemperature();
  safety_fsm(current, temperature, &power);
  update_display();
  Serial.printf("\nCurrent: %2f, Temperature: %2f, Power: %d", current, temperature, power);
  ledcWrite(PWM_CHANNEL, power);
  post_data(temperature, current);
  
}
