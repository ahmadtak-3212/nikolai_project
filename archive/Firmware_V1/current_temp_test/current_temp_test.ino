#include <OneWire.h> 
#include <SPI.h>
#include <DallasTemperature.h>

#define PWM_OUT_PIN 12
#define TEMP_IN_PIN 32
#define CURR_IN_PIN 33
#define PWM_FREQ 10000
#define ORDER 50

OneWire oneWire(TEMP_IN_PIN); 
DallasTemperature sensors(&oneWire);

int input;
int index1 = 0;
float values1[101];


float averaging_filter(float input, float* stored_values, int order, int* index) {
    //your code here
    float sum = 0;
    *(stored_values + *index) = input;

    for (int i = 0; i < order + 1; i++){
      sum += *(stored_values + i);
    }
    *index = (*index + 1) % (order + 1);
  return (sum)/(order + 1);
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);           // Set up serial port
  input = 128;
  //delay(100);
  pinMode(PWM_OUT_PIN, OUTPUT);
  pinMode(CURR_IN_PIN, INPUT);
  ledcSetup(0, PWM_FREQ, 8);
  ledcAttachPin(PWM_OUT_PIN, 0);
  ledcWrite(0, 128);
  sensors.begin(); 
  analogReadResolution(12);
}
void loop(){
  //TODO fix linear scalling

  sensors.requestTemperatures();
  float in = analogRead(CURR_IN_PIN)/4095.0;
  float current = map(in, 0.0, 1.0, -2.8, 27.7);
  float avg_current = averaging_filter(current, values1, 50, &index1);
  Serial.printf("\nCurrent: %2f, Temprature: %2f", avg_current, sensors.getTempCByIndex(0));
  //delay(1);
}
