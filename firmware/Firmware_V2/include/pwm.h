
// ------------------------------------------------
// PWM Initialization
// ------------------------------------------------
void initPWM(int pin, int channel, int write = 0, int freq=10000, int res=8 ){
    pinMode(pin, OUTPUT);
    ledcSetup(channel, freq, res);
    ledcAttachPin(pin, channel);
    ledcWrite(channel, write);
} 
// ------------------------------------------------
// PWM Writes
// ------------------------------------------------
void writePWM(int channel, int value){
    ledcWrite(channel, value);
}