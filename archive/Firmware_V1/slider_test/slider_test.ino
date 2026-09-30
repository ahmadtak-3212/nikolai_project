#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
uint16_t x,y; //we cannot use int for this. only uint16_t is accepted by tft.getTouchRaw(&x,&y).
int z; //on the other hand, int is fine for z. tft.getTouchRawZ() returns int

int xs,ys,zs;
int prev_ys;
int current_prev_ys;
int temperature_prev_ys;

int XTMIN = 500; //touch, can be further calibrated
int XTMAX = 3500;
int YTMIN = 500;
int YTMAX = 3500;

int XMIN = 0;
int XMAX = 240;
int YMIN = 0;
int YMAX = 320;

int ZTHRESHOLD = 100; //try to use a stylus, otherwise measured pressure is indistinguishable from ambient

//float percentage = -1.0;

int XBOXMIN = 100;
int XBOXMAX = 140;
int YBOXMIN = 30;
int YBOXMAX = 290;

int xshift = 40;

int lasttime = 0;
int TIMEDELAY = 100;

int scaledSliderValue = 0; //this value will contain the scaled output of the slider on a scale from 0 to 255
int SSVMAX = 255;

int current;
int temperature;
float power; //scalar from 0 to 1
int maxcurrent;
int maxtemperature;

int CURRENT_PIN = 1; //make sure these are analog pins
int TEMPERATURE_PIN = 2;
int POWER_PIN = 0;

int SLIDER_MODE = 0;
int MAIN_MENU = 1;
int state;

int XTOGGLEMIN = 20;
int XTOGGLEMAX = 60;
int YTOGGLEMIN = 260;
int YTOGGLEMAX = 300;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting...");
  tft.init();
  
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(100,30,40,260,TFT_RED);
  tft.fillRect(20,260,40,40,TFT_GREEN);
  tft.setCursor(100,300);
  tft.print("Power");


  prev_ys = YBOXMIN;
  current_prev_ys = YBOXMIN;
  temperature_prev_ys = YBOXMIN;
  maxcurrent = 260;
  maxtemperature = 260;
  ledcSetup(0,100,10);
  ledcAttachPin(POWER_PIN, 0);

  state = SLIDER_MODE;

}

