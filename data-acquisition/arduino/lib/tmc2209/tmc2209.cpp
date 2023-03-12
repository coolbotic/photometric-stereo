/**
 * @file tmc2209.cpp
 * @author James Barson
 * @version 0.1
 * @date 2023-03-11
 * @copyright Copyright (c) 2023
 * 
 */

#include "tmc2209.h"

// See tmc2209.h to configure default values and pin layout


/**
 * @brief Construct a new tmc2209 ::tmc2209 object
 * 
 */
tmc2209_::tmc2209_() {
  // configure the arduino pins to outputs
  pinMode(DIR, OUTPUT); 
  pinMode(STEP, OUTPUT); 
  pinMode(EN, OUTPUT); 
  pinMode(MS1, OUTPUT); 
  pinMode(MS2, OUTPUT);

  // enable motor
  // enabled(true);

  // set default setup size
  setMicrostep(DEFAULT_MICROSTEP);
};

/**
 * @details Microstep value is based on a matrix of the values of MS1 & MS2 pins. Further details can be found in the tmc2209 data sheet,
 * @link https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2209_Datasheet_V103.pdf
 * @page 13
 */
void tmc2209_::setMicrostep(int microstep) {
  switch (microstep) {
    case 8:
      digitalWrite(MS1, LOW);
      digitalWrite(MS2, LOW);
    break;
    case 16:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
    break;
    case 32:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, LOW);
    break;
    case 64:
      digitalWrite(MS1, LOW);
      digitalWrite(MS2, HIGH);
    break;
    default:
      Serial.print("ERROR: Invalid microstep value");
    return;
  }

  Serial.print("MICROSTEP RESOLUTION: "); Serial.println(microstep);
};

void tmc2209_::move(int steps, uint8_t direction, unsigned int delay){
    digitalWrite(DIR, direction);
    for (int i = 0; i < steps; i++) {
      step();
      delayMicroseconds(delay);
    }
}

void tmc2209_::enabled(boolean input){
  if (input == true)
  {
    Serial.println("MOTOR ENABLED: TRUE");
    digitalWrite(EN, LOW);
  } else 
  {
    Serial.println("MOTOR ENABLED: FALSE");
    digitalWrite(EN, HIGH);
  }
  
 
}

void step() {
  // TODO: Dynamically create bitmask based on 'STEP' pin rather than hardcoded.
  // PORTD maps to Arduino digital pins 0 to 7
  PORTD = PORTD | B00100000; // bitmask pin 5
  PORTD = PORTD & B11011111; // reset pin 5
}

// Sensor
// Pin 2
// 5v
// GND

// Kill Button
// Pin 3

