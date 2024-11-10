#include <Arduino.h>
#include "systick.h"
#include "config.h"
#include "adc.h"
#include "sensors.h"
#include "printer.h"
#include "calibaration.h"
#include "robot.h"

Motors motors;
Encoders encoders;
Sensors sensors;
Systick systick;
ADC adc;
Printer printer;
Calibaration calibaration;
Robot robot;


void setup()
{
  Serial.begin(115200);

  encoders.begin();
  motors.begin();
  sensors.begin();
  systick.begin();

  sensors.set_steering_mode(STEER_NORMAL);
  
}

void loop()
{

}