#pragma once

#include "Arduino.h"
#include "config.h"
#include "reporting.h"
#include "sensors.h"
#include "systick.h"

class Robot;
extern Robot robot;

class Robot
{
public:
    bool crossEncountered = false;
    bool turnEncountered = false;

    void run()
    {

        while (true)
        {
            LineFeature feature = sensors.detectFeature();

            switch (feature)
            {
            case STRAIGHT_LINE:
                // Normal line following
                followLineUntilFeature();
                break;

            case LEFT_TURN:
                turnLeft();
                break;

            case RIGHT_TURN:
                turnRight();
                break;

            case T_JUNCTION:
                handleTJunction();
                break;

            case CROSS_JUNCTION:
                handleCrossJunction();
                break;

            case NO_LINE:
                handleNoLine();
                break;
            }
        }
    }

    void followLineUntilFeature()
    {
        sensors.set_steering_mode(STEER_NORMAL);
        motion.reset_drive_system();
        motion.start_move(GO_FORWARD_DISTANCE, RUN_SPEED, RUN_SPEED, RUN_ACC);
        while (!motion.move_finished())
        {
            delay(LOOP_TIME * 1000);

            // if they detect a front wall, decelerate only to cover the remaining position
            if (sensors.detectFeature() != STRAIGHT_LINE)
                ;
            {
                break;
            }
        }
    }

    void turnLeft()
    {
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_turn(-90, OMEGA, 0, ALPHA);

        while (!motion.turn_finished())
        {
            delay(LOOP_TIME * 1000);
        }
    }

    void turnRight()
    {
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_turn(90, OMEGA, 0, ALPHA);

        while (!motion.turn_finished())
        {
            delay(LOOP_TIME * 1000);
        }
    }

    void handleTJunction()
    {
        turnLeft();
    }

    //3 types of t junction

    void handleCrossJunction()
    {
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_move(GO_FORWARD_JUNCTION_DISTANCE, RUN_SPEED, RUN_SPEED, RUN_ACC);
        while (!motion.move_finished())
        {
            delay(LOOP_TIME * 1000);
        }
    }

    void handleNoLine()
    {   
        bool lineDetected = false;

        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_move(CHECK_DASH_DISTANCE, RUN_SPEED, RUN_SPEED, RUN_ACC);
        while (!motion.move_finished())
        {
            delay(LOOP_TIME*1000);

            if (sensors.detectFeature() != NO_LINE){
                lineDetected = true;
                break;
            }
        }

        if (!lineDetected){
            turn_180();
        }
    }

    void turn_180()
    {
        sensors.set_steering_mode(STEERING_OFF);
        motion.reset_drive_system();
        motion.start_turn(180 , OMEGA, 0, ALPHA);

        while (!motion.turn_finished())
        {
            delay(LOOP_TIME);
        }
    }
};