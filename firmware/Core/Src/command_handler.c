/*
 * command-handler.c
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#include "command_handler.h"
#include "ui_screens.h"
#include "uart_console.h"

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <string.h>


extern UART_HandleTypeDef huart2;

#define COMMAND_BUFFER_SIZE 20U

typedef enum
{
	MAIN_MENU_SCREEN,
	HELP_SCREEN,
	STATUS_SCREEN,
	ALARM_CONTROL_SCREEN,
	DOOR_CONTROL_SCREEN
}CurrentScreen;

//Private variables
static CurrentScreen currentScreen = MAIN_MENU_SCREEN;
static uint8_t screenRefresh = 0;

static char commandBuffer[COMMAND_BUFFER_SIZE];
static uint8_t commandBufferIndex = 0;



//Private functions
static void ShowCurrentScreen(void);
static CommandResult HandleInput(void);
static CommandResult HandleRecievedCharacter(uint8_t rxChar);
static CommandResult HandleCommand();
static void AddCharToBuffer(uint8_t rxChar);
static void ClearCommandBuffer(void);
static CommandResult ExecuteCommand(void);




void CommandHandler_Init(void)
{
	//implementation on init function for command hander -  first screen, buffers, counters, flags in  eneteriing sstate
	currentScreen = MAIN_MENU_SCREEN;

	screenRefresh = 1;

}

CommandResult CommandHandler_Update(void)
{
	//salje securiti sistemu jel korisnik reko da locka ili nije nista njemu reko

	if(screenRefresh != 0 )
	{
		ShowCurrentScreen();
		screenRefresh = 0;
	}
	return HandleInput();
}

static void ShowCurrentScreen(void)
{
	/* function that handels when to show which screen - main handler/state machine for command handler */
	switch (currentScreen)
	{
		case MAIN_MENU_SCREEN:
			UI_ShowMainMenuScreen();
			break;

		case HELP_SCREEN:
			//not implemented yet
			break;

		case STATUS_SCREEN:
			//not implemented yet
			break;

		case ALARM_CONTROL_SCREEN:
			//not implemented yet
			break;

		case DOOR_CONTROL_SCREEN:
			//not implemented yet
			break;

		default:
			currentScreen = MAIN_MENU_SCREEN;
			break;
	}

}

static CommandResult HandleInput(void)
{
	//primi zna ako je primljen posalji ga funkcjiji koja ga dalhe obraduje
	uint8_t rxChar;


	if(HAL_UART_Receive(&huart2,&rxChar,1,HAL_MAX_DELAY) == HAL_OK)
	{
		HandleRecievedCharacter(rxChar);
	}

	return COMMAND_RESULT_NONE;

}

static CommandResult HandleRecievedCharacter(uint8_t rxChar)
{
	//odlucuje sta kad je enter- zovi novu koja obraduje cijelu naredbu unesenu
	//kad je noramlan obican unos slova onda nek zove funkciju koja ce spremit to u buffer
	if(rxChar == '\r')
	{
		return HandleCommand();
	}

	AddCharToBuffer(rxChar);

	return COMMAND_RESULT_NONE;
}
static CommandResult HandleCommand(void)
{
	//ona treba dodat novi red na terminalu
	UART_SendString("\r\n");
	//treba stavit onaj znak na kraj arraya
	commandBuffer[commandBufferIndex] = '\0';
	// treba pozvat execute command koja ce upravljat kako se izvrsava ta komanda unesweran
	CommandResult result = ExecuteCommand();
	//treba ovistit buffer tako da postavi index na 0 i da postavi buffer na sve nule mem - mozda cak mala zasebna funkcija
	ClearCommandBuffer();
	return result;
}
static void AddCharToBuffer(uint8_t rxChar)
{
	if(commandBufferIndex > (COMMAND_BUFFER_SIZE -1U))
	{
		UART_SendString("\r\nCommand too long\r\n");
		ClearCommandBuffer();

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
	//to be implemented :)
	return COMMAND_RESULT_NONE;
}
