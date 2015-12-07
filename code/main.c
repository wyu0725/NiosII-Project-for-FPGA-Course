/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <IO.h>
#include <time.h>
#include "function.h"
#include "sys/alt_irq.h"

#define ms 1000
//����
char *name = "Wang Yu";
char *ID_Number = "PB12203212";
char *Start = "Hello World!";
char *End = "Designed by WYu";
char *Init_Start = "Start ";
char *Init_End = "initialization";
volatile int Edge_Capture_Key0;
volatile int Edge_Capture_Key1;
volatile int Edge_Capture_Key2;
volatile int Edge_Capture_Key3;

alt_u8 counter = 0,hex_num = 0;
/*
//Get local time
char *wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
time_t timep;
struct tm *p;
time(timep);
*/

//Function declation
void Key0_Interrupt(void *isr_context);
void Key1_Interrupt(void *isr_context);
void Key2_Interrupt(void *isr_context);
void Key3_Interrupt(void *isr_context);

static void Interrupt_Init(void)//ͬʱ��Ҫע��������SOPC Builder��ѡ����enable bit-clearing for edge capture register�Ļ�����ô����edge capture��Ӧ����д1���жϣ�����û��ѡ��enable bit-clearing for edge capture register������д���������жϡ����ɺ����ܽᣩ
{

    void* Edge_Capture_ptr0=(void*)&Edge_Capture_Key0;//��дָ��ƥ��alt_irq_register()����ԭ��
    void* Edge_Capture_ptr1=(void*)&Edge_Capture_Key1;
    void* Edge_Capture_ptr2=(void*)&Edge_Capture_Key2;
    void* Edge_Capture_ptr3=(void*)&Edge_Capture_Key3;

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY0_BASE, 1);//ʹ�ܰ���KEY0�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY1_BASE, 1);//ʹ�ܰ���KEY1�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//ʹ�ܰ���KEY2�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//ʹ�ܰ���KEY3�ж�

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE,KEY0_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY1_BASE,KEY1_BIT_CLEARING_EDGE_REGISTER);//���ж�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY2_BASE,KEY2_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY3_BASE,KEY3_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���

	alt_ic_isr_register(KEY0_IRQ_INTERRUPT_CONTROLLER_ID,//�жϿ��������
											   KEY0_IRQ,//Ӳ���жϺ�
										Key0_Interrupt,//�жϷ����Ӻ���
    		                        Edge_Capture_ptr0,//ָ�����豸����ʵ����ص����ݽṹ��
    		                                    0x0);//flags,����δ��
													//��ע���жϣ�
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key1_Interrupt,Edge_Capture_ptr1,0x0); //ע���ж�
	alt_ic_isr_register(KEY2_IRQ_INTERRUPT_CONTROLLER_ID,KEY2_IRQ,Key2_Interrupt,Edge_Capture_ptr2,0x0); //ע���ж�
	alt_ic_isr_register(KEY3_IRQ_INTERRUPT_CONTROLLER_ID,KEY3_IRQ,Key3_Interrupt,Edge_Capture_ptr3,0x0); //ע���ж�
}
void System_Init(){
	LCD_INIT();
	Interrupt_Init();
	//LCD display Hello World.
	LCD_DISPLAY(1,3,Start);
	LCD_DISPLAY(2,1,End);
	//LED flicker
	GREEN_LED_ON(0,2);
	RED_LED_ON(0,2);
	SEVEN_SEG_ON(6,8);
	usleep(200*ms);
	GREEN_LED_OFF();
	RED_LED_OFF();
	SEVEN_SEG_OFF();
	usleep(200*ms);
	GREEN_LED_ON(0,2);
	RED_LED_ON(0,2);
	SEVEN_SEG_ON(6,8);
	usleep(200*ms);
	GREEN_LED_OFF();
	RED_LED_OFF();
	SEVEN_SEG_OFF();
	usleep(200*ms);
	GREEN_LED_ON(0,2);
	RED_LED_ON(0,2);
	SEVEN_SEG_ON(6,8);
	usleep(200*ms);
	GREEN_LED_OFF();
	RED_LED_OFF();
	SEVEN_SEG_OFF();
	//
	counter = 0;
	hex_num = 0;
}
int main()
{
	System_Init();
	SEVEN_SEG_ON(6,0);
	while(1){
		for(hex_num=0;hex_num<8;hex_num++)
			for(counter=0;counter<10;counter++){
				SEVEN_SEG_ON(hex_num,counter);
				usleep(1000*ms);
			}
	}
  //printf("Hello from Nios II!\n");
  return 0;
}
void Key0_Interrupt(void *isr_context){
	GREEN_LED_ON(500,0);
	usleep(1000*ms);
	GREEN_LED_ON(500,1);
	usleep(1000*ms);
	GREEN_LED_OFF();
}
void Key1_Interrupt(void *isr_context){
	RED_LED_ON(500,0);
	usleep(1000*ms);
	RED_LED_ON(500,1);
	usleep(1000*ms);
	RED_LED_OFF();
}
void Key2_Interrupt(void *isr_context){
	LCD_INIT();
	LCD_DISPLAY(1,4,name);
	LCD_DISPLAY(2,3,ID_Number);
	SEVEN_SEG_OFF();
	usleep(1000*ms);
	//Seven segs display 12203212
	SEVEN_SEG_ON(0,2);
	SEVEN_SEG_ON(1,1);
	SEVEN_SEG_ON(2,2);
	SEVEN_SEG_ON(3,3);
	SEVEN_SEG_ON(4,0);
	SEVEN_SEG_ON(5,2);
	SEVEN_SEG_ON(6,2);
	SEVEN_SEG_ON(7,1);
	usleep(3000*ms);
}
void Key3_Interrupt(void *isr_context){
	SEVEN_SEG_OFF();
	LCD_DISPLAY(1,5,Init_Start);
	LCD_DISPLAY(2,1,Init_End);
	usleep(1000*ms);
	SEVEN_SEG_ON(0,3);
	usleep(1000*ms);
	SEVEN_SEG_ON(0,2);
	usleep(1000*ms);
	SEVEN_SEG_ON(0,1);
	usleep(1000*ms);
	SEVEN_SEG_ON(0,0);
	System_Init();
}
