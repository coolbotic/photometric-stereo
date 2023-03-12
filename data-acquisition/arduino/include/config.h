/**
 * @file config.h
 * @author James Barson
 * @brief This file contains all the configuration options and pin layout for the photometric-stereo project.
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <stdint.h>


/* ---------------- TMC2209 ----------------- */
// Pins
// const uint8_t DIR = 7;
// const uint8_t STEP = 5;
// const uint8_t EN = 11;
// const uint8_t MS1 = 12;
// const uint8_t MS2 = 13;

// // Settings
// const uint8_t DEFAULT_MICROSTEP = 8;
/* ------------------------------------------- */


/* ---------------- home.cpp ----------------- */
// Settings

/* Number of times the honing procedure is repeated before moving on */
const uint8_t HONING_ITERATIONS = 2;

/* Speed of motor when honing exact sensor location */
const uint8_t HONING_SPEED =  10;

/* Number of steps to move away from sensor before next honing */
const uint8_t HONING_OFFSET = 30;
/* ------------------------------------------- */

/* -------------- calibrate.cpp -------------- */
/* ------------------------------------------- */

/* ----------------- endstop ----------------- */
const uint8_t ENDSTOP_PIN = 2;
/* ------------------------------------------- */

/* ------------------ relay ------------------ */
// Pins 
const uint8_t RELAY = 9;
/* ------------------------------------------- */

/* ------------------ e-stop ------------------ */
const uint8_t E_STOP_ISR_PIN= 3;
/* ------------------------------------------- */



#endif /* CONFIG_H_ */