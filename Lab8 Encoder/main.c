/*
 * File: main.c
 * Author: Alan Hosseinpour
 * Date: 04/12/2024
 * Description: Main executable file for the mobile robot lab project.
 *              This file contains the main function and other related functions
 *              to calculate and display the speed of the robot's wheels using
 *              encoders. The program also includes initialization and control 
 *              logic for the robot's motors and other components.
 */

#include "stm32f303xe.h"
#include "SysClock.h"
#include "UART.h"
#include "utility.h"
#include "Encoder.h"    // Include the Encoder header file
   

void calculateAndDisplayMotorSpeed() {
    // Calculate encoder periods
    Calculate_Encoder_TimePeriod();
    
    // Retrieve global encoder periods
    uint32_t leftPeriod = Global_LeftEncoderPeriod;
    uint32_t rightPeriod = Global_RightEncoderPeriod;
    
    // Calculate the speed of the left and right wheels in terms of revolutions per second
    // Assuming 20 vanes per wheel revolution and period in microseconds
    float leftSpeed = (float)(1.0 / (leftPeriod * 20e-6)); // Left wheel speed in revolutions per second
    float rightSpeed = (float)(1.0 / (rightPeriod * 20e-6)); // Right wheel speed in revolutions per second
    
    // Display the calculated motor wheel speed on the terminal
    printf("Left Wheel Speed: %.2f revolutions/s\n", (double)leftSpeed);
    printf("Right Wheel Speed: %.2f revolutions/s\n", (double)rightSpeed);
}
int main() {
    // Initialize encoders for left and right wheels
    Encoder_Init();

    // Main loop
    while (1) {
        // Calculate and display motor wheel speed
        calculateAndDisplayMotorSpeed();
        
        // Delay to control loop frequency (adjust as needed)
        delay_ms(1000); // 1 second delay between speed updates
        
        // Additional tasks can be added here as needed, e.g., motor control
    }
    
    // Return 0 to indicate successful completion
    return 0;
}