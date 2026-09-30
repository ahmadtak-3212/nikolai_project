#include <TFT_eSPI.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define PWM_OUT_PIN 12
#define TEMP_IN_PIN 32
#define CURR_IN_PIN 33
#define PWM_FREQ 10000
#define PWM_CHANNEL 0
#define PWM_RES 8
#define ORDER 66
#define XTMIN 500 //touch
#define XTMAX 3500
#define YTMIN 500
#define YTMAX 3500

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
#define BUTTON_PIN 22

int SLIDERRADIUS = 10;

int power_prev_ys = 0;

int BOOT = 0;
int MAINMENU = 1;
int POWER = 2;
int SETTINGS = 3;
int SYNC = 4;
int LOGIN = 5;

int screen_state = BOOT;

char screen_state_name[20] = "mainmenu";

int battery = 100; //update this to reflect the real battery

int maxcurrent = 0; int CURRENTLIMIT = 9999; int CURRENTSTEP = 10;
int maxtemperature = 0; int TEMPERATURELIMIT = 9999; int TEMPERATURESTEP = 10;

///////////////////////////////////////////////////////////////////////////////////////////////
//WIFI Functions
///////////////////////////////////////////////////////////////////////////////////////////////
char network[] = "MIT GUEST";
char password[] = "";
uint8_t channel = 1; //network channel on 2.4 GHz
byte bssid[] = {0x04, 0x95, 0xE6, 0xAE, 0xDB, 0x41}; //6 byte MAC address of AP you're targeting.
#define RESPONSE_TIMEOUT 6000 //ms to wait for response from host
#define POSTING_PERIOD  30000 //ms to wait between posting step
const uint16_t IN_BUFFER_SIZE = 1000; //size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 1000; //size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE]; //char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE]; //char array buffer to hold HTTP response
uint32_t posting_timer;

