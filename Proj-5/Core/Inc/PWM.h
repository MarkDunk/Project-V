/*
 * PWM.h
 *
 *  Created on: Mar. 9, 2023
 *      Author: mark
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_
#include "stm32f303xe.h"

void PWMInit(void);

uint16_t AngleToCount(uint8_t angle);

void SetAngle(uint8_t angle);

#endif /* SRC_PWM_H_ */
