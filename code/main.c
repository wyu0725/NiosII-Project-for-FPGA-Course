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
#include "../inc/function.h"
#include "sys/alt_irq.h"

//����
char *name = "Wang Yu";
char *ID_Number = "PB12203212";
volatile int Edge_Capture_Key0;
volatile int Edge_Capture_Key1;
volatile int Edge_Capture_Key2;
volatile int Edge_Capture_Key3;

//Function declation
void Key0_Interrupt(void *isr_context);
void Key1_Interrupt(void *isr_context);
void Key2_Interrupt(void *isr_context);
void Key3_Interrupt(void *isr_context);

static void init_button_pio(void)//ͬʱ��Ҫע��������SOPC Builder��ѡ����enable bit-clearing for edge capture register�Ļ�����ô����edge capture��Ӧ����д1���жϣ�����û��ѡ��enable bit-clearing for edge capture register������д���������жϡ����ɺ����ܽᣩ
{

    void* Edge_Capture_ptr0=(void*)&Edge_Capture_Key0;//��дָ��ƥ��alt_irq_register()����ԭ��
    void* Edge_Capture_ptr1=(void*)&Edge_Capture_Key1;
    void* Edge_Capture_ptr2=(void*)&Edge_Capture_Key2;
    void* Edge_Capture_ptr3=(void*)&Edge_Capture_Key3;

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY0_BASE, 1);//ʹ�ܰ���KEY0�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY1_BASE, 1);//ʹ�ܰ���KEY1�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//ʹ��PAUSE�ж�
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//ʹ��RESET�ж�

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE,KEY0_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY1_BASE,KEY1_BIT_CLEARING_EDGE_REGISTER);//���ж�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY2_BASE,KEY2_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY3_BASE,KEY3_BIT_CLEARING_EDGE_REGISTER);//���жϱ�Ե����Ĵ���

	alt_ic_isr_register(KEY0_IRQ_INTERRUPT_CONTROLLER_ID,//�жϿ��������
    		                                 KEY0_IRQ,//Ӳ���жϺ�
    		                          Key0_Interrupt,//�жϷ����Ӻ���
    		                         Edge_Capture_ptr0,//ָ�����豸����ʵ����ص����ݽṹ��
    		                                     0x0);//flags,����δ�ã�ע���жϣ�
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key1_Interrupt,Edge_Capture_ptr1,0x0); //ע���ж�
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key2_Interrupt,Edge_Capture_ptr1,0x0); //ע���ж�
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key3_Interrupt,Edge_Capture_ptr1,0x0); //ע���ж�
}
int main()
{
  printf("Hello from Nios II!\n");

  return 0;
}
void Key0_Interrupt(void *isr_context){

}
