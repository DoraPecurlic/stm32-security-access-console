#include "security_system.h"
#include "uart_console.h"
#include "ui_screens.h"
#include "command_handler.h"
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <ui_screens.h>

extern UART_HandleTypeDef huart2;

#define MAX_FAILED_ATTEMPTS 3
#define LOCK_TIME_MS 30000
#define BLINKING_SPEED_MS 50

#define BUTTON_REQUIRED_PRESS 3
#define BUTTON_CONF_TIME_MS 10000
#define BUTTON_DEBOUNCE_MS 200

#define PASSWORD_BUFFER_SIZE   20


typedef enum
{
	WAIT_PASSWORD,
	CHECK_PASSWORD,
	WAIT_BUTTON_CONFIRMATION,
	AUTHENTICATED,
	LOCKED
}State;

//Private variables
static uint8_t rxChar;
static char star = '*';

static char passwordBuffer[PASSWORD_BUFFER_SIZE];
static uint8_t passwordIndex = 0;

static const char password[] = "sreckovicKan";

static uint8_t failedAttempts = 0;

static volatile uint8_t buttonPressCount = 0;
static volatile uint8_t buttonConfirmed = 0;
static volatile uint32_t lastButtonInterruptTime = 0;

static uint32_t buttonConfirmationStartTime = 0;

static volatile State state = WAIT_PASSWORD;

//Private functions
static void HandlePasswordInput(void);
static void CheckPassword(void);
static void RegisterFailedAttempt(void);
static void ResetPasswordInput(void);

static void StartButtonConfirmation(void);
static void HandleButtonConfirmation(void);

static void LockSystem(void);

void SecuritySystem_Init(void)
{
	passwordIndex = 0;
	failedAttempts = 0;

	buttonPressCount = 0;
	buttonConfirmed = 0;

	memset(passwordBuffer, 0, sizeof(passwordBuffer));

	state = WAIT_PASSWORD;

	ShowWelcomeScreen();
	UART_SendString("Password: ");
}

void SecuritySystem_Update(void)
{
	 switch (state)
	    {
	        case WAIT_PASSWORD:
	            HandlePasswordInput();
	            break;

	        case CHECK_PASSWORD:
	            CheckPassword();
	            break;

	        case WAIT_BUTTON_CONFIRMATION:
	            HandleButtonConfirmation();
	            break;

	        case AUTHENTICATED:
	        {
	        	CommandResult commandResult = CommandHandler_Update();
	        	if (commandResult == COMMAND_RESULT_LOCK)
	        	{
	        	    ResetPasswordInput();
	        	}

	        	break;
	        }

	        case LOCKED:
	            LockSystem();
	            break;

	        default:
	            ResetPasswordInput();
	            break;
	    }
}

void SecuritySystem_ButtonInterrupt(uint16_t gpioPin)
{
    if(gpioPin != GPIO_PIN_13)
    {
        return;
    }

    uint32_t currentTime = HAL_GetTick();

    if ((currentTime - lastButtonInterruptTime) < BUTTON_DEBOUNCE_MS)
    {
        return;
    }

    lastButtonInterruptTime = currentTime;

    if (state != WAIT_BUTTON_CONFIRMATION)
    {
        return;
    }

    if (buttonPressCount < BUTTON_REQUIRED_PRESS)
    {
        buttonPressCount++;
    }

    if (buttonPressCount == BUTTON_REQUIRED_PRESS)
    {
        buttonConfirmed = 1;
    }
}


static void HandlePasswordInput(void)
{
	HAL_UART_Receive(&huart2,&rxChar,1,HAL_MAX_DELAY);
	if(rxChar == '\r')
	{
		passwordBuffer[passwordIndex] ='\0';

		state = CHECK_PASSWORD;
	}
	else if(passwordIndex < sizeof(passwordBuffer) - 1)
	{
		passwordBuffer[passwordIndex] = rxChar;
		passwordIndex++;

		HAL_UART_Transmit(&huart2,(uint8_t *)&star,1,HAL_MAX_DELAY);

	}
	else
	{
		UART_SendString("\r\nPassword too long\r\n");
		RegisterFailedAttempt();

	}
}

static void RegisterFailedAttempt(void)
{
	failedAttempts++;

	if(failedAttempts < MAX_FAILED_ATTEMPTS )
	{
		ResetPasswordInput();
	}
	else
	{
		state = LOCKED;
	}
}

static void ResetPasswordInput(void)
{
	passwordIndex = 0;
	memset(passwordBuffer,0,sizeof(passwordBuffer));

	ShowWelcomeScreen();
	UART_SendString("Re-enter password: ");

	state = WAIT_PASSWORD;
}

static void LockSystem(void)
{
    uint32_t startTime = HAL_GetTick();
    uint32_t lastDisplayedSecond = UINT32_MAX;
    uint32_t lastBlinkTime = HAL_GetTick();

    char message[60];

    ShowLockScreen();

    while ((HAL_GetTick() - startTime) < LOCK_TIME_MS)
    {
        uint32_t currentTime = HAL_GetTick();
        uint32_t elapsedTime = currentTime - startTime;

        uint32_t remainingSeconds = (LOCK_TIME_MS - elapsedTime + 999U) / 1000U;

        if (remainingSeconds != lastDisplayedSecond)
        {
            lastDisplayedSecond = remainingSeconds;

            snprintf(message, sizeof(message), "\r\033[KLocked: %lu seconds remaining",remainingSeconds);

            UART_SendString(message);
        }

        if ((currentTime - lastBlinkTime)
                >= BLINKING_SPEED_MS)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            lastBlinkTime = currentTime;
        }
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    UART_SendString("\r\n");

    failedAttempts = 0;

    ResetPasswordInput();
}

static void CheckPassword(void)
{
    if (strcmp(password, passwordBuffer) == 0)
    {
    	UART_SendString("\r\nConfirm your identity\r\n");
    	UART_SendString("Press the button 3 times within 10 seconds.\r\n");

        StartButtonConfirmation();
    }
    else
    {
    	UART_SendString("\r\nAccess denied\r\n");
        RegisterFailedAttempt();
    }
}

static void StartButtonConfirmation(void)
{
    buttonPressCount = 0;
    buttonConfirmed = 0;

    lastButtonInterruptTime = HAL_GetTick();
    buttonConfirmationStartTime = HAL_GetTick();

    state = WAIT_BUTTON_CONFIRMATION;
}

static void HandleButtonConfirmation(void)
{
    if (buttonConfirmed != 0)
    {
        buttonConfirmed = 0;


        CommandHandler_Init();

        state = AUTHENTICATED;


        return;
    }

    if ((HAL_GetTick() - buttonConfirmationStartTime) >= BUTTON_CONF_TIME_MS)
    {
    	UART_SendString("\r\nConfirmation failed\r\n");
        RegisterFailedAttempt();
    }
}
