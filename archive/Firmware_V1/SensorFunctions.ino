
const uint8_t ANALOG_PINS_RESOLUTION = 12; // TODO chnage this?
const uint16_t CUR1_PIN = 99; // TODO Figure out what this actually maps to in the breadboard.
const uint16_t TEMP1_PIN = 100;

#define NUM_COILS 1
float curr[NUM_COILS];
float temp[NUM_COILS];
void read_curr_temp_into_buffers() {
    curr[0] = analogRead(CUR1_PIN);
    temp[0] = digitalRead(TEMP1_PIN);
}

float* average_curr;
float* average_temp;
const float ALPHA = 0.7;
// Design Decision: We take an average that forgets data over time because it's more accurate to what we want.
// TODO: Find a nice alpha.
void update_average_curr_temp(float alpha) {
    for(int i = 0; i < NUM_COILS; i++) {
        average_curr[i] = average_curr [i] * (1 - alpha) + curr[i] * alpha;
        average_temp[i] = average_temp [i] * (1 - alpha) + temp[i] * alpha;
    }
}

uint8_t safety_state;
const uint8_t GOOD = 0;
const uint8_t BAD = 1;

const float MAX_TEMP = 1000; // TODO Units and values.
const float MAX_CURR = 1000;
void safety_fsm() {   
    switch(safety_state) { 
        case GOOD:
        // If any coil is above max threshold, BAD and break.
        for(int i = 0; i < NUM_COILS; i++) {
            if (curr[i] > MAX_CURR || temp[i] > MAX_TEMP) {
                safety_state = BAD;
                // shutdownMethodHere();
                break;
            }
        }
        break;
        case BAD:
        bool back_to_good = true;
        // If any is still above threshold, stay.
        for(int i = 0; i < NUM_COILS; i++) {
            if (curr[i] > MAX_CURR || temp[i] > MAX_TEMP) {
                back_to_good = false;
                break;
            }
        }

        // Otherwise, safe to keep going.
        if (back_to_good) {
            safety_state = GOOD;
            // TODO safe to keep going method here;
        }
        break;
    }
}

int timer;
void sensor_setup() {

    timer = millis();
}

const int LOOP_PERIOD = 5000; // in ms
void sensor_loop() {
    read_curr_temp_into_buffers();
    safety_fsm();
    update_average_curr_temp(ALPHA);

    while (millis() - timer < LOOP_PERIOD);
    timer = millis();
}
