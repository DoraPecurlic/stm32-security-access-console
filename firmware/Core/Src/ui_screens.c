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


