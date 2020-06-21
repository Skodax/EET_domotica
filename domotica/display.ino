void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
  // DISPLAY THE CURRENT INTESITY VALUE
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_24);
  display->drawString(x, y, "Instensity");

  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(128 + x, 30 + y, IrmsTxt);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
  // DISPLAY THE CURRENT JOYSTICK VALUE
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(x, y, "Joy");
  display->drawString(x, 20 + y, "Btn A");
  display->drawString(x, 40 + y, "Btn B");

  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(128 + x, y, joyTxt);

  if(btnA){
    display->drawFastImage(110 + x, 25 + y, 8, 8, activeSymbol);
  } else {
    display->drawFastImage(110 + x, 25 + y, 8, 8, inactiveSymbol);
  }

  if(btnB){
    display->drawFastImage(110 + x, 45 + y, 8, 8, activeSymbol);
  } else {
    display->drawFastImage(110 + x, 45 + y, 8, 8, inactiveSymbol);
  }
}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawFrame1, drawFrame2};

// how many frames are there?
int frameCount = 2;

void initDisplay(){
  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(30);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Manual frames transition
  ui.disableAutoTransition();

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();
}
