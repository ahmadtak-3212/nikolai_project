//<App !Start!>
// FILE: [guislice.ino]
// Created by GUIslice Builder version: [0.17.b11]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "guislice_GSLC.h"
#include "main.h"
#include "pwm.h"
#include "sensors.h"
#include "iot_server.h"
// ------------------------------------------------
// Program Globals
// ------------------------------------------------
float current  = 0.0;
float temperature =0.0;
float battery = 0.0;
float max_curr = 6.0;
float max_temp = 60.0;
uint8_t power = 0;
uint32_t e_timer = 0;
uint32_t producer_timer = 0;
uint32_t read_timer = 0;

safety_states safety_state = INIT;
// char username[MAX_STR] = "AHMAD";
// char univ_password[MAX_STR] = "123";
// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemBatteryStatus0= NULL;
gslc_tsElemRef* m_pElemCurrentStatus0= NULL;
gslc_tsElemRef* m_pElemCurrentStatus1= NULL;
gslc_tsElemRef* m_pElemPowerStatus0= NULL;
gslc_tsElemRef* m_pElemProgressBattery= NULL;
gslc_tsElemRef* m_pElemSeekbarPower0= NULL;
gslc_tsElemRef* m_pElemSelectUser = NULL;
gslc_tsElemRef* m_pElemTempratureStatus0= NULL;
gslc_tsElemRef* m_pElemTempratureStatus1= NULL;
gslc_tsElemRef* m_pElemToggleImgWIFI= NULL;
gslc_tsElemRef* m_pElemValMaxCurrent= NULL;
gslc_tsElemRef* m_pElemValMaxTemprature= NULL;
gslc_tsElemRef* m_pElemXRingGaugeCurrent0= NULL;
gslc_tsElemRef* m_pElemXRingGaugeCurrent1= NULL;
gslc_tsElemRef* m_pElemXRingGaugeTemprature0= NULL;
gslc_tsElemRef* m_pElemXRingGaugeTemprature1= NULL;
gslc_tsElemRef* m_pElemKeyPadNum  = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  char maxTemp[MAX_STR];
  char maxCurr[MAX_STR];
  char *currUser;
  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_IMAGEBTN_WIFI:
        break;
      case E_ELEM_IMAGEBTN_SYNC:
        currUser = gslc_ElemGetTxtStr(&m_gui, m_pElemSelectUser);
        get_user_data(currUser, &max_curr, &max_temp);
        snprintf(maxTemp,MAX_STR, "%2.1f", max_temp);
        snprintf(maxCurr,MAX_STR, "%2.1f", max_curr);
        gslc_ElemSetTxtStr(&m_gui, m_pElemValMaxTemprature, maxTemp);
        gslc_ElemSetTxtStr(&m_gui, m_pElemValMaxCurrent, maxCurr);
        break;
      case E_ELEM_BTN_POWER:
        gslc_SetPageCur(&m_gui, E_PG_POWER);
        break;
      case E_ELEM_BTN_SETTINGS:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        break;
      case E_ELEM_BTN_BACK:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BTN_BACK_2:
        //post data to server let it act as submit
        // gslc_ElemXKeyPadValGet(&m_gui, m_pElemValMaxCurrent, maxCurr, MAX_STR);
        // gslc_ElemXKeyPadValGet(&m_gui, m_pElemValMaxTemprature, maxTemp, MAX_STR);
        snprintf(maxCurr, MAX_STR, "%s", gslc_ElemGetTxtStr(&m_gui, m_pElemValMaxCurrent));
        snprintf(maxTemp, MAX_STR, "%s", gslc_ElemGetTxtStr(&m_gui, m_pElemValMaxTemprature));
        //snprintf(username, MAX_STR, "%s", currUser); 
        currUser = gslc_ElemGetTxtStr(&m_gui, m_pElemSelectUser);
        max_curr = atof(maxCurr);
        max_temp = atof(maxTemp);
        post_user_data(currUser,univ_password, max_curr, max_temp); //assume passord is "123" for all users 
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_NUMINPUT_MC:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValMaxCurrent);
        break;
      case E_ELEM_NUMINPUT_MT:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemValMaxTemprature);
        break;
      case E_ELEM_SELECT_USER:
        gslc_SetPageCur(&m_gui, E_PG_USER_SELECT);
        break;
      case E_ELEM_SELECT_AHMAD:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        gslc_ElemSetTxtStr(&m_gui, m_pElemSelectUser, "AHMAD"); 
        snprintf(username, MAX_STR, "%s", "AHMAD"); 
        break;
      case E_ELEM_SELECT_JAMES:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        gslc_ElemSetTxtStr(&m_gui, m_pElemSelectUser, "JAMES");  
        snprintf(username, MAX_STR, "%s", "JAMES"); 
        break;
      case E_ELEM_SELECT_COLIN:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        gslc_ElemSetTxtStr(&m_gui, m_pElemSelectUser, "COLIN");  
        snprintf(username, MAX_STR, "%s", "COLIN"); 
        break;
      case E_ELEM_SELECT_SEBASTAIN:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        gslc_ElemSetTxtStr(&m_gui, m_pElemSelectUser, "SEBASTAIN");  
        snprintf(username, MAX_STR, "%s", "SEBASTAIN"); 
        break;
      case E_ELEM_SELECT_DEVAN:
        gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
        gslc_ElemSetTxtStr(&m_gui, m_pElemSelectUser, "DEVAN");  
        snprintf(username, MAX_STR, "%s", "DEVAN"); 
        break;

