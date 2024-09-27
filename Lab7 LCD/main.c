/*
Author: Alan Hosseinpour
File: main.c
Description: Main program file for interfacing with an external LCD module using an STM32F303XE microcontroller
Date: 04/10/2024 (Updated)

This program initializes the necessary GPIO ports and LCD module, and displays text on the LCD screen.
The top line of the display shows the name(s) of the author(s), while the second line displays a formatted
4-digit hexadecimal number that increments continuously.

*/

#include "stm32f303xe.h"
#include "SysClock.h"
#include "UART.h"
#include "utility.h"
#include "LCD.h"

int main(void) {
    // Initialize system clock
    System_Clock_Init();
    SystemCoreClockUpdate(); // Update system core clock

    // Initialize LCD and check for errors (if any)
    LCD_Init();
    
    // Clear the display
    LCD_Clear();

    // Print your name(s) on the top line of the display
    LCDputs("Alan HPM");

    // Initialize count variable
    uint16_t count = 0;

    // Define delay in milliseconds will be adjusted if needed 
    const uint16_t display_delay_ms = 500;

    // Loop forever
    while (1) {
        // Print the count variable on the second line of the display as a formatted 4-digit hexadecimal number
        char count_str[5]; // Buffer for formatted count

        // Format count variable as 4-digit hexadecimal number and store in count_str
        sprintf(count_str, "%04X", count);

        // Move the cursor to the start of the second line of the display
        LCDcmd(LCD_CMD_SETDDADDR | LCD_DDRAM_ADDR_LINE2);

        // Display the formatted count on the second line of the display
        LCDputs(count_str);

        // Increment the count variable
        count++;

        // Delay to control refresh rate of the display and ensure readability
        delay_ms(display_delay_ms);
    }

    // The program should never reach here, but you can handle exit conditions if desired
    return 0; // This is optional since the program loops indefinitely
}