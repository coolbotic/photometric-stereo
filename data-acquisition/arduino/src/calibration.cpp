/**
 * @file calibration.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "calibration.h"

void calibrate(AccelStepper& stepper) {
      Serial.print("SIZE");
      stepper.runToNewPosition(28*2); // move out of sensor

      stepper.setSpeed(750); // move into the sensor slowly
        while(!digitalRead(ENDSTOP_PIN)) { // keep stepping till sensor reached
            stepper.runSpeed();
        }

        Serial.println(stepper.currentPosition());
        stepper.moveTo(0);
}