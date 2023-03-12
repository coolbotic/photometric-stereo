/**
 * @file tmc2209.h
 * @author James Barson
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */


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


#ifndef TMC2209_H_
#define TMC2209_H_
#include <Arduino.h>

#define CLOCKWISE 0x1
#define ANTICLOCKWISE 0x0

/**
 * @brief Declaration of the Arduino UNO connection to the TMC2209.
 * @note These must be changed if you have altered the connections to the Arduino.
 */
const uint8_t DIR = 7;
const uint8_t STEP = 5; // Note: this is just for reference to change the step pin please see the 'step()' 
const uint8_t EN = 11;
const uint8_t MS1 = 12;
const uint8_t MS2 = 13;

const uint8_t DEFAULT_MICROSTEP = 8;


class tmc2209_
{

    public:
    /**
     * @brief Construct a new tmc2209_ object, initialise pins & set default microstep
     */
    tmc2209_();
    
    /**
     * @brief Set the microstep value for the tmc2209 stepper drive. 
     * @note This sets the number of microstep in a step.
     * i.e. this is the resolution, therefore 8 is the most course/biggest and 64 is the finest/smallest.
     * @param microstep takes a value of 8, 16, 32, 64
     */
    void setMicrostep(int microstep);

    /**
     * @brief 
     * 
     * @param steps 
     * @param ms 
     */
    void ramp(int steps, int ms);

    /**
     * @brief 
     * 
     * @param steps 
     * @param delay
     */
    void move(int steps, uint8_t direction, unsigned int delay);

    /**
     * @brief Enables or Disables motor by setting 'EN' pin.
     */
    void enabled(boolean input);

};



/**
 * @brief Toggle 'STEP' pin using direct port manipulation, as 'digitalWrite()' is too slow.
 */
void step();

#endif /* TMC2209_H_*/