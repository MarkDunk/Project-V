#ifndef DCMOTOR_H
#define DCMOTOR_H

#include "stm32f303xe.h"

// Motor Constants
#define DCMOTOR_LEFT 0UL
#define DCMOTOR_RIGHT 1UL
#define DCMOTOR_STOP 0UL
#define DCMOTOR_FWD 1UL
#define DCMOTOR_BWD 2UL

// Function Prototypes
void DCMotor_Init(void);
void DCMotor_SetSpeed(uint8_t motor, uint16_t dutyCycle);
void DCMotor_SetDir(uint8_t motor, uint8_t dir);
void DCMotor_SetMotor(uint8_t motor, uint8_t dir, uint16_t dutyCycle);
void DCMotor_SetMotors(uint8_t leftDir, uint8_t rightDir, uint16_t leftDutyCycle, uint16_t rightDutyCycle);
void DCMotor_Stop(void);
void DCMotor_Forward(uint16_t dutyCycle);
void DCMotor_Backward(uint16_t dutyCycle);

#endif
