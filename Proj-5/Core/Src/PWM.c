/*
 * PWM.c
 *
 *  Created on: Mar. 9, 2023
 *      Author: mark
 */

#include "stm32f303xe.h"
#include "PWM.h"

//Initialize CH2 of TIM15
void PWMInit(void){
	//enable gpiob clock
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//set to af
	GPIOB->MODER &= ~(0x03UL << (2*15));
	GPIOB->MODER |= (0x02UL << (2*15));
	//set af mode
	GPIOB->AFR[1] |= (0x1UL << (4*7));
	//No-pull
	GPIOB->PUPDR &= ~(0x3UL << (2*15));
	//set to output mode
	GPIOB->OTYPER &= ~(0x1UL << 15);
	//Enable APB2 bus
	RCC->APB2ENR |= (0x1UL << 16);
	//for 1us clock
	TIM15->PSC = 36;
	//20ms period
	TIM15->ARR = 20000;
	//enable ARPE
	TIM15->CR1 |= (0x1UL << 7);
	//Enable MOE
	TIM15->BDTR |= (0x1UL << 15);
	//Configure ch2 of TIM15
	TIM15->CCMR1 |= (0x6UL << 12);
	TIM15->CCMR1 |= (0x1UL << 11);
	//Enable output 2 of tim15
	TIM15->CCER |= (0x1UL << 4);
	//Clear the ccr2 reg
	TIM15->CCR2 = 0;

	//Force update
	TIM15->EGR |= (0x1UL);
	//Start the timer
	TIM15->CR1 |= (0x1UL);
}

//Convert angle to microseconds
uint16_t AngleToCount(uint8_t angle){
	//Keep the servo in bounds

	if(angle < -8500){
		angle = -8500;
	}
	else if(angle > 8500){
		angle = 8500;
	}
	//Angle converted to microseconds
	return(1500+(angle/100));
}

void SetAngle(uint8_t angle){
	TIM15->CCR2 = AngleToCount(angle);
}
