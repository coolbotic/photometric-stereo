/**
 * @file home.cpp
 * @author James Barson
 * @brief Homing function for the ps rig.
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "home.h"


void home(AccelStepper& stepper) {
  /* Find the sensor */
  Serial.println("Looking for sensor...");
  stepper.runToNewPosition(250);            // move right incase already at home
  stepper.move(-999999);                  // accelerate till home found
  
  while(!digitalRead(ENDSTOP_PIN))
  {
    stepper.run();
  }

  stepper.setCurrentPosition(0);
  Serial.println("Sensor Detected!");
     
  /* Find left of sensor */
  Serial.println("Honing left of sensor....");
  for (size_t i = 0; i < HONING_ITERATIONS; i++)
  {
    
    stepper.move(HONING_OFFSET); // offset before honing
    stepper.runToPosition();
    
    stepper.setSpeed(-HONING_SPEED);        // move into the sensor

    // step till sensor reached
    while(!digitalRead(ENDSTOP_PIN)) { 
        stepper.runSpeed();
    }

    Serial.println(stepper.currentPosition()); // check pos
    stepper.setCurrentPosition(0); // set zero position
  }
  
  /* Find right of sensor */
  Serial.println("Honing right of sensor....");
  stepper.runToNewPosition(-HONING_OFFSET); // move to the right of sensor

      long sum = 0;
      for (size_t j = 0; j < HONING_ITERATIONS; j++)
      {
        stepper.move(-HONING_OFFSET); // offset before honing
        stepper.runToPosition();

        stepper.setSpeed(HONING_SPEED); // move into the sensor slowly
        while(!digitalRead(ENDSTOP_PIN)) { // keep stepping till sensor reached
            stepper.runSpeed();
        }

        Serial.println(stepper.currentPosition());
        sum = sum + stepper.currentPosition();
      }

      long centersensor = (sum/HONING_ITERATIONS) / 2;

      for (size_t k = 0; k < HONING_ITERATIONS; k++)
      {
        stepper.runToNewPosition(0); // run to 0
        stepper.runToNewPosition(centersensor);
      }

      stepper.setCurrentPosition(0); // set zero position
};