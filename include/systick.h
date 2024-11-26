#pragma once

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "sensors.h"
#include "Ticker.h"
#include "printer.h"
#include "motion.h"
#include "reporting.h"
#include "config.h"

class Systick;
extern Systick systick;

class Systick
{
private:
    Ticker ticker;

public:

    void begin()
    {
        encoders.setLoopTime(LOOP_TIME);
        ticker.attach(LOOP_TIME, []()
                      {
                          encoders.update();
                          //sensors.update();
                          motors.update(motion.velocity(), motion.omega(), sensors.get_steering_adjustment());
                          reporter.sendDebugData();
                        //   printer.printTimeDiff();
                        //   printer.printEncoderCounts();
                        //   printer.printSteeringAdjustment(false);
                        //   printer.printMotorFeedPercentages(true);
                      });
    }
};