void loop() {
  // put your main code here, to run repeatedly:

  lasttime = millis();
  
  /*
  tft.getTouchRaw(&x, &y);
  
  Serial.printf("x: %i     ", x);

  Serial.printf("y: %i     ", y);

  Serial.printf("z: %i \n", tft.getTouchRawZ());

  tft.fillScreen(TFT_BLACK);

  tft.setCursor(0,0);

  tft.printf("x: %i\ny: %i\nz: %i", x,y,tft.getTouchRawZ());

  delay(250);
  */

  tft.getTouchRaw(&x, &y);

  z = tft.getTouchRawZ();

  

  rawToScale(&x,&y,&xs,&ys);

  if(z > ZTHRESHOLD){

    if(state == SLIDER_MODE){
      if(XBOXMIN < xs && xs < XBOXMAX && YBOXMIN < ys && ys < YBOXMAX){
        updateScaledSliderValue(&ys,&scaledSliderValue);
        if(ys > prev_ys){
          tft.fillRect(100,prev_ys,40,ys-prev_ys,TFT_RED);
        }
        else if(ys < prev_ys){
          tft.fillRect(100,ys,40,prev_ys-ys,TFT_BLACK);
        }
        
        
        prev_ys = ys;

        power = (scaledSliderValue+0.0)/SSVMAX;
        ledcWrite(0, (int) (power*1023));
      }
      else if(XTOGGLEMIN < xs && xs < XTOGGLEMAX & YTOGGLEMIN < ys && ys < YTOGGLEMAX){
        //tft.fillRect(100,30,40,290,TFT_BLACK);
        tft.fillScreen(TFT_BLACK);
        tft.fillRect(XTOGGLEMIN, YTOGGLEMIN, 40, 40, TFT_GREEN);
        tft.drawRect(100-xshift,30,40,260,TFT_RED);
        tft.drawRect(100+xshift,30,40,260,TFT_RED);
        tft.setCursor(100-xshift,300); tft.print("Current");
        tft.setCursor(100+xshift,300); tft.print("Temperature");
        prev_ys = YBOXMIN;
        state = MAIN_MENU;
      }
    }
    else if(state == MAIN_MENU){
      if(XBOXMIN - xshift < xs && xs < XBOXMAX - xshift && YBOXMIN < ys && ys < YBOXMAX){
        //current slider
        if(ys > current_prev_ys){
          tft.fillRect(100-xshift,current_prev_ys,40,ys-current_prev_ys,TFT_RED);
        }
        else if(ys < current_prev_ys){
          tft.fillRect(100-xshift,ys,40,current_prev_ys-ys,TFT_BLACK);
        }
        
        
        current_prev_ys = ys;

        maxcurrent = ys - YBOXMIN; //should scale this
      }
      else if(XBOXMIN + xshift < xs && xs < XBOXMAX + xshift && YBOXMIN < ys && ys < YBOXMAX){
        //temperature slider
        if(ys > temperature_prev_ys){
          tft.fillRect(100+xshift,temperature_prev_ys,40,ys-temperature_prev_ys,TFT_RED);
        }
        else if(ys < temperature_prev_ys){
          tft.fillRect(100+xshift,ys,40,temperature_prev_ys-ys,TFT_BLACK);
        }
        
        
        temperature_prev_ys = ys;

        maxtemperature = ys - YBOXMIN; //should scale this
      }
      else if(XTOGGLEMIN < xs && xs < XTOGGLEMAX & YTOGGLEMIN < ys && ys < YTOGGLEMAX){
        //tft.fillRect(100-xshift,30,40,290,TFT_BLACK);
        //tft.fillRect(100+xshift,30,40,290,TFT_BLACK);
        tft.fillScreen(TFT_BLACK);
        tft.fillRect(XTOGGLEMIN,YTOGGLEMIN,40,40,TFT_GREEN);
        tft.drawRect(100,30,40,260,TFT_RED);
        tft.setCursor(100,300); tft.print("Power");
        //prev_ys = YBOXMIN;
        current_prev_ys = YBOXMIN;
        temperature_prev_ys = YBOXMIN;
        state = SLIDER_MODE;
      }
    }
    tft.setCursor(0,0);
    tft.printf("x:%04d\ny:%04d\nz:%04d\nxs:%03d\nys:%03d\nssv:%03d",x,y,z,xs,ys,scaledSliderValue);
  }

  tft.drawCircle(xs,ys,5,TFT_BLUE);
  current = analogRead(CURRENT_PIN);
  temperature = analogRead(TEMPERATURE_PIN);
  tft.setCursor(160,0);
  tft.printf("curr:%04d", current);
  tft.setCursor(160,10);
  tft.printf("maxcurr:%04d", maxcurrent);
  tft.setCursor(160,20);
  tft.printf("temp:%04d", temperature);
  tft.setCursor(160,30);
  tft.printf("maxtemp:%04d",maxtemperature);


  while(millis() < lasttime + TIMEDELAY);

}

void rawToScale(uint16_t* x, uint16_t* y, int* xs, int* ys){
  if(*x < XTMIN){
    *xs = XMAX; //x is reversed!
  }
  else if (*x > XTMAX){
    *xs = XMIN;
  }
  else{
    *xs = ((XMIN-XMAX)*(*x) + XMAX*XTMAX - XMIN*XTMIN)/(XTMAX-XTMIN);
  }

  if(*y < YTMIN){
    *ys = YMIN;
  }
  else if (*y > YTMAX){
    *ys = YMAX;
  }
  else{
    *ys = ((YMAX-YMIN)*(*y) + YMIN*YTMAX - YMAX*YTMIN)/(YTMAX-YTMIN);
  }

  
  
}

void updateScaledSliderValue(int* ys,int* ssv){
  if(YBOXMIN < *ys && *ys < YBOXMAX){
    *ssv = ((*ys-YBOXMIN)*SSVMAX)/(YBOXMAX-YBOXMIN);
  }
}


