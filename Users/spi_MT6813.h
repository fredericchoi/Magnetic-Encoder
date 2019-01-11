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
	
#ifndef _MT6813_H_
#define _MT6813_H_

#include "stm32f10x.h"



#define GPIO_CS_Pin_Name  GPIO_Pin_4
#define GPIO_CS_Pin_Type  GPIOA


//以下内容一般不需变动
#define SPI_CS_ENABLE  GPIO_ResetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)       //片选脚电平拉低
#define SPI_CS_DISABLE GPIO_SetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)         //片选脚电平拉高
//#define INDEX_ENABLE   GPIO_SetBits(GPIOA, GPIO_Pin_4)/* for incremental signal index */




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
uint16_t ReadAngle(uint16_t regaddr_h, uint16_t regaddr_l);
uint16_t SPIx_ReadWriteByte(uint16_t byte);

//extern void delay_us(u32 nus);
#endif
