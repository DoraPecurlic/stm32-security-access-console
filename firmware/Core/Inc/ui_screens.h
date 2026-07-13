/*
 * screens.h
 *
 *  Created on: Jul 11, 2026
 *      Author: Dora_
 */

#ifndef INC_UI_SCREENS_H_
#define INC_UI_SCREENS_H_

#include <stdint.h>

void ShowWelcomeScreen(void);
void ShowLockScreen(void);


void UI_ShowMainMenuScreen(void);
void UI_ShowHelpScreen(void);
void UI_ShowStatusScreen(uint8_t isDoorOpened, uint8_t isAlarmOn);

#endif /* INC_UI_SCREENS_H_ */
