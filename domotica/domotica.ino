// WEB SERVER (WIFI)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "config.dist.h"        // Wifi credentials
WebServer server(80);

// DISPLAY
#include "DFRobot_OLED12864.h"
#include "OLEDDisplayUi.h"      // Include the UI lib
#include "images.h"             // Custom images file

// Initialize the OLED display using Wire library
DFRobot_OLED12864  display(0x3c);
OLEDDisplayUi ui(&display);


// CT SENSOR
#include "EmonLib.h"
double intensity;
double power;
char itensityTxt[10];                                         // Current intensity as text
char powerTxt[10];

// JOYSTICK AND BUTTONS
int joy;
bool btnA, btnB;
char joyTxt[10];

void setup()
{
  Serial.begin(115200);

  setUpButtons();
  setUpCTsensor();
  
  initDisplay();
  ui.update();

  setupWebServer();
}

void loop()
{ 
 
  // WEB SERVER
  server.handleClient();

  // CT SENSOR
  intensity = readIntensity();
  power = getPower();
  getIntensityText(itensityTxt);
  getPowerText(powerTxt);

  // JOYSTICK AND BUTTONS
  joy = readJoystick();
  btnA = readBtnA();
  btnB = readBtnB();
  getJoystickTxt(joyTxt);                                 // Joystick value as text

  // FRAME CONTROL
  if(joy == 1){
    ui.nextFrame();                                       // Right transition 
  }else if(joy == 4){
    ui.previousFrame();                                   // Left transition
  }

  // DISPLAY
  ui.update();
}
