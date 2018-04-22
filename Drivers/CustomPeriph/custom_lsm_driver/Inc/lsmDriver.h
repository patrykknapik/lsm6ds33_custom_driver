/*
 * lsmDriver.h
 *
 *  Created on: 14.04.2018
 *      Author: Patryk Knapik 226302@student.pwr.edu.pl
 */

#ifndef CUSTOMPERIPH_INC_LSMDRIVER_H_
#define CUSTOMPERIPH_INC_LSMDRIVER_H_

#include "lsmDefs.h"
#include "gpio.h"
#include "spi.h"
#include "usbd_cdc_if.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	SPI_HandleTypeDef * hspi;
	GPIO_TypeDef * CS_Port;
	uint16_t CS_Pin;
	uint8_t CTRL1_XL;
	uint8_t CTRL2_G;
	uint8_t INT1_CTRL;
	uint8_t INT2_CTRL;

}LSM_InitTypeDef;

typedef struct{
	LSM_InitTypeDef Init;
	uint16_t x;
	uint16_t y;
	uint16_t z;
	int32_t XLscale;
	int32_t Gscale;
	volatile bool int1;
	volatile bool int2;

}LSM_HandleTypeDef;

typedef enum{
	LSM_OK,
	LSM_NO_DEVICE,
	LSM_WRONG_DEVICE,
	LSM_SPI_ERROR,
	LSM_ERROR
}LSM_StatusTypeDef;

LSM_StatusTypeDef LSM_Init(LSM_HandleTypeDef * hlsm);

LSM_StatusTypeDef LSM_GetWAI(LSM_HandleTypeDef * hlsm, uint8_t * WAI);

LSM_StatusTypeDef LSM_GetData(LSM_HandleTypeDef * hlsm, int32_t * data);

void LSM_INT1fromISR(LSM_HandleTypeDef * hlsm);

void LSM_INT2fromISR(LSM_HandleTypeDef * hlsm);

int32_t int16to32(int16_t * data);

bool LSM_isDataReady(LSM_HandleTypeDef * hlsm);


#endif /* CUSTOMPERIPH_INC_LSMDRIVER_H_ */