void wifi_setup() {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.printf("%d: %s, Ch:%d (%ddBm) %s ", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "open" : "");
      uint8_t* cc = WiFi.BSSID(i);
      for (int k = 0; k < 6; k++) {
        Serial.print(*cc, HEX);
        if (k != 5) Serial.print(":");
        cc++;
      }
      Serial.println("");
    }
  }
  delay(100); //wait a bit (100 ms)

  //if using regular connection use line below:
  WiFi.begin(network, password);
  //if using channel/mac specification for crowded bands use the following:
  //WiFi.begin(network, password, channel, bssid);


  uint8_t count = 0; //count used for Wifi check times
  Serial.print("Attempting to connect to ");
  Serial.println(network);
  while (WiFi.status() != WL_CONNECTED && count < 12) {
    delay(500);
    Serial.print(".");
    count++;
  }
  delay(2000);
  if (WiFi.isConnected()) { //if we connected then print our IP, Mac, and SSID we're on
    Serial.println("CONNECTED!");
    Serial.println(WiFi.localIP().toString() + " (" + WiFi.macAddress() + ") (" + WiFi.SSID() + ")");
    delay(500);
  } else { //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Going to restart");
    Serial.println(WiFi.status());
    ESP.restart(); // restart the ESP (proper way)
  }

}
void post_data(float temperature, float current) {
  if (millis() - posting_timer > POSTING_PERIOD) {
    posting_timer = millis();
    request_buffer[0] = '\0';
    char body[100]; //for body
    sprintf(body, "temperature=%2f&current=%2f", temperature, current); //generate body, posting temp, humidity to server
    int body_len = strlen(body); //calculate body length (for header reporting)
    sprintf(request_buffer, "POST http://608dev-2.net/sandbox/sc/team73/Server/server.py  HTTP/1.1\r\n");
    strcat(request_buffer, "Host: 608dev-2.net\r\n");
    strcat(request_buffer, "Content-Type: application/x-www-form-urlencoded\r\n");
    sprintf(request_buffer + strlen(request_buffer), "Content-Length: %d\r\n", body_len); //append string formatted to end of request buffer
    strcat(request_buffer, "\r\n"); //new line from header to body
    strcat(request_buffer, body); //body
    strcat(request_buffer, "\r\n"); //new line
    Serial.println("");
    Serial.println(request_buffer);
    do_http_request("608dev-2.net", request_buffer, response_buffer, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT, false);
    Serial.println(response_buffer); //viewable in Serial Terminal
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


TFT_eSPI tft = TFT_eSPI();
OneWire oneWire(TEMP_IN_PIN);
DallasTemperature sensors(&oneWire);

uint16_t x, y;
int z;
int xs, ys, zs;

float percentage = -1.0;
int lasttime = 0;
int timetrack = 0;

int input;
int index0 = 0;
float values[101];
int power;

///////////////////////////////////////////////////////////////////////////////////////////////
//Button Class
///////////////////////////////////////////////////////////////////////////////////////////////
enum button_state {S0, S1, S2, S3, S4};
class Button {
  public:
    uint32_t S2_start_time;
    uint32_t button_change_time;
    uint32_t debounce_duration;
    uint32_t long_press_duration;
    uint8_t pin;
    uint8_t flag;
    uint8_t button_pressed;
    button_state state; // This is public for the sake of convenience
    Button(int p) {
      flag = 0;
      state = S0;
      pin = p;
      S2_start_time = millis(); //init
      button_change_time = millis(); //init
      debounce_duration = 10;
      long_press_duration = 1000;
      button_pressed = 0;
    }
    void read() {
      uint8_t button_val = digitalRead(pin);
      button_pressed = !button_val; //invert button
    }
    int update() {
      read();
      if (state == S0) {
        flag = 0;
        if (button_pressed) {
          state = S1;
          button_change_time = millis();
        }
      } else if (state == S1) {
        if (button_pressed && millis() - button_change_time >= debounce_duration) {
          state = S2;

          S2_start_time = millis();
        } else if (!button_pressed) {
          state = S0;
          button_change_time = millis();
        }
      } else if (state == S2) {
        if (button_pressed && millis() - S2_start_time >= long_press_duration) {
          //flag = 2;
          state = S3;
        } else if (!button_pressed) {
          state = S4;
          button_change_time = millis();
        }
      } else if (state == S3) {
        if (!button_pressed) {
          state = S4;
          button_change_time = millis();
        }
      } else if (state == S4) {
        if (!button_pressed && millis() - button_change_time >= debounce_duration) {
          if ( millis() - S2_start_time >= long_press_duration) {

            flag = 2;
          } else if ( millis() - S2_start_time < long_press_duration) {
            flag = 1;
          }
          state = S0;
        } else if (button_pressed && millis() - S2_start_time < long_press_duration) {
          state = S2;
          button_change_time = millis();
        } else if (button_pressed && millis() - S2_start_time >= long_press_duration) {
          state = S3;
          button_change_time = millis();
        }
      }
      return flag;
    }
};

float getTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(1);
}

float getCurrent() {
  float in = analogRead(CURR_IN_PIN) / 4095.0;
  float current = map(in, 0.0, 1.0, -2.8, 27.7);
  float avg_current = averaging_filter(current, values, 5, &index0);
  return avg_current;
}
enum states {OFF, ON};
states state;
Button on_off = Button(BUTTON_PIN);
void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  state = OFF;

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
  wifi_setup();
  posting_timer = millis();
  Serial.println("WIFI SETUP DONE");
}

void init_power(){
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(115, YBOXMIN, 10, YBOXMAX - YBOXMIN, TFT_WHITE);
  tft.fillRect(220,300,20,20,TFT_GOLD); //to MainMenu
}

