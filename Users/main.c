/**************************************
 * File Name  £ºmain.c
 * Description:  read angle data from MT 6813 to STM32C8T6 per PA4 PA5 PA6 PA7         
 *   STd£ºST3.0.0  																										  

*********************************************************/	


#include "stm32f10x.h"                  // Device header
#include "spi_MT6813.h"

#define ReadAngAddr_h 0x8300
#define ReadAngAddr_l 0x8400

//void delay_us(u32 nus);
//void delay_ms(u32 i);

uint16_t Angle_raw;

extern void	SPI_MT6813_Init(void);
int main(void)
{	
  SystemInit();	// Set SYSTEM TICK 72M!?
	SPI_MT6813_Init();
	while(1)
	{	
		Angle_raw = ReadAngle(ReadAngAddr_h, ReadAngAddr_l);	
  }
}

//void delay_us(u32 i)
//{
//    u32 temp;
//    SysTick->LOAD=9*i;         //
//    SysTick->CTRL=0X01;         //
//    SysTick->VAL=0;                //
//    do
//    {
//        temp=SysTick->CTRL;           //
//    }
//    while((temp&0x01)&&(!(temp&(1<<16))));     //
//    SysTick->CTRL=0;    //
//    SysTick->VAL=0;        //
//}	    			


//void delay_ms(u32 i)
//{
//    u32 temp;
//    SysTick->LOAD=900*i;      //, 72MHZ?
//    SysTick->CTRL=0X01;        //
//    SysTick->VAL=0;            //
//    do
//    {
//        temp=SysTick->CTRL;       //
//    }
//    while((temp&0x01)&&(!(temp&(1<<16))));    //
//    SysTick->CTRL=0;    //
//    SysTick->VAL=0;        //
//}







