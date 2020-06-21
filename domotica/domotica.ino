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
  Serial.println();
  Serial.println();

  setUpButtons();
  setUpCTsensor();
  
  initDisplay();
}

void loop()
{ 
  // DISPLAY
  int remainingTimeBudget = ui.update();
  
  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    
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
  }
}
