/*
 * Stepper.c
 *
 *  Created on: Feb 2, 2023
 *      Author: mark
 */


#include "Stepper.h"
#include "stm32f303xe.h"


#define numSteps 8 //Number of motor states

static uint8_t index = 0;
static uint16_t steps = 0;
uint16_t pos = 0;

static char Steps[numSteps] = {0x9, 0x8, 0xa, 0x2, 0x6, 0x4, 0x5, 0x1}; //Stepper output mask

void Stepper_Init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	GPIOC->MODER &= ~(0xFFUL); //Clear PC0-3 mode bits
	GPIOC->MODER |= (0x55UL); //Set PC0-3 to output

	GPIOC->OTYPER &= ~(0xFUL); //Set output to push-pull

	GPIOC->PUPDR &= ~(0xFUL); //Set no pull-up
}

void Home_Stepper(void){
	while(!(GPIOC->IDR | (0x1<<5))){
		Full_CW();
	}
	while(!(GPIOC->IDR | (0x1<<6))){
			Full_CCW();
			steps++;
	}
//	steps = steps/2;
	pos = steps/2;
	while(pos){
		Full_CW();
		pos--;
	}

	pos = steps/2;

}

void Step(void){
	if(!(GPIOC->IDR | (0x3 << 5))){
		GPIOC->ODR &= ~(0xFUL); //Reset PC0-3 but keep the output state of the other ports
		GPIOC->ODR |= Steps[(index & 0x7UL)]; //Set output to index referenced value
	}
}

void Set_Position(uint8_t angle){
	if(angle < 128){
		if (pos > steps){
			Full_CW();
		}else if (pos <)
	}
	else{
		angle = angle - 128;

	}
}

void Full_CW(void){
	index += 2;
	Step();
}

void Full_CCW(void){
	index -= 2;
	Step();
}

//void Half_CW(void){
//	index++;
//	Step();
//}
//
//void Half_CCW(void){
//	index--;
//	Step();
//}
