/*
 * security_system.h
 *
 *  Created on: Jul 10, 2026
 *      Author: Dora_
 */

#ifndef INC_SECURITY_SYSTEM_H_
#define INC_SECURITY_SYSTEM_H_

#include <stdint.h>

void SecuritySystem_Init(void);
void SecuritySystem_Update(void);
void SecuritySystem_ButtonInterrupt(uint16_t gpioPin);

#endif /* INC_SECURITY_SYSTEM_H_ */
