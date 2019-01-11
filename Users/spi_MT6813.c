<<<<<<< HEAD
/**
  ******************************************************************************
  * @file    spi_MT6813.c
  * @author  fredericchoi	
  * @version V0.0.1
  * @date    10-JUA-2019
  * @brief   This file contains the headers of the spi_MT6813.
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2019</center></h2>
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "spi_MT6813.h"

void SPI_MT6813_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,ENABLE );
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO, ENABLE);

	/*SPI: NSS,SCK,MISO and MOSI */
	//SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA5--CLK--
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//GPIO_StructInit(&GPIO_InitStructure);
	
	/* Configure PA6 as encoder input */
	//MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//PA6--MISO--Input
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA7 - MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA7--MOSI--AF!!!
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//CSN-NSS
	GPIO_InitStructure.GPIO_Pin = GPIO_CS_Pin_Name;//PB0--CS
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PA7--MOSI
	GPIO_Init(GPIO_CS_Pin_Type, &GPIO_InitStructure);
	
	/**********SPI****************/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI1--
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;  // send everytime 8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;   // 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  //MT 6813 requires Mode 3
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //72M/8 = 9Mhz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}


/* read and write a byte of 8bits data, read+ write = 16 bits*/
uint16_t SPIx_ReadWriteByte(uint16_t byte)
{
  uint16_t retry = 0;
	while( (SPI1->SR&1<<1) == 0 )//���ͻ������ǿ�
	{
		if( ++retry > 200 )
			return 0 ;//�ӳ�һ��ʱ��󷵻�
	}
	SPI1->DR = byte;     //��������
	
	retry = 0;
	while( (SPI1->SR&1<<0) == 0 ) //���ջ�����Ϊ��
	{
		if( ++retry > 200 )
			return 0;//�ӳ�һ��ʱ��󷵻�
	}
	return SPI1->DR;          //��һ�»����������־
}

/*put two bytes data togather and data fusion*/
uint16_t ReadAngle(uint16_t regaddr_h, uint16_t regaddr_l)
{
	
		uint8_t Angle_h = 0;
		uint8_t Angle_l = 0;
		uint16_t ang_raw = 0;
	
		SPI_CS_ENABLE;
	  Angle_h =(uint8_t) SPIx_ReadWriteByte(regaddr_h);	  // read high byte 0x03
		SPI_CS_DISABLE;

	  SPI_CS_ENABLE;
	  Angle_l = (uint8_t)SPIx_ReadWriteByte(regaddr_l);  // read low byte 0x04
		SPI_CS_DISABLE;
	  ang_raw = ((uint16_t)Angle_l >> 2 | (uint16_t)Angle_h << 6);  // put two bytes data to one, see user manual MT6813
	
	  return ang_raw;
}

=======
/**
  ******************************************************************************
  * @file    spi_TLE5012B.c
  * @author  Keith Cheung
  * @version V3.5.0
  * @date    13-MAY-2017
  * @brief   This file contains the headers of the spi_TLE5012B.
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2017</center></h2>
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "spi_MT6813.h"
//#include "PublicSet.h"

//uint16_t TLE_Angle,Angle_Speed,TLE_Offset_Angle;

//spi_TLE5012B.H ���м�Ҫ˵��

void Delay( uint16_t i )
{
   while( i-- );
}


void SPI_MT6813_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,ENABLE );
	
//	//���¶��䣬������������������ʹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO, ENABLE);
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//ʹJTDO��JTDI��JTCK ������ͨIO�ڽ��в���
	//GPIOB0 ������ͨIO�ڽ��в���
	
	/*SPI: NSS,SCK,MISO and MOSI */
	//SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA5--CLK--��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//GPIO_StructInit(&GPIO_InitStructure);
	
	/* Configure PA6 as encoder input */
	//MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//PA6--MISO--����
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA7 - MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA7--MOSI--�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//CSN-NSS
	GPIO_InitStructure.GPIO_Pin = GPIO_CS_Pin_Name;//PB0--CS--�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PA7--MOSI--�������
	GPIO_Init(GPIO_CS_Pin_Type, &GPIO_InitStructure);
