/*
 * uart_console.c
 *
 *  Created on: Jul 10, 2026
 *      Author: Dora_
 */
#include "uart_console.h"
#include "main.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

void UART_SendString(const char *text)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)text, strlen(text), HAL_MAX_DELAY);
}

void ClearScreen(void)
{
	UART_SendString("\033[2J\033[3J\033[H"); //reset putty-ja
}

void UART_ShowPrompt(void)
{
    UART_SendString("\r\n> ");
}
