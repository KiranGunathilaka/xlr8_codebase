#include <Arduino.h>
#include "systick.h"
#include "config.h"
#include "adc.h"
#include "sensors.h"
#include "printer.h"
#include "calibaration.h"
#include "motion.h"
#include "profile.h"
#include "robot.h"
#include "reporting.h"

Motors motors;
Encoders encoders;
Sensors sensors;
Systick systick;
ADC adc;
Printer printer;
Calibaration calibaration;
Robot robot;
Motion motion;
Profile rotation;
Profile forward;
Reporting reporter;

void setup()
{
  Serial.begin(115200);

  encoders.begin();
  motors.begin();
  //sensors.begin();
  systick.begin();
  reporter.begin();

  motion.reset_drive_system();

  sensors.set_steering_mode(STEERING_OFF);

  // Optional: Use motors to move during calibration
  //calibaration.sensorAutoCalibrate();
}

void loop()
{

}