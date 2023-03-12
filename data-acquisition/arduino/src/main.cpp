/**
 * @file main.cpp
 * @author James Barson
 * @brief 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"


tmc2209_ motor;

AccelStepper stepper(AccelStepper::DRIVER, STEP, DIR);

  // Motor Power
  // 3.3v @ 1.5A -- 4.95W
  // TMC2209, Vm = 5V, max current is 1A (to keep in datasheet of motor)

  //TMC2209 
  // Vref = (Irms * 2.5V) / 1.77A (Rsense = 0.11ohm)
  // Vref = (0.7A * 2.5V) / 1.77A = 0.99V
  // Imax = Irms * 1.41 = 0.99A (within spec yay)

  // Wiring 
  // DIR = Pin 7 - 7
  // STEP = Pin 9 - 5
  // EN = Pin 8 - 11
  // MS1 = Pin 6 - 12
  // MS2 = Pin 5 - 13

  // Sensor
  // Pin 2
  // 5v
  // GND

  // Kill Button
  // Pin 3


// ISR Flags
volatile boolean e_stop = false;
volatile boolean endstop = false;

// Calibration
boolean calibration = false;
int calibration_counter = 0;

boolean homeSearch = false;

void e_stop_ISR() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 300ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 300) 
  {
    e_stop = !e_stop; // toggle 'e-stop' variable
    Serial.println("---------------------------------");
    Serial.println("E-STOP TRIGGERED");
    Serial.println("Please reset the Arduino (i.e. Unplug the USB cable)");
    
    digitalWrite(RELAY, LOW); // turn relay off (i.e. IR LED)
    Serial.println("RELAY ENABLED: FALSE");
    
    stepper.disableOutputs();
    Serial.println("MOTOR ENABLED: FALSE");

    Serial.println("(Please do not rely on this mechanism as it is only implemented in software, have the power plug nearby)");
    Serial.println("---------------------------------");
  };
  last_interrupt_time = interrupt_time;
  };

void endstop_ISR() {
  detachInterrupt(digitalPinToInterrupt(ENDSTOP_PIN)); // makes debounce unecessary
  endstop = !endstop; // toggle 'endstop' variable
};

// void endstopTesting() {
// detachInterrupt(digitalPinToInterrupt(ENDSTOP_PIN)); // makes debounce unecessary
// int step = 1;
// for (size_t i = 0; i < 1000; i++)
// {
//   motor.move(1, CLOCKWISE, 10000);
//   step = step + 1;
  
//   if (digitalRead(ENDSTOP_PIN))
//   {
//     Serial.println("ENDSTOP_PIN: TRUE");
//     Serial.print("Step: "); Serial.println(step);
//   }
   

//   // MICRO - 16
//   // ANTICLOCKWISE Sensor high, 270 - 335, 5000 delay (DIFF = 65)
//   // CLOCKWISE Sensor high, 566 - 630, 5000 delay (DIFF = 64)

//   // ANTICLOCKWISE Sensor high, 513 - 577, 10000 delay (DIFF = 64)
//   // CLOCKWISE Sensor high, 367 - 431, 1000 delay (DIFF = 64)

// }
// }

void setup() {
  // TEMP CODE
  pinMode(RELAY, OUTPUT);
  pinMode(ENDSTOP_PIN, INPUT); // endstop
  pinMode(E_STOP_ISR_PIN, INPUT_PULLUP); // button 
  // pinMode(EN, OUTPUT); // enable


  // attachInterrupt(digitalPinToInterrupt(ENDSTOP_PIN), endstop_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(E_STOP_ISR_PIN), e_stop_ISR, FALLING);


  digitalWrite(RELAY, LOW);
  // digitalWrite(EN, LOW);
  // put your setup code here, to run once:
  Serial.begin(115200);

  stepper.setMaxSpeed(1500.0);
  stepper.setAcceleration(150.0);
  stepper.setMinPulseWidth(150.0);
  stepper.setPinsInverted(false,false,true);
  stepper.setEnablePin(EN);
  // stepper.moveTo(5000);
  home(stepper);
  // stepper.moveTo(17142/360);
};


void loop() {



  stepper.run();
};



  /* CALIBRATION */
  // if (calibration == true) {
  //   // Serial.print("calibration:"); Serial.println(calibration);
  //   // Serial.print("calibration_counter:"); Serial.println(calibration_counter);
  //   // Serial.print("endstop:"); Serial.println(endstop);
    

  //   if (calibration_counter == 0) { // check if first iteration
  //     Serial.println("Moving away from home");
  //     motor.move(2000, CLOCKWISE, 2500); // push away incase at home point
  //   }

  //   if (calibration_counter <= 0 && endstop == false) {
  //     Serial.println("Trying to find home");
  //     Serial.print("calibration_counter: "); Serial.println(calibration_counter);
  //     motor.move(1, ANTICLOCKWISE, 2500);
  //     calibration_counter = (calibration_counter - 1);
  //   };

  //   if (calibration_counter <= 0 && endstop == true) {
  //     Serial.println("Home found");
  //     calibration_counter = 0; // reset counter
  //     // Serial.print("calibration_counter: "); Serial.println(calibration_counter);
  //     endstop = false; // clear the flag

  //     motor.move(30, CLOCKWISE, 2500); // move out the sensor
  //     calibration_counter = 30;
  //     attachInterrupt(digitalPinToInterrupt(ENDSTOP_PIN), endstop_ISR, RISING); // re-attach endstop ISR
  //   };

  //   // counting size
  //   if (calibration_counter >= 0 && endstop == false) {
  //     Serial.print("calibration_counter: "); Serial.println(calibration_counter);
  //     motor.move(1, CLOCKWISE, 2500);
  //     calibration_counter = (calibration_counter + 1);
  //   }

  //   if (calibration_counter >= 0 && endstop == true) {
  //     Serial.println("Calibration Finished");
  //     Serial.print("calibration_counter: "); 
  //     Serial.println(calibration_counter);
  //     endstop = false;
  //     calibration = false;
  //   }
    
  //   return;
  // };