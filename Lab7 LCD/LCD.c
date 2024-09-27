/*
Author: Alan Hosseinpour
File: LCD.c
Description: Implementation file for interfacing with an external LCD module using an STM32F303XE microcontroller.

Date: 04/01/2024

This file provides functions to initialize GPIO pins, send commands and data to the LCD, and print text on the display.
*/



#include "LCD.h"
#include <stdarg.h>
#include <stdio.h>
#include "utility.h"
#include "stm32f303xe.h"
#include "SysClock.h"

// Array to store custom character identifiers (values from 0 to 7)
unsigned char customChar[8] = {'<', '>', '|', '}', '{', ']', '[', '^'};
// Helper function to initialize GPIO pins for LCD
// 1. Turn on GPIOA clock
void LCD_GPIO_Init(void){
ENABLE_GPIO_CLOCK(A);

// Initialize GPIO PA6-11 pins one at a time
for(int i=6; i<=11; i++){
 GPIO_MODER_SET(A, i, GPIO_MODE_OUT);
 GPIO_OTYPER_SET(A, i, GPIO_OTYPE_PP);
 GPIO_PUPDR_SET(A, i, GPIO_PUPD_NO);
 }
}

// Initialize LCD
void LCD_Init(void) {
    LCD_GPIO_Init();

    // Sync with LCD (slapping it awake)
    CLEAR_BITS(LCD_PORT, LCD_RS_BIT | LCD_E_BIT | LCD_BUS_BIT); // Clear all 6 bits PA6-11
    LCD_E_LO;
    LCD_RS_IR;
    delay_ms(10);

    // Syncing step 1
    LCD_E_HI;
    LCD_BUS(0x03);
    LCD_E_LO; // Latch
    delay_ms(5);

    // Syncing step 2
    LCD_E_HI;
    LCD_BUS(0x03);
    LCD_E_LO; // Latch
    delay_ms(1);

    // Syncing step 3
    LCD_E_HI;
    LCD_BUS(0x03);
    LCD_E_LO; // Latch

    // Syncing step 4
    LCD_E_HI;
    LCD_BUS(0x02);
    LCD_E_LO; // Latch

    // Configure LCD using LCDcmd()
    LCDcmd(LCD_CMD_FUNCTION | LCD_FUNCTION_5X8FONT | LCD_FUNCTION_2LINES | LCD_FUNCTION_4BITBUS);
    LCDcmd(LCD_CMD_DISPLAY | LCD_DISPLAY_OFF);
    LCDcmd(LCD_CMD_CLEAR);
    LCDcmd(LCD_CMD_ENTRY | LCD_ENTRY_MOVE_CURSOR | LCD_ENTRY_INC);
    LCDcmd(LCD_CMD_DISPLAY | LCD_DISPLAY_NOBLINK | LCD_DISPLAY_NOCURSOR);
}

// Clear LCD display
void LCD_Clear(void) {
    delay_ms(LCD_STD_CMD_DELAY);
    LCDcmd(LCD_CMD_CLEAR);
    delay_ms(LCD_LONG_CMD_DELAY);
}

// Move cursor to home position
void LCD_HomeCursor(void) {
    LCDcmd(LCD_CMD_HOME);
    delay_ms(LCD_LONG_CMD_DELAY);
}

// Send command to LCD
void LCDcmd(uint8_t cmd) {
    delay_ms(LCD_STD_CMD_DELAY);
    LCD_E_LO;
    LCD_RS_IR; // Selecting command register
    LCD_E_HI;
    LCD_BUS(HI_NYBBLE(cmd));
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(LO_NYBBLE(cmd));
    LCD_E_LO;
}

// Send data to LCD
void LCDdata(uint8_t data) {
    delay_ms(LCD_STD_CMD_DELAY);
    LCD_E_LO;
    LCD_RS_DR; // Selecting data register
    LCD_E_HI;
    LCD_BUS(HI_NYBBLE(data));
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(LO_NYBBLE(data));
    LCD_E_LO;
}

// Put a character on LCD and handle custom characters
void LCDputc(unsigned char ch) {
    switch (ch) {
        case '\n':
            LCDdata(ch);
            LCDcmd(LCD_CMD_SETDDADDR | LCD_DDRAM_ADDR_LINE2); // Move cursor to line 2
            break;

        case '\r':
            LCD_HomeCursor(); // Move cursor to home position
            break;

        default:
            // Check if the character matches any custom character
            for (int i = 0; i < 8; i++) {
                if (ch == customChar[i]) {
                    LCDdata((uint8_t)i); // Send the corresponding custom character data (0-7)
                    return;
                }
            }
            // If no match, send the character as is
            LCDdata(ch);
            break;
    }
}

// Put a string on LCD
void LCDputs(char* str) {
    while (*str != '\0') {
        LCDputc(*str++);
    }
}

// Print formatted string on LCD
void LCDprintf(char* str, ...) {
    va_list args;
    char buffer[MAX_LCD_BUFSIZ];
    va_start(args, str);
    (void)vsnprintf(buffer, MAX_LCD_BUFSIZ, str, args);
    va_end(args);
    LCDputs(buffer);
}