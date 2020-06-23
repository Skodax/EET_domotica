#define JOYSTICK_PIN 35
#define BTNA_PIN 25
#define BTNB_PIN 26
int joyRaw, joyVal;
bool _btnA = true, _btnB = true;                      // Private variables, holds the button state

// BTN ISR
// IRAM_ATTR = place code into RAM for faster execution
void IRAM_ATTR isr_btnA(){
  _btnA = digitalRead(BTNA_PIN);
}
void IRAM_ATTR isr_btnB(){
  _btnB = digitalRead(BTNB_PIN);
}

// BTN SETUP
void setUpButtons(){
  pinMode(BTNA_PIN, INPUT);                       // Declare buttons pin as input
  pinMode(BTNB_PIN, INPUT);

  attachInterrupt(BTNA_PIN, isr_btnA, CHANGE);   // Atach btn isr to the pin on falling edge
  attachInterrupt(BTNB_PIN, isr_btnB, CHANGE);   // Atach btn isr to the pin on falling edge
}

// BTN READ
bool readBtnA(){
  return !_btnA;      // Buttons are active low, so value is inverted for active high read
}

bool readBtnB(){
  return !_btnB;      // Buttons are active low, so value is inverted for active high read
}

// JOYSTICK READ
int readJoystick(){

  // READ ANALOG VALUE
  joyRaw = analogRead(JOYSTICK_PIN);

  // CONVERT TO DIGITAL
  if(joyRaw > 3600)     {joyVal = 0;}     // IDLE (no user action)
  else if(joyRaw > 2700){joyVal = 1;}     // RIGHT
  else if(joyRaw > 1800){joyVal = 2;}     // PUSH
  else if(joyRaw > 1000){joyVal = 3;}     // UP
  else if(joyRaw > 300) {joyVal = 4;}     // LEFT
  else                  {joyVal = 5;}     // DOWN

  return joyVal;
}

void getJoystickTxt(char *joystickTxt){
  switch (joyVal) {
    case 0:
      strcpy(joystickTxt, "IDLE");
      return;
      
    case 1:
      strcpy(joystickTxt, "RIGHT");
      return;
      
    case 2:
      strcpy(joystickTxt, "PUSH");
      return;
         
    case 3:
      strcpy(joystickTxt, "UP");
      return;
          
    case 4:
      strcpy(joystickTxt, "LEFT");
      return;
            
    case 5:
      strcpy(joystickTxt, "DOWN");
      return;
  }
}
