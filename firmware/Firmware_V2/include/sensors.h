// ------------------------------------------------
// Init Sensors
// ------------------------------------------------
void initCurr(int curr_pin, int curr_read_res = 12){
    pinMode(curr_pin, INPUT);
    analogReadResolution(curr_read_res);
}
void initBatt(int batt_pin, int batt_read_res =12){
    pinMode(batt_pin, INPUT);
    analogReadResolution(batt_read_res);
}
void initTemp(){
    sensors.begin();
} 

// ------------------------------------------------
// Get Sensor Data
// ------------------------------------------------

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getCurrent(){
    float in = analogRead(CURR_IN_PIN)/4095.0;  
    float current = map(in, 0.0, 1.0, -2.8, 27.7);
    current = current + 1.3; // current offset
    return current;
} 
float getBattery(){
    float in = analogRead(BATT_IN_PIN)/4095.0;  
    float battery = map(in, 0.0, 1.0, 0, 2.25);
    return battery;
}
float getTemperature(){
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    //Serial.printf("\nTrue Temp: %2f", temp);
    if(temp == (float) -127.0){
        temp = 0.0;
    }
    return temp;
}