//	SPI_CS_DISABLE;
	
	/**********SPI****************/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI1--˫��ȫ˫������
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;  // send everytime 8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;   // 
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   // Mode 3 for 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  //1
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //72M/8 = 9Mhz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}


//uint16_t SPIx_ReadWriteByte(uint16_t byte)
//{
//	uint16_t retry = 0;
//	while( (SPI1->SR&1<<1) == 0 )//���ͻ������ǿ�
//	{
//		if( ++retry > 200 )
//			return 0;//�ӳ�һ��ʱ��󷵻�
//	}
//	SPI1->DR = byte;     //��������
//	
//	retry = 0;
//	while( (SPI1->SR&1<<0) == 0 ) //���ջ�����Ϊ��
//	{
//		if( ++retry > 200 )
//			return 0;//�ӳ�һ��ʱ��󷵻�
//	}
//	return SPI1->DR;          //��һ�»����������־
//}


uint16_t SPIx_ReadWriteByte(uint16_t byte)
{
  uint16_t retry = 0;
	while( (SPI1->SR&1<<1) == 0 )//���ͻ������ǿ�
	{
		if( ++retry > 200 )
			return 0 ;//�ӳ�һ��ʱ��󷵻�
	}
	SPI1->DR = byte;     //��������
	
	retry = 0;
	while( (SPI1->SR&1<<0) == 0 ) //���ջ�����Ϊ��
	{
		if( ++retry > 200 )
			return 0;//�ӳ�һ��ʱ��󷵻�
	}
	return SPI1->DR;          //��һ�»����������־
}

//�õ� 0~359 ��
//uint16_t ReadAngle(void)
//{
//	return ( ReadValue(READ_ANGLE_VALUE) * 360 / 0x10000 );
//}
uint16_t ReadAngle(uint16_t regaddr_h, uint16_t regaddr_l)
{
	
	 uint8_t Angle_h = 0;
	 uint8_t Angle_l = 0;
	 uint16_t Angle_raw = 0;

//	 
		SPI_CS_ENABLE;
	  Angle_h =(uint8_t) SPIx_ReadWriteByte(regaddr_h);	
		 Ang_h = Angle_h;

			SPI_CS_DISABLE;
//	 delay_us(1);
	  SPI_CS_ENABLE;
	  Angle_l = (uint8_t)SPIx_ReadWriteByte(regaddr_l);
			 Ang_l = Angle_l;
		SPI_CS_DISABLE;
	 Angle_raw = ((uint16_t)Angle_l >> 2 | (uint16_t)Angle_h << 6);
	return Angle_raw;
}

//�õ����ٶ�
//uint16_t ReadSpeed(void)
//{
//	return ReadValue(READ_SPEED_VALUE);
//}


//uint16_t ReadValue(uint16_t u16RegValue)
//{
//	uint16_t u16Data;

//	SPI_CS_ENABLE;
//	
//	SPIx_ReadWriteByte(u16RegValue);
//  SPI_TX_OFF;
//	
//	//���� 0xFFFF �����õģ�������Ϊ����ʱ��
//	u16Data = ( SPIx_ReadWriteByte(0xffff) & 0x7FFF ) << 1;//0x12/0xff*100k
//	
//	SPI_CS_DISABLE;
//  SPI_TX_ON;
//	
//	return(u16Data);
//}

uint8_t ReadValue(uint8_t u8RegValue)
{
	uint8_t u8Data;

//	SPI_CS_ENABLE;
	
	SPIx_ReadWriteByte(u8RegValue);
//  SPI_TX_OFF;
//	
//	//���� 0xFFFF �����õģ�������Ϊ����ʱ��
//	u8Data = ( SPIx_ReadWriteByte(0xff) & 0x7F ) << 1;//0x12/0xff*100k  // not yet understand
	
	SPI_CS_DISABLE;
//  SPI_TX_ON;
	
	return(u8Data);
}
>>>>>>> 6b95a7df831cf0eb78c4ebebd95d3cf542b52174
