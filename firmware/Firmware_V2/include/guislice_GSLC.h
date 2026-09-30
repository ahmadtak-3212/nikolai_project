//<File !Start!>
// FILE: [guislice_GSLC.h]
// Created by GUIslice Builder version: [0.17.b11]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Num.h"
#include "elem/XProgress.h"
#include "elem/XRingGauge.h"
#include "elem/XSeekbar.h"
#include "elem/XToggleImgbtn.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be arduino
#endif
#include <TFT_eSPI.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
extern "C" const unsigned short Sync[] PROGMEM;
extern "C" const unsigned short wifi_off[] PROGMEM;
extern "C" const unsigned short wifi_on[] PROGMEM;
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_POWER,E_PG_SETTINGS,E_PG_USER_SELECT
      ,E_POP_KEYPAD_NUM};
enum {E_DRAW_LINE0,E_DRAW_LINE3,E_DRAW_LINE4,E_DRAW_LINE5
      ,E_ELEM_BTN_BACK,E_ELEM_BTN_BACK_2,E_ELEM_BTN_POWER
      ,E_ELEM_BTN_SETTINGS,E_ELEM_IMAGEBTN_SYNC,E_ELEM_IMAGEBTN_WIFI
      ,E_ELEM_NUMINPUT_MC,E_ELEM_NUMINPUT_MT,E_ELEM_PROGRESS_BATTERY
      ,E_ELEM_RINGGAUGE_CURR,E_ELEM_RINGGAUGE_CURR_P
      ,E_ELEM_RINGGAUGE_TEMP_P,E_ELEM_RINGGUAGE_TEMP
      ,E_ELEM_SEEKBAR_COIL_POWER,E_ELEM_SELECT_AHMAD
      ,E_ELEM_SELECT_COLIN,E_ELEM_SELECT_DEVAN,E_ELEM_SELECT_JAMES
      ,E_ELEM_SELECT_SEBASTAIN,E_ELEM_SELECT_USER,E_ELEM_TEXT12
      ,E_ELEM_TEXT13,E_ELEM_TEXT14,E_ELEM_TEXT15,E_ELEM_TEXT17
      ,E_ELEM_TEXT18,E_ELEM_TEXT19,E_ELEM_TEXT20,E_ELEM_TEXT21
      ,E_ELEM_TEXT_BATTERY,E_ELEM_TEXT_CURR,E_ELEM_TEXT_CURR_P
      ,E_ELEM_TEXT_MAIN,E_ELEM_TEXT_POWER,E_ELEM_TEXT_POWER_TITLE
      ,E_ELEM_TEXT_TEMP,E_ELEM_TEXT_TEMP_P,E_ELEM_KEYPAD_NUM};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                5

#define MAX_ELEM_PG_MAIN 14 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_POWER 11 // # Elems total on page
#define MAX_ELEM_PG_POWER_RAM MAX_ELEM_PG_POWER // # Elems in RAM

#define MAX_ELEM_PG_SETTINGS 9 // # Elems total on page
#define MAX_ELEM_PG_SETTINGS_RAM MAX_ELEM_PG_SETTINGS // # Elems in RAM

