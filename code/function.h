/*
 * function.h
 *
 *  Created on: 2015-12-7
 *      Author: wy
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "system.h"
#include "unistd.h"
#include "string.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"

//Function
//Green LED
void GREEN_LED_ON(alt_u16 delay,alt_u8 mode);
void GREEN_LED_OFF();
//Red LED
void RED_LED_ON(alt_u16 delay,alt_u8 mode);
void RED_LED_OFF();
//Seven segs display
void SEVEN_SEG_ON(alt_u8 hex_num,alt_u8 display_num);
void SEVEN_SEG_OFF();
//LCD display
void LCD_WR_CMD(alt_u8 cmd);
void LCD_WR_DATA(alt_u8 data);
void LCD_ON();
void LCD_CLEAR();
void LCD_INIT();
void LCD_DISPLAY(alt_u8 line,alt_u8 num,char *data);

#endif /* FUNCTION_H_ */
