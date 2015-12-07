/*
 * function.c
 *
 *  Created on: 2015-12-3
 *      Author: wy
 */
#include "../inc/function.h"

/*------GREEN LED------*/
void GREEN_LED_ON(alt_u16 delay , alt_u8 mode){//ÑÓ³Ùdelay ms
	alt_u16 led_data,led_code;
	switch(mode){
		case 0: for(led_data=0;led_data<8;led_data++){
					led_code = 0x01<<led_data;
					IOWR_ALTERA_AVALON_PIO_DATA(LEDGREEN_BASE,led_code);
					usleep(delay*1000);
				}break;
		case 1: for(led_data=0;led_data<8;led_data++){
					led_code = 0x08>>led_data;
					IOWR_ALTERA_AVALON_PIO_DATA(LEDGREEN_BASE,led_code);
					usleep(delay*1000);
				}break;
		default:
			led_code=0x00;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDGREEN_BASE,led_code);
		break;
	}
}
void GREEN_LED_OFF(){
	IOWR_ALTERA_AVALON_PIO_DATA(LEDGREEN_BASE,0x00);
}
/*------RED LED------*/
void RED_LED_ON(alt_u16 delay , alt_u8 mode){
	alt_32 led_data,led_code;
	switch(mode){
	case 0:for(led_data=0;led_data<18;led_data++){
				led_code=0x0001<<led_data;
				IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,led_code);
				usleep(delay*1000);
			}
			for(led_data=0;led_data<18;led_data++){
				led_code=0x020000>>led_data;
				IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,led_code);
				usleep(delay*1000);
			}break;
	//}//break;
	case 1:
		led_code=0x01;
		for(led_data=0;led_data<9;led_data++){
			led_code=led_code<<2;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,led_code);
			usleep(delay*1000);
		}
		led_code=0x02;
		for(led_data=0;led_data<9;led_data++){
			led_code=led_code<<2;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,led_code);
			usleep(delay*1000);
		}		break;
	default:
		led_code=0x00;
		IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,led_code);
		break;
		//break;
	}
}
void RED_LED_OFF(){
	IOWR_ALTERA_AVALON_PIO_DATA(LEDRED_BASE,0x00);
}
/*------Seven seg led display------*/
void SEVEN_SEG_ON(alt_u8 hex_num,alt_u8 display_num){
	alt_u8 seg_code;
	switch(display_num){ //code seg a,b..g
		case 0:seg_code=0x40;break;
		case 1:seg_code=0x79;break;
		case 2:seg_code=0x24;break;
		case 3:seg_code=0x30;break;
		case 4:seg_code=0x19;break;
		case 5:seg_code=0x12;break;
		case 6:seg_code=0x02;break;
		case 7:seg_code=0x78;break;
		case 8:seg_code=0x00;break;
		case 9:seg_code=0x10;break;
		case 10:seg_code=0x08;break;
		case 11:seg_code=0x03;break;
		case 12:seg_code=0x46;break;
		case 13:seg_code=0x21;break;
		case 14:seg_code=0x06;break;
		case 15:seg_code=0x0e;break;
		default:seg_code=0x7f;break;
	}
	switch(hex_num)	{
		case 0:IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE,seg_code);break;
		case 1:IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE,seg_code);break;
		case 2:IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE,seg_code);break;
		case 3:IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE,seg_code);break;
		case 4:IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE,seg_code);break;
		case 5:IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE,seg_code);break;
		default:
			IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE,seg_code);
			IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE,seg_code);
		    IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE,seg_code);
			IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE,seg_code);
			IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE,seg_code);
			IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE,seg_code);break;
			break;
	}
}

void SEVEN_SEG_OFF(){
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE,0x7f);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE,0x7f);
}
/*------LCD DISPLAY------*/
void LCD_WR_CMD(alt_u8 cmd){
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE,0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RW_BASE,0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE,cmd);
	usleep(40);//39us
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE,1);
}
void LCD_WR_DATA(alt_u8 data){
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE,0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,1);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RW_BASE,0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE,data);
	usleep(40);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE,1);
}
void LCD_ON(){
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_ON_BASE,1);//ÆôÓÃLCD
}
void LCD_CLEAR(){
	LCD_WR_CMD(0x01);//Display clear
	usleep(2000);
}
void LCD_INIT(){//Initial LCD DISPLAY
	usleep(15*1000);//Wait 15ms after VCC rise
	LCD_ON();
	LCD_WR_CMD(0x30);
	usleep(5*1000);
	LCD_WR_CMD(0x30);
	usleep(100);
	LCD_WR_CMD(0x30);
	usleep(40);
	LCD_WR_CMD(0x38);//8bits,2-Line,5*8
	usleep(40);
	LCD_WR_CMD(0x08);//Display off
	usleep(40);
	//LCD_WR_CMD(0x01);//Display clear
	//usleep(2000)
	LCD_CLEAR();
	LCD_WR_CMD(0x06);//cursor moving forward,not enable shift
	usleep(40);
	LCD_WR_CMD(0x08);//Display cursor
	usleep(40);
}
void LCD_DISPLAY(alt_u8 line,alt_u8 num,char *data){
	alt_u8 i;
	switch(line){
	case 1: LCD_WR_CMD(0x80 + num);break;
	case 2: LCD_WR_CMD(0xc0 + num);break;
	default:break;
	}
	for(i=0;iNstrlen(data);i++){
		LCD_WR_DATA(data[i]);
		usleep(2000);
	}
}


