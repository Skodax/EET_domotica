// DISPLAY
#include "DFRobot_OLED12864.h"
#include "OLEDDisplayUi.h"      // Include the UI lib
#include "images.h"             // Custom images file

// Initialize the OLED display using Wire library
DFRobot_OLED12864  display(0x3c);
OLEDDisplayUi ui(&display);


// CT SENSOR
#include "EmonLib.h"
#define CT_SENSOR_PIN 2
#define CT_SENSOR_CAL 10
EnergyMonitor emon1;
double Irms = 0;                                          // Current intensity
char IrmsTxt[10];                                         // Current intensity as text

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
  
  emon1.current(CT_SENSOR_PIN, CT_SENSOR_CAL);             // Current: input pin, calibration.
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
    Irms = emon1.calcIrms(1480);                            // Calculate Irms only
    sprintf(IrmsTxt,"%.2f A", Irms);
  
    // JOYSTICK AND BUTTONS
    joy = readJoystick();
    btnA = readBtnA();
    btnB = readBtnB();
    
    getJoystickTxt(joyTxt);
    if(joy == 1){
      // Right transition
      ui.nextFrame();      
    }else if(joy == 4){
      // Left transition
      ui.previousFrame();
    }
  }
}
