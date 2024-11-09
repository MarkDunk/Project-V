/*
 * Stepper.h
 *
 *  Created on: Feb 2, 2023
 *      Author: mark
 */

#ifndef SRC_STEPPER_H_
#define SRC_STEPPER_H_
#include "stm32f303xe.h"

void Stepper_Init(void);
void Home_Stepper(void);
void Set_Position(uint8_t angle);
void Step(void);
void Full_CW();
void Full_CCW();
void Half_CW();
void Half_CCW();

#endif /* SRC_STEPPER_H_ */