void power_update_display() {
  //lasttime = millis();
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  Serial.printf("%d, %d, %d ", xs, ys, z);
  if (z > ZTHRESHOLD) {
    tft.drawCircle(xs,ys,1,TFT_ORANGE);
    if (XBOXMIN < xs && xs < XBOXMAX && YBOXMIN < ys && ys < YBOXMAX) {
      //tft.fillScreen(TFT_BLACK);
      //tft.fillRect(100, 30, 40, ys - 30, TFT_RED);
      if(power_prev_ys > ys){
        tft.fillRect(105, ys, 30, power_prev_ys - ys + 10, TFT_BLACK);
        tft.fillRect(115, ys, 10, min(power_prev_ys + 10, YBOXMAX)-ys, TFT_WHITE);
        tft.fillCircle(120, ys, 10, TFT_RED);
      }
      else{
        tft.fillRect(105, power_prev_ys - 10, 30, ys - power_prev_ys + 10, TFT_BLACK);
        tft.fillRect(115, max(power_prev_ys - 10, YBOXMIN), 10, ys - max(power_prev_ys - 10, YBOXMIN), TFT_RED);
        tft.fillCircle(120, ys, 10, TFT_RED);
      }
      power_prev_ys = ys;
      power = map((float) ys, (float) YBOXMIN, (float) YBOXMAX, 0.0, 255.0);
      tft.setRotation(1); //not default
      tft.setCursor(0, 0);
      tft.printf("x:%i\ny:%i\nz:%i\nxs:%i\nys:%i", x, y, z, xs, ys);
      tft.setRotation(2); //default
    }
    else if(220 < xs && 300 < ys){
      //to mainmenu
      screen_state = MAINMENU;
      init_mainmenu();
    }
  }
  //while (millis() - lasttime < TIMEDELAY);
}

void init_mainmenu(){
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(120, 100, 30, TFT_BLUE); tft.setCursor(110,100); tft.print("Power");
  tft.fillCircle(120,220,30,TFT_GREEN); tft.setCursor(100,220); tft.print("Settings");
  tft.fillRect(220, 0, 20, 20, TFT_GOLD);
}

void mainmenu_update_display(){
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  Serial.printf("%d, %d, %d ", xs, ys, z);
  if (z > ZTHRESHOLD) {
    tft.drawCircle(xs,ys,1,TFT_ORANGE);
    if(90 < xs && xs < 150 && 70 < ys && ys < 130){
      //to Power
      screen_state = POWER;
      init_power();
    }
    else if (90 < xs && xs < 150 && 190 < ys && ys < 250){
      //to Settings
      screen_state = SETTINGS;
      init_settings();
    }
    else if (220 < xs && ys < 20){
      // to Sync
      screen_state = SYNC;
      init_sync();
    }
  }
}

void init_settings(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(100,80); tft.print("Max Current");
  tft.fillRect(40,90,40,40,TFT_RED); tft.setCursor(60,110); tft.print("-");
  tft.drawRect(80,90,80,40,TFT_GREEN); tft.setCursor(110,110); tft.printf("%04d",maxcurrent);
  tft.fillRect(160,90,40,40,TFT_BLUE); tft.setCursor(180,110); tft.print("+");

  tft.fillRect(40,190,40,40,TFT_RED); tft.setCursor(60,210); tft.print("-");
  tft.drawRect(80,190,80,40,TFT_GREEN); tft.setCursor(110,210); tft.printf("%04d",maxtemperature);
  tft.fillRect(160,190,40,40,TFT_BLUE); tft.setCursor(180,210); tft.print("+");
  tft.setCursor(100,240); tft.print("Max Temperature");

  tft.fillRect(220,300,20,20,TFT_GOLD);
}

void settings_update_display(){
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  Serial.printf("%d, %d, %d ", xs, ys, z);
  if (z > ZTHRESHOLD) {
    tft.drawCircle(xs,ys,1,TFT_ORANGE);
    if(40 < xs && xs < 80 && 90 < ys && ys < 130){
      //decrease maxcurrent
      maxcurrent -= CURRENTSTEP;
      if(maxcurrent < 0){ maxcurrent = 0;}
      tft.setCursor(110,110); tft.printf("%04d",maxcurrent);
    }
    else if (160 < xs && xs < 200 && 90 < ys && ys < 130){
      //increase maxcurrent
      maxcurrent += CURRENTSTEP;
      if(maxcurrent > CURRENTLIMIT){maxcurrent = CURRENTLIMIT;}
      tft.setCursor(110,110); tft.printf("%04d",maxcurrent);
    }
    else if (40 < xs && xs < 80 && 190 < ys && ys < 230){
      //decrease maxtemperature
      maxtemperature -= TEMPERATURESTEP;
      if (maxtemperature < 0){maxtemperature = 0;}
      tft.setCursor(110,210); tft.printf("%04d",maxtemperature);
    }
    else if (160 < xs && xs < 200 && 190 < ys && ys < 230){
      //increase maxtemperature
      maxtemperature += TEMPERATURESTEP;
      if (maxtemperature > TEMPERATURELIMIT){maxtemperature = TEMPERATURELIMIT;}
      tft.setCursor(110,210); tft.printf("%04d", maxtemperature);
    }
    else if(220 < xs && 300 < ys){
      //go to mainmenu
      screen_state = MAINMENU;
      init_mainmenu();
    }
  }
}

