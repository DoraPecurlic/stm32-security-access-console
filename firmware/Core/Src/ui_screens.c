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
    UART_SendString("                HELP\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("\r\n");

    UART_SendString("This console controls a simple STM32 security system.\r\n");
    UART_SendString("\r\n");
    UART_SendString("Commands:\r\n");
    UART_SendString("  help      - Opens this help screen\r\n");
    UART_SendString("\r\n");
    UART_SendString("  status    - Shows overall system status \r\n");
    UART_SendString("\r\n");
    UART_SendString("  alarm     - Alarm control unit; User can turn on the alarm when needed or turn it of.\r\n");
    UART_SendString("              When alarm is triggered, LED is blinking fast\r\n");
    UART_SendString("              When alarm is not triggered, LED is turned off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  door      - Door control unit; User can open or close the door\r\n");
    UART_SendString("              When door is opened, LED is turned on\r\n");
    UART_SendString("              When door is closed, LED is off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  lock      - Locks system; User is logged out \r\n");
    UART_SendString("\r\n");

    UART_SendString("Type 'back' to return to main menu.\r\n");

    UART_ShowPrompt();
}
