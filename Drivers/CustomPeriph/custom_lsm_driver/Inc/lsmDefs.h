/*
 * lsmDefs.h
 *
 *  Created on: 14.04.2018
 *      Author: Patryk Knapik 226302@student.pwr.edu.pl
 */

#ifndef CUSTOMPERIPH_INC_LSMDEFS_H_
#define CUSTOMPERIPH_INC_LSMDEFS_H_

#define LSM_WAI						0x69U

//registers
#define LSM_FUNC_CFG_ACCESS 		0x01U
#define LSM_ORIENT_CFG_G 			0x0BU
#define LSM_INT1_CTRL 				0x0DU
#define LSM_INT2_CTRL				0x0EU
#define LSM_WHO_AM_I				0x0FU
#define LSM_CTRL1_XL				0x10U
#define LSM_CTRL2_G					0x11U
#define LSM_CTRL3_C					0x12U
#define LSM_CTRL4_C					0x13U
#define LSM_CTRL5_C					0x14U
#define LSM_CTRL6_C					0x15U
#define LSM_CTRL7_G					0x16U
#define LSM_CTRL8_XL				0x17U
#define LSM_CTRL9_XL				0x18U
#define LSM_CTRL10_C				0x19U

#define LSM_OUTX_L_G				0x22U
#define LSM_OUTX_H_G				0x23U
#define LSM_OUTY_L_G				0x24U
#define LSM_OUTY_H_G				0x25U
#define LSM_OUTZ_L_G				0x26U
#define LSM_OUTZ_H_G				0x27U
#define LSM_OUTX_L_XL				0x28U
#define LSM_OUTX_H_XL				0x29U
#define LSM_OUTY_L_XL				0x2AU
#define LSM_OUTY_H_XL				0x2BU
#define LSM_OUTZ_L_XL				0x2CU
#define LSM_OUTZ_H_XL				0x2DU

//bits
#define SignX_Gpos					(5U)
#define SignX_G					(1 << SignX_Gpos)

#define SignY_Gpos					(4U)
#define SignY_G					(1 << SignY_Gpos)

#define SignZ_Gpos					(3U)
#define SignZ_G					(1 << SignZ_Gpos)

#define ODR_XL3pos					(7U)
#define ODR_XL2pos					(6U)
#define ODR_XL1pos					(5U)
#define ODR_XL0pos					(4U)
#define FS_XL1pos					(3U)
#define FS_XL0pos					(2U)
#define BW_XL1pos					(1U)
#define BW_XL0pos					(0U)

typedef enum{
	XL_POWER_DOWN,
	XL_ODR_12_5HZ = (1 << ODR_XL0pos),
	XL_ODR_26HZ = (1 << ODR_XL1pos),
	XL_ODR_52HZ = (1 << ODR_XL0pos) | (1 << ODR_XL1pos),
	XL_ODR_104HZ = (1 << ODR_XL2pos),
	XL_ODR_208HZ = (1 << ODR_XL0pos) | (1 << ODR_XL2pos),
	XL_ODR_416HZ = (1 << ODR_XL1pos) | (1 << ODR_XL2pos),
	XL_ODR_833HZ = (1 << ODR_XL0pos) | (1 << ODR_XL1pos),
	XL_ODR_1_66KHZ = (1 << ODR_XL3pos),
	XL_ODR_3_33KHZ = (1 << ODR_XL0pos) | (1 << ODR_XL3pos),
	XL_ODR_6_66KHZ = (1 << ODR_XL1pos) | (1 << ODR_XL3pos)
}ODR_XL;

typedef enum{
	XL_FS_2G,
	XL_FS_4G = (1 << FS_XL1pos),
	XL_FS_8G = (1 << FS_XL0pos) | (1 << FS_XL1pos),
	XL_FS_16G = (1 << FS_XL0pos)
}FS_XL;

#define INT1_DRDY_XLpos				(0U)
#define INT1_DRDY_XL				(1 << INT1_DRDY_XLpos)

#define INT1_DRDY_Gpos				(1U)
#define INT1_DRDY_G					(1 << INT1_DRDY_Gpos)

#define ODR_G3pos					(7U)
#define ODR_G2pos					(6U)
#define ODR_G1pos					(5U)
#define ODR_G0pos					(4U)
#define FS_G1pos					(3U)
#define FS_G0pos					(2U)
#define FS125						(1U)


typedef enum{
	G_POWER_DOWN,
	G_ODR_12_5HZ = (1 << ODR_G0pos),
	G_ODR_26HZ = (1 << ODR_G1pos),
	G_ODR_52HZ = (1 << ODR_G0pos) | (1 << ODR_G1pos),
	G_ODR_104HZ = (1 << ODR_G2pos),
	G_ODR_208HZ = (1 << ODR_G0pos) | (1 << ODR_G2pos),
	G_ODR_416HZ = (1 << ODR_G1pos) | (1 << ODR_G2pos),
	G_ODR_833HZ = (1 << ODR_G0pos) | (1 << ODR_G1pos) | (1 << ODR_G2pos),
	G_ODR_1_66KHZ = (1 << ODR_G3pos),
}ODR_G;

typedef enum{
	G_FS_125DPS = (1 << FS125),
	G_FS_250DPS = 0,
	G_FS_500DPS = (1 << FS_G1pos),
	G_FS_1000DPS = (1 << FS_G0pos) | (1 << FS_G1pos),
	G_FS_2000DPS = (1 << FS_G0pos)
}FS_G;



#endif /* CUSTOMPERIPH_INC_LSMDEFS_H_ */