//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
//<Keypad Enums !Start!>
      case E_ELEM_NUMINPUT_MC:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValMaxCurrent, pvData);
	    gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_NUMINPUT_MT:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemValMaxTemprature, pvData);
	    gslc_PopupHide(&m_gui);
        break;

//<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;
  char acText[MAX_STR];

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_ELEM_SEEKBAR_COIL_POWER:
      // Fetch the slider position
      nVal = gslc_ElemXSeekbarGetPos(pGui,m_pElemSeekbarPower0);
      power = nVal;
      snprintf(acText, MAX_STR, "%d", nVal); 
      gslc_ElemSetTxtStr(&m_gui, m_pElemPowerStatus0, acText);  
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>
// ------------------------------------------------
// Update Status Inidcators
// ------------------------------------------------
void safety_Update(float current, float temperature, uint8_t *power, int max_curr, int max_temo) {   
    switch(safety_state) { 
        case INIT:
        *power = 0;
        if (current < max_curr && temperature < max_temo) {
            safety_state = OPERATIONAL;
        }
        break;
        case OPERATIONAL:
        if (current > max_curr || temperature > max_temo) {
            safety_state = E_STOP;
            e_timer = millis();
            *power = 0;
        }
        break;
        case E_STOP: 
        *power = 0;
        if (current < max_curr && temperature < max_temo  && (millis() - e_timer > E_PERIOD)  ) {
            safety_state = OPERATIONAL;
            e_timer = millis(); 
        }
        
        break;
    
    }
}

// ------------------------------------------------
// Update Status Inidcators
// ------------------------------------------------
void stat_Update(float battery, float temperature, float current){
    //Serial.printf("\nCurrent: %.2f, Temprature: %.2f, Battery: %.2f", current, temperature, battery);
    char currText[MAX_STR];
    char tempText[MAX_STR];
    char battText[MAX_STR];
    snprintf(currText, MAX_STR, "%.2f", current);
    snprintf(tempText, MAX_STR, "%.2f", temperature);
    snprintf(battText, MAX_STR, "%.2f", battery);
    gslc_ElemSetTxtStr(&m_gui, m_pElemCurrentStatus0, currText);
    gslc_ElemSetTxtStr(&m_gui, m_pElemCurrentStatus1, currText);
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGaugeCurrent0, map(current,-2.8, max_curr, 0, 100));
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGaugeCurrent1, map(current,-2.8, max_curr, 0, 100));

    
    
    gslc_ElemSetTxtStr(&m_gui, m_pElemBatteryStatus0, battText);
    gslc_ElemXProgressSetVal(&m_gui, m_pElemProgressBattery, battery);
    if(temperature != 0.0F){ //this means not reading properly
      gslc_ElemSetTxtStr(&m_gui, m_pElemTempratureStatus0, tempText);
      gslc_ElemSetTxtStr(&m_gui, m_pElemTempratureStatus1, tempText);
      gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGaugeTemprature0, map(temperature, 0, max_temp, 0, 100));
      gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGaugeTemprature1, map(temperature, 0, max_temp, 0, 100));
    }
    // gslc_ElemSetTxtStr(&m_gui, m_pElemCurrentStatus0, battText);

}


// ------------------------------------------------
// Consumer Producer Loop
// ------------------------------------------------

void consumer_loop(void * parameter){
  for(;;){
    gslc_Update(&m_gui);
  }

}
void producer_loop(void * parameter){
  for(;;){

    current = getCurrent();
    temperature = getTemperature();
    //float battery = map(getBattery(), 0.0, 2.25, 0.0, 100.0);
    battery  = 71.0; // Cant have ADC2 GPIO14 and WIFI at same time figured this out to late 
    Serial.printf("\nCurrent: %.2f, Temprature: %.2f, Battery: %.2f, Power: %d", current, temperature, battery, power);
    stat_Update(battery, temperature, current);
    safety_Update(current, temperature, &power, max_curr, max_temp);
    writePWM(COIL_OUT_PWM_CHANNEL, power); 

    
    delay(20);
  }
}


// ------------------------------------------------
// Setup
// ------------------------------------------------
void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial 
  delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);
  // ----------------------------8//*--------------------
  // Init Peripherals
  // ------------------------------------------------
  // initWIFI(network, password);
  initPWM(COIL_OUT_PIN, COIL_OUT_PWM_CHANNEL, 0);
  initCurr(CURR_IN_PIN);  // Analog
  //initBatt(BATT_IN_PIN);
  initTemp();
  
  delay(1000);
  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();


  // ------------------------------------------------
  // Init tasks
  // ------------------------------------------------
  producer_timer = millis();
	xTaskCreatePinnedToCore(
			producer_loop, /* Function to implement the task */
			"Producer", /* Name of the task */
			10000, /* Stack size in words */
			NULL, /* Task input parameter */
			0, /* Priority of the task */
			&Producer, /* Task handle. */
			0); /* Core where the task should run */

  xTaskCreatePinnedToCore(
			consumer_loop, /* Function to implement the task */
			"Consumer", /* Name of the task */
			10000, /* Stack size in words */
			NULL, /* Task input parameter */
			0, /* Priority of the task */
			&Consumer, /* Task handle. */
			1); /* Core where the task should run */
	Serial.println("Setup completed.");


}


// -----------------------------------
// Main event loop
// -----------------------------------

void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
 
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  // current = getCurrent();
  // temperature = getTemperature();
  // battery = 50;

  //stat_Update(battery, temperature, current);
  //gslc_Update(&m_gui);
  vTaskDelete (NULL);
}

