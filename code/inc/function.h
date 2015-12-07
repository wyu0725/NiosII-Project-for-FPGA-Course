/*
 * function.h
 *
 *  Created on: 2015-12-3
 *      Author: wy
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "system.h"
#include "unistd.h"
#include "string.h"
#include"alt_types.h"
#include"altera_avalon_pio_regs.h"

void GREEN_LED_ON(alt_u16 delay,alt_u8 mode);
void GREEN_LED_OFF();
void RED_LED_ON(alt_u16 delay,alt_u8 mode);
void RED_LED_OFF();
void SEVEN_SEG_ON(alt_u8 hex_num,alt_u8 display_num);
void SEVEN_SEG_OFF();


#endif /* FUNCTION_H_ */
