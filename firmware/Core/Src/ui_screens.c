/*
 * screens.c
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#include "uart_console.h"
#include <stdint.h>

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
    UART_SendString("              When alarm is triggered, external LED is blinking fast\r\n");
    UART_SendString("              When alarm is not triggered, external LED is turned off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  door      - Door control unit\r\n");
    UART_SendString("            - User can open or close the door\r\n");
    UART_SendString("              When door is opened, user LED is turned on\r\n");
    UART_SendString("              When door is closed, user LED is off\r\n");
    UART_SendString("\r\n");
    UART_SendString("  lock      - Locks system\r\n");
    UART_SendString("            - User will be logged out\r\n");
    UART_SendString("\r\n");

    UART_SendString("Type 'back' to return to main menu\r\n");

    UART_ShowPrompt();
}
void UI_ShowStatusScreen(uint8_t isDoorOpened, uint8_t isAlarmOn)
{
	ClearScreen();

	UART_SendString("\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("          CURRENT SYSTEM STATUS\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("\r\n");

	if(isDoorOpened)
	{
		UART_SendString("Door:   OPENED\r\n");
	}
	else
	{
		UART_SendString("Door:   CLOSED\r\n");
	}

	if(isAlarmOn)
	{
			UART_SendString("Alarm:   ON\r\n");
	}
	else
	{
			UART_SendString("Alarm:   OFF\r\n");
	}

	UART_SendString("\r\n");
	UART_SendString("Type 'back' to return.\r\n");
	UART_SendString("> ");
}
void UI_ShowDoorControlScreen(uint8_t isDoorOpened)
{
    ClearScreen();

    UART_SendString("\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("             DOOR CONTROL\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("\r\n");

    if(isDoorOpened != 0U)
    {
        UART_SendString("Current door state: OPENED\r\n");
    }
    else
    {
        UART_SendString("Current door state: CLOSED\r\n");
    }

    UART_SendString("\r\n");
    UART_SendString("Available commands:\r\n");
    UART_SendString("  open  - Open the door\r\n");
    UART_SendString("  close - Close the door\r\n");
    UART_SendString("  back  - Return to main menu\r\n");
    UART_SendString("\r\n");

    UART_ShowPrompt();
}

void UI_ShowAlarmControlScreen(uint8_t isAlarmOn)
{
	ClearScreen();

	UART_SendString("\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("             ALARM CONTROL\r\n");
	UART_SendString("========================================\r\n");
	UART_SendString("\r\n");

	if(isAlarmOn != 0U)
	{
	   UART_SendString("Current alarm state: ON\r\n");
	}
	else
	{
	   UART_SendString("Current alarm state: OFF\r\n");
	}

	UART_SendString("\r\n");
	UART_SendString("Available commands:\r\n");
	UART_SendString("  ON  - Turn Alarm on\r\n");
	UART_SendString("  OFF - Turn alarm off\r\n");
	UART_SendString("  back  - Return to main menu\r\n");
	UART_SendString("\r\n");

	UART_ShowPrompt();

}