void init_sync(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(100,150); tft.print("SYNC coming soon");
  tft.fillRect(220,300,20,20,TFT_GOLD); //to MainMenu
}
void sync_update_display(){
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  Serial.printf("%d, %d, %d ", xs, ys, z);
  if (z > ZTHRESHOLD) {
    tft.drawCircle(xs,ys,1,TFT_ORANGE);
    if(220 < xs && 300 < ys){
      //to mainmenu
      screen_state = MAINMENU;
      init_mainmenu();
    }
  }
}
void init_login(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(100,150); tft.print("LOGIN coming soon");
  tft.fillRect(220,300,20,20,TFT_GOLD); //to MainMenu
}
void login_update_display(){
  tft.getTouchRaw(&x, &y);
  z = tft.getTouchRawZ();
  rawToScale(&x, &y, &xs, &ys);
  Serial.printf("%d, %d, %d ", xs, ys, z);
  if (z > ZTHRESHOLD) {
    tft.drawCircle(xs,ys,1,TFT_ORANGE);
    if(220 < xs && 300 < ys){
      //to mainmenu
      screen_state = MAINMENU;
      init_mainmenu();
    }
  }
}

void update_screen_name(){
  if(screen_state == BOOT){
    strcpy(screen_state_name, "BOOT");
  }
  else if (screen_state == MAINMENU){
    strcpy(screen_state_name, "MAINMENU");
  }
  else if (screen_state == POWER){
    strcpy(screen_state_name, "POWER");
  }
  else if (screen_state == SETTINGS){
    strcpy(screen_state_name, "SETTINGS");
  }
  else if (screen_state == SYNC){
    strcpy(screen_state_name, "SYNC");
  }
  else if (screen_state == LOGIN){
    strcpy(screen_state_name, "LOGIN");
  }
}


void loop() {
  lasttime = millis();
  timetrack = millis();
  float current = getCurrent(); int ct = millis() - timetrack; timetrack = millis();
  float temperature = getTemperature(); int tt = millis() - timetrack; timetrack = millis();
  int flag = on_off.update(); int ft = millis() - timetrack; timetrack = millis();
  Serial.printf("Current: %2f, Temperature: %2f, Power: %d, State: %d ", current, temperature, power, state);
  if (state == ON) {
    ledcWrite(PWM_CHANNEL, power);
    if (flag != 0) {
      state = OFF;
    }
  } else if (state == OFF) {
    ledcWrite(PWM_CHANNEL, 0);
    if (flag != 0) {
      state = ON;
    }
  }
  int lt = millis() - timetrack; timetrack = millis();

  if(screen_state == BOOT){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(110,150); tft.print("NIKOLAI BOOT SCREEN"); delay(1000);
    screen_state = MAINMENU;
    init_mainmenu();
  }
  else if (screen_state == MAINMENU){
    mainmenu_update_display();
  }
  else if (screen_state == POWER){
    power_update_display();
  }
  else if (screen_state == SETTINGS){
    settings_update_display();
  }
  else if (screen_state == SYNC){
    sync_update_display();
  }
  else if (screen_state == LOGIN){
    login_update_display();
  }
  else{
    //what????? how is this possible?
    //just set screen_state to something
    screen_state = BOOT;
  }
  int st = millis() - timetrack; timetrack = millis();

  //post_data(temperature, current);
  
  update_screen_name(); int ut = millis() - timetrack; timetrack = millis();
  Serial.printf("c%d,t%d,f%d,l%d,s%d,u%d\n",ct,tt,ft,lt,st,ut);
  tft.setCursor(0,0); tft.printf("screen: %s\nuser: %s\nbatt: %03d\npower: %03d\ncurrent: %04d\nmaxcurrent: %04d\ntemperature: %04d\nmaxtemperature: %04d",
    screen_state_name, "testuser", battery, power, current, maxcurrent, temperature, maxtemperature);
  while(millis() - lasttime < TIMEDELAY);
}
