#pragma once

#include <Wire.h>
#include "config.h"
#include "encoders.h"

class Sensors;
extern Sensors sensors;

enum
{
    STEER_NORMAL,
    STEERING_OFF,
};

enum
{
    FAST_MODE,
    SLOW_MODE
};

class Sensors
{
private:

    float last_steering_error = 0;
    float accumelated_steering_error = 0;
    volatile float cross_track_error;
    volatile float steering_adjustment;

public:
    float steering_kp = STEERING_KP;
    float steering_kd = STEERING_KD;


    bool enableIR = false;

    uint8_t steering_mode = STEER_NORMAL;

    // Initialize all sensors
    void begin()
    {

    }


    // to not take readings and save time
    void enableIR_Readings()
    {
        enableIR = true;
    }

    void disableIR_Readings()
    {
        enableIR = false;
    }

    float get_steering_adjustment()
    {
        return steering_adjustment;
    }


    void set_steering_mode(uint8_t mode)
    {
        last_steering_error = cross_track_error;
        steering_adjustment = 0;
        steering_mode = mode;
    }

    void calculate_steering_adjustment()
    {
        float pTerm = steering_kp * cross_track_error;
        float dTerm = steering_kd * (cross_track_error - last_steering_error);

        float adjustment = (pTerm + dTerm) * encoders.getLoopTime();

        last_steering_error = cross_track_error;
        steering_adjustment = adjustment;
    }

    void update()
    {
        
    }

   
};