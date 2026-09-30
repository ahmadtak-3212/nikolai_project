/*
MAIN HEADER FILE


*/
#include <Arduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <WiFi.h>
#include <stdlib.h>

/*
*   Global Pin Defintions
*/
#define ILI9431_BRIGHTNESS_PIN 16
#define TEMP_IN_PIN 32
#define CURR_IN_PIN 33
#define COIL_OUT_PIN 12
#define BATT_IN_PIN 14

#define MAX_TEMPERATURE 36
#define MAX_CURRENT 3

//PWM
#define GLOBAL_PWM_FREQ 10000
#define GLOBAL_PWM_RES 8
//Brightness
#define ILI9431_BRIGHTNESS_PWM_CHANNEL 0
#define COIL_OUT_PWM_CHANNEL 1

#define E_PERIOD 20000
#define PRODUCER_PERIOD 20

TaskHandle_t Consumer;
TaskHandle_t Producer;
// QueueHandle_t curr_queue;
// QueueHandle_t temp_queue;
// QueueHandle_t batt_queue;

OneWire oneWire(TEMP_IN_PIN); 
DallasTemperature sensors(&oneWire);


//Saftey States
enum safety_states {INIT, OPERATIONAL, E_STOP, };

