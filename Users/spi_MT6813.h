/**
  ******************************************************************************
  * @file    spi_TLE5012B.h 
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
	
#ifndef _TLE5012B_H_
#define _TLE5012B_H_

#include "stm32f10x.h"

//extern uint16_t TLE_Angle, Angle_Speed, TLE_Offset_Angle;
/*
TLE5012B_E1000 ����˵��:

1:NC
2:SCK <= 120R => stm32f103 PA5
3:CSQ (CS) <= 120R => stm32f103 PB0
4:DATA <= 120R => stm32f103 PA6
  DATA <= 120R => stm32f103 PA7
  DATA <= 2.2K => Vdd 3.3V
  PS:�������� SPI , MOSI , MISO ����ʹ��

5:NC
6:Vdd 3.3V
7:GND
8:NC
*/

//���������á������š���Բ�������� ֱ�� 10 x �� 2mm

//SPI5012B_Init() ʱ�����������

//���������谴ʵ�ʸ���
#define SPI_TX_OFF {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0x40000000;}//��PA7��MOSI�����óɿ�©--����ģʽ
#define SPI_TX_ON  {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0xB0000000;}//��PA7��MOSI�����ó�����--���ģʽ��50MHz��

#define GPIO_CS_Pin_Name  GPIO_Pin_4
#define GPIO_CS_Pin_Type  GPIOA

//#define GPIO_CS_Pin_Name  GPIO_Pin_0
//#define GPIO_CS_Pin_Type  GPIOB

//��������һ�㲻��䶯
#define SPI_CS_ENABLE  GPIO_ResetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)       //Ƭѡ�ŵ�ƽ����
#define SPI_CS_DISABLE GPIO_SetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)         //Ƭѡ�ŵ�ƽ����
//#define INDEX_ENABLE   GPIO_SetBits(GPIOA, GPIO_Pin_4)/* for incremental signal index */

//#define CLK_H GPIO_SetBits(GPIOA, GPIO_Pin_5)                 //ʱ�ӽ�PA5��ƽ����
//#define CLK_L GPIO_ResetBits(GPIOA, GPIO_Pin_5)               //ʱ�ӽ�PA5��ƽ����

//#define DATA_H	GPIO_SetBits(GPIOA, GPIO_Pin_6)                         //PA6��MISO����ƽ����
//#define DATA_L	GPIO_ResetBits(GPIOA, GPIO_Pin_6)                       //PA6��MISO����ƽ����
//#define READ_DATA	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

/* SPI command for TLE5012 */
#define READ_STATUS					0x8001			//8000
#define READ_ANGLE_VALUE		0x8021			//8020
#define READ_SPEED_VALUE		0x8031			//8030

#define WRITE_MOD1_VALUE		0x5060							//0_1010_0_000110_0001
#define MOD1_VALUE	0x0001

#define WRITE_MOD2_VALUE		0x5080							//0_1010_0_001000_0001
#define MOD2_VALUE	0x0801

#define WRITE_MOD3_VALUE		0x5091							//0_1010_0_001001_0001
#define MOD3_VALUE	0x0000

#define WRITE_MOD4_VALUE		0x50E0							//0_1010_0_001110_0001
#define MOD4_VALUE	0x0098				//9bit 512

#define WRITE_IFAB_VALUE		0x50B1
#define IFAB_VALUE 0x000D

/* SPI command for MT6813 */
#define READ_ANGLE_H		0x8300
#define READ_ANGLE_L		0x8400


//#define READ_STATUS					0x8001			//8000
//#define READ_ANGLE_VALUE		0x8021			//8020
//#define READ_SPEED_VALUE		0x8031			//8030

//#define WRITE_MOD1_VALUE		0x5060							//0_1010_0_000110_0001
//#define MOD1_VALUE	0x0001

//#define WRITE_MOD2_VALUE		0x5080							//0_1010_0_001000_0001
//#define MOD2_VALUE	0x0801

//#define WRITE_MOD3_VALUE		0x5091							//0_1010_0_001001_0001
//#define MOD3_VALUE	0x0000

//#define WRITE_MOD4_VALUE		0x50E0							//0_1010_0_001110_0001
//#define MOD4_VALUE	0x0098				//9bit 512

//#define WRITE_IFAB_VALUE		0x50B1
//#define IFAB_VALUE 0x000D
/* Functionality mode */
#define REFERESH_ANGLE		0

void SPI_MT6813_Init(void);
void SPI_SendData16(uint16_t SendData);
uint16_t SPI_ReadData16(void);
uint16_t ReadAngle(uint16_t regaddr_h, uint16_t regaddr_l);
//uint16_t ReadSpeed(void);
//uint16_t ReadValue(uint16_t u16Value);
//uint16_t SPIx_ReadWriteByte(uint16_t byte);
uint8_t ReadValue(uint8_t u8RegValue);
uint16_t SPIx_ReadWriteByte(uint16_t byte);
uint16_t TlE5012W_Reg(uint16_t Reg_CMD, uint16_t Reg_Data);


extern int Angle_raw;
extern uint8_t Ang_h;
extern uint8_t Ang_l;
extern void delay_us(u32 nus);
#endif
