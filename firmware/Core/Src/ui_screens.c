/*
 * screens.c
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#include "uart_console.h"

void ShowWelcomeScreen(void)
{
	ClearScreen();
	UART_SendString("\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("    STM32 Security Access Console\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("\r\n");
}
void ShowLockScreen(void)
{
	ClearScreen();
	UART_SendString("\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("   !!! STM32 Security Access LOCKED!!!\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("\r\n");
}


void UI_ShowMainMenuScreen(void)
{
	ClearScreen();
	ShowWelcomeScreen();

    UART_SendString("Available commands:\r\n\r\n");
    UART_SendString("  help     - Show user manual\r\n");
    UART_SendString("  status   - Show system status\r\n");
    UART_SendString("  alarm    - Alarm control\r\n");
    UART_SendString("  door     - Door control\r\n");
    UART_SendString("  lock     - Lock console\r\n");

    UART_SendString("\r\nEnter command:");
    UART_ShowPrompt();
}

void UI_ShowHelpScreen(void)
{
	ClearScreen();

    UART_SendString("\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("          HELP - User Manual\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("\r\n");

    UART_SendString("Commands:\r\n");
    UART_SendString("  help      - Opens this help screen\r\n");
    UART_SendString("\r\n");
    UART_SendString("  status    - Shows overall system status \r\n");
    UART_SendString("\r\n");
    UART_SendString("  alarm     - Alarm control unit\r\n");
    UART_SendString("              User can turn on or off the alarm when needed\r\n");
    UART_SendString("              When alarm is triggered, LED is blinking fast\r\n");
    UART_SendString("              When alarm is not triggered, LED is turned off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  door      - Door control unit\r\n");
    UART_SendString("            - User can open or close the door\r\n");
    UART_SendString("              When door is opened, LED is turned on\r\n");
    UART_SendString("              When door is closed, LED is off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  lock      - Locks system\r\n");
    UART_SendString("            - User will be logged out\r\n");
    UART_SendString("\r\n");

    UART_SendString("Type 'back' to return to main menu\r\n");

    UART_ShowPrompt();
}
void UI_ShowStatusScreen(void)
{
	ClearScreen();

	UART_SendString("\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("          CURRENT SYSTEM STATUS\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("\r\n");

}
