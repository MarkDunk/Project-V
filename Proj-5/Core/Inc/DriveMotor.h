

#include "stm32f303xe.h"
#include "stm32f3xx_hal.h"

void DriveMotor_Init(void);
void SetMotorSpeed( uint8_t motor, uint16_t dutyCycle );
void SetMotorDir( char dir );
void MotorsForward(void);
void MotorsBackward(void);
void HalfRight(void);
void HalfLeft(void);
void RevRight(void);
void RevLeft(void);
void FullRight(void);
void FullLeft(void);