#define MAX_ELEM_PG_USER_SELECT 7 // # Elems total on page
#define MAX_ELEM_PG_USER_SELECT_RAM MAX_ELEM_PG_USER_SELECT // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_POWER_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_POWER];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_SETTINGS_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_SETTINGS];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_USER_SELECT_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_USER_SELECT];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXProgress                m_sXBarGauge2;
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXToggleImgbtn            m_sToggleImg7;
gslc_tsXSeekbar                 m_sXSeekbar2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXRingGauge               m_sXRingGauge4;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemBatteryStatus0;
extern gslc_tsElemRef* m_pElemCurrentStatus0;
extern gslc_tsElemRef* m_pElemCurrentStatus1;
extern gslc_tsElemRef* m_pElemPowerStatus0;
extern gslc_tsElemRef* m_pElemProgressBattery;
extern gslc_tsElemRef* m_pElemSeekbarPower0;
extern gslc_tsElemRef* m_pElemSelectUser;
extern gslc_tsElemRef* m_pElemTempratureStatus0;
extern gslc_tsElemRef* m_pElemTempratureStatus1;
extern gslc_tsElemRef* m_pElemToggleImgWIFI;
extern gslc_tsElemRef* m_pElemValMaxCurrent;
extern gslc_tsElemRef* m_pElemValMaxTemprature;
extern gslc_tsElemRef* m_pElemXRingGaugeCurrent0;
extern gslc_tsElemRef* m_pElemXRingGaugeCurrent1;
extern gslc_tsElemRef* m_pElemXRingGaugeTemprature0;
extern gslc_tsElemRef* m_pElemXRingGaugeTemprature1;
extern gslc_tsElemRef* m_pElemKeyPadNum;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_POWER,m_asPage2Elem,MAX_ELEM_PG_POWER_RAM,m_asPage2ElemRef,MAX_ELEM_PG_POWER);
  gslc_PageAdd(&m_gui,E_PG_SETTINGS,m_asPage3Elem,MAX_ELEM_PG_SETTINGS_RAM,m_asPage3ElemRef,MAX_ELEM_PG_SETTINGS);
  gslc_PageAdd(&m_gui,E_PG_USER_SELECT,m_asPage4Elem,MAX_ELEM_PG_USER_SELECT_RAM,m_asPage4ElemRef,MAX_ELEM_PG_USER_SELECT);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  

  // Create progress bar E_ELEM_PROGRESS_BATTERY 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS_BATTERY,E_PG_MAIN,&m_sXBarGauge2,
    (gslc_tsRect){10,10,25,12},0,100,0,GSLC_COL_BLUE_LT2,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK1,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemProgressBattery = pElemRef;
  
  // Create E_ELEM_TEXT_BATTERY text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_BATTERY,E_PG_MAIN,(gslc_tsRect){40,10,25,10},
    (char*)"50 %",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemBatteryStatus0 = pElemRef;

  // Create ring gauge E_ELEM_RINGGUAGE_TEMP 
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGUAGE_TEMP,E_PG_MAIN,&m_sXRingGauge1,
          (gslc_tsRect){210,170,60,60},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 60); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 7);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 0, 360, false);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, ((gslc_tsColor){125,214,0}), GSLC_COL_RED);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemXRingGaugeTemprature0 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE_CURR 
  static char m_sRingText2[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE_CURR,E_PG_MAIN,&m_sXRingGauge2,
          (gslc_tsRect){40,170,60,60},
          (char*)m_sRingText2,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 60); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 7);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, ((gslc_tsColor){125,214,0}), GSLC_COL_RED);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemXRingGaugeCurrent0 = pElemRef;
  
  // Create E_ELEM_TEXT_MAIN text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_MAIN,E_PG_MAIN,(gslc_tsRect){96,10,127,26},
    (char*)"NIKOLAI",0,E_BUILTIN15X24);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE0 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE0,E_PG_MAIN,95,40,225,40);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // Create E_ELEM_IMAGEBTN_WIFI button with image label
  pElemRef = gslc_ElemXToggleImgbtnCreate(&m_gui,E_ELEM_IMAGEBTN_WIFI,E_PG_MAIN,&m_sToggleImg7,(gslc_tsRect){285,10,25,25},
          gslc_GetImageFromProg((const unsigned char*)wifi_on,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromProg((const unsigned char*)wifi_off,GSLC_IMGREF_FMT_BMP24),
          false,&CbBtnCommon);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemToggleImgWIFI = pElemRef;
  
  // Create E_ELEM_IMAGEBTN_SYNC button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_ELEM_IMAGEBTN_SYNC,E_PG_MAIN,(gslc_tsRect){250,10,25,25},
          gslc_GetImageFromProg((const unsigned char*)Sync,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromProg((const unsigned char*)Sync,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_ELEM_TEXT_CURR text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_CURR,E_PG_MAIN,(gslc_tsRect){40,196,60,10},
    (char*)"3.5",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemCurrentStatus0 = pElemRef;
  
  // Create E_ELEM_TEXT_TEMP text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_TEMP,E_PG_MAIN,(gslc_tsRect){210,196,60,10},
    (char*)"32.7",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  m_pElemTempratureStatus0 = pElemRef;
  
  // Create E_ELEM_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_MAIN,(gslc_tsRect){40,150,67,10},
    (char*)"Current (A)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT15,E_PG_MAIN,(gslc_tsRect){200,150,85,10},
    (char*)"Temprature (C)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // create E_ELEM_BTN_POWER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_POWER,E_PG_MAIN,
    (gslc_tsRect){21,76,120,40},(char*)"POWER",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_LT1,GSLC_COL_BLUE_DK1);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN_SETTINGS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_SETTINGS,E_PG_MAIN,
    (gslc_tsRect){181,76,120,40},(char*)"SETTINGS",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_LT1,GSLC_COL_BLUE_DK1);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_PG_POWER
  

  // Create seekbar E_ELEM_SEEKBAR_COIL_POWER 
  pElemRef = gslc_ElemXSeekbarCreate(&m_gui,E_ELEM_SEEKBAR_COIL_POWER,E_PG_POWER,&m_sXSeekbar2,
    (gslc_tsRect){20,80,280,50},0,255,0,
    15,14,16,GSLC_COL_BLUE,GSLC_COL_GRAY,GSLC_COL_BLUE_DK2,false);
  gslc_ElemXSeekbarSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemXSeekbarSetStyle(&m_gui,pElemRef,true,GSLC_COL_BLUE_LT4,false,GSLC_COL_GRAY,
    0,0,GSLC_COL_BLACK);
  m_pElemSeekbarPower0 = pElemRef;
  
  // Create E_ELEM_TEXT_POWER_TITLE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_POWER_TITLE,E_PG_POWER,(gslc_tsRect){50,10,217,26},
    (char*)"Change Power",0,E_BUILTIN15X24);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // Create ring gauge E_ELEM_RINGGAUGE_CURR_P 
  static char m_sRingText3[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE_CURR_P,E_PG_POWER,&m_sXRingGauge3,
          (gslc_tsRect){40,170,60,60},
          (char*)m_sRingText3,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 60); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 7);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, ((gslc_tsColor){125,214,0}), GSLC_COL_RED);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemXRingGaugeCurrent1 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE_TEMP_P 
  static char m_sRingText4[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE_TEMP_P,E_PG_POWER,&m_sXRingGauge4,
          (gslc_tsRect){210,170,60,60},
          (char*)m_sRingText4,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 60); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 7);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, 0, 360, false);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, ((gslc_tsColor){125,214,0}), GSLC_COL_RED);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemXRingGaugeTemprature1 = pElemRef;

  // Create E_DRAW_LINE3 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE3,E_PG_POWER,50,40,270,40);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // Create E_ELEM_TEXT_CURR_P text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_CURR_P,E_PG_POWER,(gslc_tsRect){40,196,60,10},
    (char*)"3.5",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemCurrentStatus1 = pElemRef;
  
  // Create E_ELEM_TEXT_TEMP_P text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_TEMP_P,E_PG_POWER,(gslc_tsRect){210,196,60,10},
    (char*)"32.5",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemTempratureStatus1 = pElemRef;
  
  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT12,E_PG_POWER,(gslc_tsRect){200,150,85,10},
    (char*)"Temprature (C)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT13,E_PG_POWER,(gslc_tsRect){40,150,67,10},
    (char*)"Current (A)",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // create E_ELEM_BTN_BACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BACK,E_PG_POWER,
    (gslc_tsRect){125,180,70,40},(char*)"Back",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_DK1,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT_POWER text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_POWER,E_PG_POWER,(gslc_tsRect){141,60,37,18},
    (char*)"0",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_pElemPowerStatus0 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SETTINGS
  
  
  // Create E_ELEM_TEXT17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT17,E_PG_SETTINGS,(gslc_tsRect){87,10,145,26},
    (char*)"SETTINGS",0,E_BUILTIN15X24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // Create E_DRAW_LINE4 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE4,E_PG_SETTINGS,85,40,235,40);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // create E_ELEM_BTN_BACK_2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BACK_2,E_PG_SETTINGS,
    (gslc_tsRect){240,190,70,40},(char*)"Back",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_DK1,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT18,E_PG_SETTINGS,(gslc_tsRect){8,60,61,18},
    (char*)"USER:",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT19,E_PG_SETTINGS,(gslc_tsRect){5,105,157,18},
    (char*)"MAX CURRENT: ",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_NUMINPUT_MC numeric input field
  static char m_sInputNumber1[7] = "3";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT_MC,E_PG_SETTINGS,(gslc_tsRect){191,95,120,35},
    (char*)m_sInputNumber1,7,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValMaxCurrent = pElemRef;
  
  // Create E_ELEM_TEXT20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT20,E_PG_SETTINGS,(gslc_tsRect){7,148,193,18},
    (char*)"MAX TEMPRATURE: ",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_NUMINPUT_MT numeric input field
  static char m_sInputNumber2[7] = "36";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT_MT,E_PG_SETTINGS,(gslc_tsRect){191,140,120,35},
    (char*)m_sInputNumber2,7,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemValMaxTemprature = pElemRef;
  
  // create E_ELEM_SELECT_USER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_USER,E_PG_SETTINGS,
    (gslc_tsRect){90,50,220,35},(char*)"AHMAD",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemSelectUser = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_USER_SELECT
  
  
  // Create E_ELEM_TEXT21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT21,E_PG_USER_SELECT,(gslc_tsRect){60,10,199,26},
    (char*)"SELECT USER",0,E_BUILTIN15X24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);

  // Create E_DRAW_LINE5 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE5,E_PG_USER_SELECT,60,41,260,41);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // create E_ELEM_SELECT_AHMAD button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_AHMAD,E_PG_USER_SELECT,
    (gslc_tsRect){50,49,220,30},(char*)"AHMAD",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // create E_ELEM_SELECT_JAMES button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_JAMES,E_PG_USER_SELECT,
    (gslc_tsRect){50,86,220,30},(char*)"JAMES",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // create E_ELEM_SELECT_COLIN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_COLIN,E_PG_USER_SELECT,
    (gslc_tsRect){50,123,220,30},(char*)"COLIN",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // create E_ELEM_SELECT_SEBASTAIN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_SEBASTAIN,E_PG_USER_SELECT,
    (gslc_tsRect){50,160,220,30},(char*)"SEBASTAIN",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // create E_ELEM_SELECT_DEVAN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SELECT_DEVAN,E_PG_USER_SELECT,
    (gslc_tsRect){50,197,220,30},(char*)"DEVAN",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
