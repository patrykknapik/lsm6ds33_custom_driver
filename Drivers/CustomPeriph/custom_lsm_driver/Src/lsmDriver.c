/*
 * lsmDriver.c
 *
 *  Created on: 14.04.2018
 *      Author: Patryk Knapik 226302@student.pwr.edu.pl
 */

#include "lsmDriver.h"

LSM_StatusTypeDef LSM_Init(LSM_HandleTypeDef * hlsm) {
	uint8_t reg[2];
	uint8_t res;
	if (HAL_SPI_GetState(hlsm->Init.hspi) != HAL_SPI_STATE_READY) {
		return LSM_SPI_ERROR;
	}
	reg[0] = LSM_WHO_AM_I | 0x80;
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	HAL_SPI_Transmit(hlsm->Init.hspi, reg, 1, 50);
	HAL_SPI_Receive(hlsm->Init.hspi, &res, 1, 50);
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	if (res != LSM_WAI)
		return LSM_WRONG_DEVICE;

	reg[0] = LSM_CTRL3_C;
	reg[1] = 0x05;

	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	if (HAL_SPI_Transmit(hlsm->Init.hspi, reg, 2, 50) != HAL_OK)
		return LSM_SPI_ERROR;
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	HAL_Delay(500);

	reg[0] = LSM_CTRL1_XL;
	reg[1] = hlsm->Init.CTRL1_XL;

	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	HAL_SPI_Transmit(hlsm->Init.hspi, reg, 2, 50);
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	reg[0] = LSM_CTRL2_G;
	reg[1] = hlsm->Init.CTRL2_G;

	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	HAL_SPI_Transmit(hlsm->Init.hspi, reg, 2, 50);
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	reg[0] = LSM_INT1_CTRL;
	reg[1] = hlsm->Init.INT1_CTRL;

	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	HAL_SPI_Transmit(hlsm->Init.hspi, reg, 2, 50);
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	switch (hlsm->Init.CTRL1_XL & ((1 << FS_XL0pos) | (1 << FS_XL1pos))) {
	case XL_FS_2G:
		hlsm->XLscale = 1638;
		break;

	case XL_FS_4G:
		hlsm->XLscale = 819;
		break;

	case XL_FS_8G:
		hlsm->XLscale = 410;
		break;

	case XL_FS_16G:
		hlsm->XLscale = 205;
		break;

	}

	switch (hlsm->Init.CTRL2_G & ((1 << FS_G0pos) | (1 << FS_G1pos))) {

	case G_FS_250DPS:
		hlsm->Gscale = 763;
		break;

	case G_FS_500DPS:
		hlsm->Gscale = 1526;
		break;

	case G_FS_1000DPS:
		hlsm->Gscale = 3052;
		break;

	case G_FS_2000DPS:
		hlsm->Gscale = 6104;
		break;

	}

	if (hlsm->Init.CTRL2_G & (1 << FS125))
		hlsm->Gscale = 381;

	return LSM_OK;
}

LSM_StatusTypeDef LSM_GetWAI(LSM_HandleTypeDef * hlsm, uint8_t * WAI) {
	uint8_t wai_reg = LSM_WHO_AM_I | 0x80;

	if (HAL_SPI_GetState(hlsm->Init.hspi) != HAL_SPI_STATE_READY) {
		return LSM_SPI_ERROR;
	}
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	HAL_SPI_Transmit(hlsm->Init.hspi, &wai_reg, 1, 50);
	HAL_SPI_Receive(hlsm->Init.hspi, WAI, 1, 50);
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);
	return LSM_OK;
}

LSM_StatusTypeDef LSM_GetData(LSM_HandleTypeDef * hlsm, int32_t * data) {
	uint8_t reg = LSM_OUTX_L_G | 0x80;
	uint8_t tmp[12];
	int16_t buffor;

	if (HAL_SPI_GetState(hlsm->Init.hspi) != HAL_SPI_STATE_READY) {
		return LSM_SPI_ERROR;
	}

	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, RESET);
	if (HAL_SPI_Transmit(hlsm->Init.hspi, &reg, 1, 50) != HAL_OK)
		return LSM_SPI_ERROR;
	if (HAL_SPI_Receive(hlsm->Init.hspi, tmp, 12, 200) != HAL_OK)
		return LSM_SPI_ERROR;
	HAL_GPIO_WritePin(hlsm->Init.CS_Port, hlsm->Init.CS_Pin, SET);

	//acc
	buffor = ((tmp[7] << 8) | (tmp[6]));
	data[0] = int16to32(&buffor);
	data[0] = data[0] * 100 / (hlsm->XLscale);

	buffor = ((tmp[9] << 8) | (tmp[8]));
	data[1] = int16to32(&buffor);
	data[1] = data[1] * 100 / (hlsm->XLscale);

	buffor = ((tmp[11] << 8) | (tmp[10]));
	data[2] = int16to32(&buffor);
	data[2] = data[2] * 100 / (hlsm->XLscale);

	//gyro
	buffor = ((tmp[1] << 8) | (tmp[0]));
	data[3] = int16to32(&buffor);
	data[3] = data[3] * (hlsm->Gscale) / 100;

	buffor = ((tmp[3] << 8) | (tmp[2]));
	data[4] = int16to32(&buffor);
	data[4] = data[4] * (hlsm->Gscale) / 100;

	buffor = ((tmp[5] << 8) | (tmp[4]));
	data[5] = int16to32(&buffor);
	data[5] = data[5] * (hlsm->Gscale) / 100;

	return LSM_OK;
}

int32_t int16to32(int16_t * data) {
	int32_t out;
	if (*data < 0) {
		*data = -(*data);
		out = (int32_t) (*data);
		out = -out;
	} else {
		out = (int32_t) (*data);
	}
	return out;
}

bool LSM_isDataReady(LSM_HandleTypeDef * hlsm) {
	bool tmp = hlsm->int1;
	hlsm->int1 = false;
	//TODO check which int is responsible for data if any
	return tmp;
}

inline void LSM_INT1fromISR(LSM_HandleTypeDef * hlsm) {
	hlsm->int1 = true;
}

inline void LSM_INT2fromISR(LSM_HandleTypeDef * hlsm) {
	hlsm->int2 = true;
}
