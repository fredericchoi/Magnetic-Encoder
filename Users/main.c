/**************************************
 * 文件名  ：main.c
 * 描述    ：板子上的LED1闪烁。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0  																										  

*********************************************************/	


#include "stm32f10x.h"                  // Device header

#include "led.h"
#include "spi_MT6813.h"

#define ReadAngAddr_h 0x8300
#define ReadAngAddr_l 0x8400

void delay_us(u32 nus);
void delay_ms(u32 i);

uint8_t Ang_h;
uint8_t Ang_l;

int Angle_raw;
//extern void ReadAngle(void);
uint16_t Angle_HIGH;

extern void	SPI_MT6813_Init(void);
int main(void)
{

	
 SystemInit();	// 配置系统时钟为72M 	
// LED_GPIO_Config(); //LED 端口初始化 
 //SPI_Init_MT();	
	SPI_MT6813_Init();


while(1)
{
	
Angle_HIGH = ReadAngle(ReadAngAddr_h, ReadAngAddr_l);
/*       Angle data fusion:	      */
//			 Angle_temp_h	= SPI_Read(0x03);
//	     Angle_temp_h<<=5;
//			 Angle_temp_l	= SPI_Read(0x04);
//	     MagDet_parity = Angle_temp_l&0x03;
//	     Angle_temp_l >>= 2;
//	     Angle_raw = Angle_temp_h| Angle_temp_l;
//       delay_ms(1);
		
		
// test with LED if programm is running		
//				GPIO_ResetBits(GPIOC,GPIO_Pin_13);			  // PA2输出高电平亮
//		delay_ms(100);
//			GPIO_SetBits(GPIOC,GPIO_Pin_13);	  // 灭
//		delay_ms(100);

  }
}



//void SPI_MT6813_Init(void)
//{
//	
//	
//	
//	SPI_InitTypeDef  SPI_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA,ENABLE );  // Enable both SPI & GPIO!
//	
//	//????,?????,?????
//	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO, ENABLE);
//	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//?JTDO?JTDI?JTCK ????IO?????
//	//GPIOB0 ????IO?????
//	
//	/*SPI: NSS,SCK,MISO and MOSI */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA5--CLK--????
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	//GPIO_StructInit(&GPIO_InitStructure);
//	
//	/* Configure PA6 as encoder input */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//PA6--MISO--??
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	/* PA7*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PA7--MOSI--????
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_CS_Pin_Name;//PB0--CS--????
//	GPIO_Init(GPIO_CS_Pin_Type, &GPIO_InitStructure);
//	
//	/**********SPI****************/
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI1--?????!!
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; // 72Mhz/32 = 2.25Mhz, Mt6813 Maxmum rate 2.5Mhz
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	
//	SPI_Init(SPI1, &SPI_InitStructure);
//	SPI_Cmd(SPI1, ENABLE);

//}


//------------------------------------------




void delay_us(u32 i)
{
    u32 temp;
    SysTick->LOAD=9*i;         //??????, 72MHZ?
    SysTick->CTRL=0X01;         //??,???????,???????
    SysTick->VAL=0;                //?????
    do
    {
        temp=SysTick->CTRL;           //????????
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //??????
    SysTick->CTRL=0;    //?????
    SysTick->VAL=0;        //?????
}	    			


void delay_ms(u32 i)
{
    u32 temp;
    SysTick->LOAD=900*i;      //??????, 72MHZ?
    SysTick->CTRL=0X01;        //??,???????,???????
    SysTick->VAL=0;            //?????
    do
    {
        temp=SysTick->CTRL;       //????????
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    //??????
    SysTick->CTRL=0;    //?????
    SysTick->VAL=0;        //?????
}






///////////////soft spi with GPIO A/////////////////////////////////

/*
void SPI_Init_MT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = SPI_MISO ;			               
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_CSn | SPI_MOSI | SPI_SCK;			       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_CSn_1;
	SPI_SCK_0;
	SPI_MOSI_0;

	delay_ms(50);	
}


void SPI_WrCmd(int cmd)		//spi ???
{
     int i=8;
     SPI_SCK_1;
	 delay_us(SPI_delay);
	
     while(i--)
     {
       if(cmd&0x80)
			 {SPI_MOSI_1;}
       else
			 {SPI_MOSI_0;}

			delay_us(SPI_delay);
			SPI_SCK_0;
			delay_us(SPI_delay);			 
			SPI_SCK_1;
			cmd<<=1;
			delay_us(SPI_delay);
     }		 
		 SPI_MOSI_0;
			delay_us(SPI_delay);		 
}

int SPI_ReCmd(void)		//spi ???
{
	
	int i=8;
	int spi_data=0;
	
	while(i--)
	{
				
		spi_data <<= 1;
		
		delay_us(SPI_delay);		
		SPI_SCK_0;
		delay_us(SPI_delay);
		SPI_SCK_1; 
		
		if(SPI_MISO_READ) 
			spi_data += 1;
		else
			spi_data += 0;
		
	}
	
	return spi_data;
	
}

void SPI_Write(u8 addr,u8	Data)//SPI Write
{
	SPI_CSn_1;
	SPI_CSn_0;
	delay_us(SPI_delay);
	
	SPI_WrCmd(0x7F & addr);delay_us(SPI_delay);
	SPI_WrCmd(Data);
	
	delay_us(SPI_delay);
	SPI_CSn_1;
	
}

int SPI_Read(uint8_t addr)		//SPI Read
{
	int SPI_READ_DATA;
	
	SPI_CSn_1;
	SPI_CSn_0;
	
	delay_us(SPI_delay);
	
	SPI_WrCmd(0x80 | addr);delay_us(SPI_delay);
	SPI_READ_DATA = SPI_ReCmd();
	
	delay_us(SPI_delay);
	SPI_CSn_1;
	
	return SPI_READ_DATA;
}


*/
