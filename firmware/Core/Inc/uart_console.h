/*
 * uart_console.h
 *
 *  Created on: Jul 10, 2026
 *      Author: Dora_
 */

#ifndef INC_UART_CONSOLE_H_
#define INC_UART_CONSOLE_H_


void UART_SendString(const char *text);
void ClearScreen(void);
void ShowWelcomeScreen(void);
void ShowLockScreen(void);
void ShowAuthenticatedScreen(void);

#endif /* INC_UART_CONSOLE_H_ */
