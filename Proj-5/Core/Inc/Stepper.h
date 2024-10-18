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
void Step(void);
void Full_CW(void);
void Full_CCW(void);
void Half_CW(void);
void Half_CCW(void);

#endif /* SRC_STEPPER_H_ */
