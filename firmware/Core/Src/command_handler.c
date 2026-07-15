/*
 * command-handler.c
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#include "command_handler.h"
#include "ui_screens.h"
#include "uart_console.h"
#include "main.h"

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <string.h>


extern UART_HandleTypeDef huart2;

#define COMMAND_BUFFER_SIZE 20U
#define ALARM_BLINK_INTERVAL_MS 500U

typedef enum
{
	MAIN_MENU_SCREEN,
	HELP_SCREEN,
	STATUS_SCREEN,
	ALARM_CONTROL_SCREEN,
	DOOR_CONTROL_SCREEN
}CurrentScreen;

/* private variables */
static CurrentScreen currentScreen = MAIN_MENU_SCREEN;
static uint8_t screenRefresh = 0;
static uint32_t lastAlarmBlinkTime = 0U;

static char commandBuffer[COMMAND_BUFFER_SIZE];
static uint8_t commandBufferIndex = 0;

static uint8_t isDoorOpened = 0U;
static uint8_t isAlarmOn = 0U;

/* private functions */
static void ShowCurrentScreen(void);
static CommandResult HandleInput(void);
static CommandResult HandleRecievedCharacter(uint8_t rxChar);
static CommandResult HandleCommand();
static void AddCharToBuffer(uint8_t rxChar);
static void ClearCommandBuffer(void);
static CommandResult ExecuteCommand(void);

static void HandleDoorControlCommand(void);
static void SetDoorState(uint8_t opened);

static void HandleAlarmControlCommand(void);
static void SetAlarmState(uint8_t alarmOn);
static void UpdateAlarmLed(void);

static void ReEnterCommand(void);


void CommandHandler_Init(void)
{

	currentScreen = MAIN_MENU_SCREEN;

	screenRefresh = 1;

	SetDoorState(0U);
	SetAlarmState(0U);

}

CommandResult CommandHandler_Update(void)
{

	UpdateAlarmLed();

	if(screenRefresh != 0 )
	{
		ShowCurrentScreen();
		screenRefresh = 0;
	}
	return HandleInput();
}

static void ShowCurrentScreen(void)
{

	switch (currentScreen)
	{
		case MAIN_MENU_SCREEN:
			UI_ShowMainMenuScreen();
			break;

		case HELP_SCREEN:
			UI_ShowHelpScreen();
			break;

		case STATUS_SCREEN:
			UI_ShowStatusScreen(isDoorOpened, isAlarmOn);
			break;

		case ALARM_CONTROL_SCREEN:
			UI_ShowAlarmControlScreen(isAlarmOn);
			break;

		case DOOR_CONTROL_SCREEN:
			UI_ShowDoorControlScreen(isDoorOpened);
			break;

		default:
			currentScreen = MAIN_MENU_SCREEN;
			break;
	}

}

static CommandResult HandleInput(void)
{

	uint8_t rxChar;

	if(HAL_UART_Receive(&huart2,&rxChar,1,10) == HAL_OK)
	{
		return HandleRecievedCharacter(rxChar);
	}

	return COMMAND_RESULT_NONE;

}

static CommandResult HandleRecievedCharacter(uint8_t rxChar)
{
	if(rxChar == '\r')
	{
		return HandleCommand();
	}

	AddCharToBuffer(rxChar);

	return COMMAND_RESULT_NONE;
}

static CommandResult HandleCommand(void)
{
	UART_SendString("\r\n");

	commandBuffer[commandBufferIndex] = '\0';

	CommandResult result = ExecuteCommand();

	ClearCommandBuffer();

	return result;
}

static void AddCharToBuffer(uint8_t rxChar)
{
	if(commandBufferIndex >= (COMMAND_BUFFER_SIZE - 1U))
	{
		ReEnterCommand();
		return;

	}

	commandBuffer[commandBufferIndex] = (char)rxChar;
	commandBufferIndex++;

	HAL_UART_Transmit(&huart2,&rxChar,1,HAL_MAX_DELAY);
}

static void ClearCommandBuffer(void)
{
	commandBufferIndex = 0;
	memset(commandBuffer,0,sizeof(commandBuffer));
}

static CommandResult ExecuteCommand(void)
{

	if(strcmp(commandBuffer, "help") == 0)
	{
		screenRefresh = 1;
		currentScreen = HELP_SCREEN;
		return COMMAND_RESULT_NONE;
	}
	if(strcmp(commandBuffer, "back") == 0)
	{
		screenRefresh = 1;
		currentScreen = MAIN_MENU_SCREEN;
		return COMMAND_RESULT_NONE;
	}

	if(strcmp(commandBuffer, "status") == 0)
	{
		screenRefresh = 1;
		currentScreen = STATUS_SCREEN;
		return COMMAND_RESULT_NONE;
	}

	if(strcmp(commandBuffer, "door") == 0)
	{
		screenRefresh = 1;
		currentScreen = DOOR_CONTROL_SCREEN;

		return COMMAND_RESULT_NONE;
	}

	if(strcmp(commandBuffer, "alarm") == 0)
	{
		screenRefresh = 1;
		currentScreen = ALARM_CONTROL_SCREEN;

		return COMMAND_RESULT_NONE;
	}

	if(strcmp(commandBuffer, "lock") == 0)
	{
		SetDoorState(0U);
		SetAlarmState(0U);

		return COMMAND_RESULT_LOCK;
	}

	 if(currentScreen == DOOR_CONTROL_SCREEN)
	 {
	      HandleDoorControlCommand();

	      return COMMAND_RESULT_NONE;
	 }

	 if(currentScreen == ALARM_CONTROL_SCREEN)
	 {
	 	     HandleAlarmControlCommand();

	 	     return COMMAND_RESULT_NONE;
	 }

	 ReEnterCommand();

	return COMMAND_RESULT_NONE;
}

static void HandleDoorControlCommand(void)
{
	if(strcmp(commandBuffer, "open") == 0)
	{
		SetDoorState(1U);
		screenRefresh = 1;

		return;
	}

	if(strcmp(commandBuffer, "close") == 0)
	{
		SetDoorState(0U);
		screenRefresh = 1;

		return;
	}

	ReEnterCommand();

}

static void SetDoorState(uint8_t opened)
{
	isDoorOpened = opened;

	if(isDoorOpened != 0U)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}
}

static void HandleAlarmControlCommand(void)
{
	if(strcmp(commandBuffer, "on") == 0)
		{
		    SetAlarmState(1U);
			screenRefresh = 1;

			return;
		}

		if(strcmp(commandBuffer, "off") == 0)
		{
			SetAlarmState(0U);
			screenRefresh = 1;

			return;
		}

		ReEnterCommand();
}

static void SetAlarmState(uint8_t alarmOn)
{
	isAlarmOn = alarmOn;

	if(isAlarmOn != 0U)
	{
		HAL_GPIO_WritePin(ALARM_LED_GPIO_Port, ALARM_LED_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ALARM_LED_GPIO_Port, ALARM_LED_Pin, GPIO_PIN_RESET);
	}
}

static void UpdateAlarmLed(void)
{
	uint32_t currentTime = HAL_GetTick();

	if(isAlarmOn == 0U)
	{
		return;
	}

	if((currentTime - lastAlarmBlinkTime ) >= ALARM_BLINK_INTERVAL_MS)
	{
		lastAlarmBlinkTime = currentTime;

		HAL_GPIO_TogglePin(ALARM_LED_GPIO_Port, ALARM_LED_Pin);
	}
}

static void ReEnterCommand(void)
{
	UART_SendString("\r\nPlease enter valid command\r\n");
	ClearCommandBuffer();
	UART_ShowPrompt();
}
