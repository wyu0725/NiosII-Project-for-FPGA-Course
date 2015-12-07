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

//变量
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

static void init_button_pio(void)//同时需要注意若是在SOPC Builder中选择了enable bit-clearing for edge capture register的话，那么对于edge capture就应该是写1清中断；若是没有选择enable bit-clearing for edge capture register，则是写任意数清中断。（由韩彬总结）
{

    void* Edge_Capture_ptr0=(void*)&Edge_Capture_Key0;//改写指针匹配alt_irq_register()函数原型
    void* Edge_Capture_ptr1=(void*)&Edge_Capture_Key1;
    void* Edge_Capture_ptr2=(void*)&Edge_Capture_Key2;
    void* Edge_Capture_ptr3=(void*)&Edge_Capture_Key3;

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY0_BASE, 1);//使能按键KEY0中断
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY1_BASE, 1);//使能按键KEY1中断
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//使能PAUSE中断
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY2_BASE, 1);//使能RESET中断

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE,KEY0_BIT_CLEARING_EDGE_REGISTER);//清中断边缘捕获寄存器
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY1_BASE,KEY1_BIT_CLEARING_EDGE_REGISTER);//清中断缘捕获寄存器
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY2_BASE,KEY2_BIT_CLEARING_EDGE_REGISTER);//清中断边缘捕获寄存器
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY3_BASE,KEY3_BIT_CLEARING_EDGE_REGISTER);//清中断边缘捕获寄存器

	alt_ic_isr_register(KEY0_IRQ_INTERRUPT_CONTROLLER_ID,//中断控制器标号
    		                                 KEY0_IRQ,//硬件中断号
    		                          Key0_Interrupt,//中断服务子函数
    		                         Edge_Capture_ptr0,//指向与设备驱动实例相关的数据结构体
    		                                     0x0);//flags,保留未用（注册中断）
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key1_Interrupt,Edge_Capture_ptr1,0x0); //注册中断
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key2_Interrupt,Edge_Capture_ptr1,0x0); //注册中断
	alt_ic_isr_register(KEY1_IRQ_INTERRUPT_CONTROLLER_ID,KEY1_IRQ,Key3_Interrupt,Edge_Capture_ptr1,0x0); //注册中断
}
int main()
{
  printf("Hello from Nios II!\n");

  return 0;
}
void Key0_Interrupt(void *isr_context){

}
