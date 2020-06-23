#define CT_SENSOR_PIN 34
#define CT_SENSOR_CAL 1.957                               // Pendent to calibrate better
#define CT_SENSOR_NUM_OF_SAMPLES 1480

#define VOLTAGE 230                                       // Suply voltage of the network to measure

EnergyMonitor emon1;
double Irms = 0;                                          // Current intensity
double Pwr = 0;

void setUpCTsensor(){
  emon1.current(CT_SENSOR_PIN, CT_SENSOR_CAL);             // Current: input pin, calibration.
}

double readIntensity(){
    Irms = emon1.calcIrms(CT_SENSOR_NUM_OF_SAMPLES);        // Calculate Irms only
    if(Irms < 0.04){Irms = 0;}                              // Eliminate noise
    return Irms;
}

void getIntensityText(char *IrmsTxt){
  sprintf(IrmsTxt,"%.2f A", Irms);                          // Intensity as text. Two decimal value
}

double getPower(){
  Pwr = Irms * VOLTAGE;
  return Pwr;
}

void getPowerText(char *PwrTxt){
  sprintf(PwrTxt,"%.f W", Pwr);                            // Power as text. No decimal value
}
