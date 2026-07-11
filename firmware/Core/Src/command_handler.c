/*
 * command-handler.c
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#include "command_handler.h"
#include "ui_screens.h"

#include <stdint.h>

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




//Private functions
static void ShowCurrentScreen(void);



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
	return COMMAND_RESULT_NONE;
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
