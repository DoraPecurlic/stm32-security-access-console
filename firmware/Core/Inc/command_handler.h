/*
 * command-handler.h
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#ifndef INC_COMMAND_HANDLER_H_
#define INC_COMMAND_HANDLER_H_

typedef enum
{
	COMMAND_RESULT_NONE,
	COMMAND_RESULT_LOCK
}CommandResult;

void CommandHandler_Init(void);
CommandResult CommandHandler_Update(void);

#endif /* INC_COMMAND_HANDLER_H_ */
