#define S5K4BA_COMPLETE
//#undef S5K4BA_COMPLETE
/*
 * Driver for S5K4BA (UXGA camera) from Samsung Electronics
 * 
 * 1/4" 2.0Mp CMOS Image Sensor SoC with an Embedded Image Processor
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __S5K4BA_H__
#define __S5K4BA_H__

struct s5k4ba_reg {
	unsigned char addr;
	unsigned char val;
};

struct s5k4ba_regset_type {
	unsigned char *regset;
	int len;
};

/*
 * Macro
 */
#define REGSET_LENGTH(x)	(sizeof(x)/sizeof(s5k4ba_reg))

/*
 * User defined commands
 */
/* S/W defined features for tune */
#define REG_DELAY	0xFF00	/* in ms */
#define REG_CMD		0xFFFF	/* Followed by command */

/* Following order should not be changed */
enum image_size_s5k4ba {
	/* This SoC supports upto UXGA (1600*1200) */
#if 0
	QQVGA,	/* 160*120*/
	QCIF,	/* 176*144 */
	QVGA,	/* 320*240 */
	CIF,	/* 352*288 */
	VGA,	/* 640*480 */
#endif
	SVGA,	/* 800*600 */
#if 0
	HD720P,	/* 1280*720 */
	SXGA,	/* 1280*1024 */
	UXGA,	/* 1600*1200 */
#endif
};

/*
 * Following values describe controls of camera
 * in user aspect and must be match with index of s5k4ba_regset[]
 * These values indicates each controls and should be used
 * to control each control
 */
enum s5k4ba_control {
	S5K4BA_INIT,
	S5K4BA_EV,
	S5K4BA_AWB,
	S5K4BA_MWB,
	S5K4BA_EFFECT,
	S5K4BA_CONTRAST,
	S5K4BA_SATURATION,
	S5K4BA_SHARPNESS,
};

#define S5K4BA_REGSET(x)	{	\
	.regset = x,			\
	.len = sizeof(x)/sizeof(s5k4ba_reg),}


/*
 * User tuned register setting values
 */
static unsigned char s5k4ba_init_reg[][2] = {
	{0xfc,0x07},
	{0x66,0x01},    /* Watch Dog Time On */
	{0xfc,0x00},
	{0x00,0xAA},	/* For EDS Check */
	{0x21,0x03},	/* peter0223 */
	{0xfc,0x01},
	{0x04,0x01},	/* ARM Clock Divider */

	{0xfc,0x02},
	{0x30,0x90},	/* Analog offset */
	{0x37,0x0d}, 	/* Global Gain */
	{0x2d,0x48},	/* Double Shutter */
	{0x60,0x00},	/* Blank_Adrs */

	{0x45,0x1e},	/*0e// CDS Timing for Average Sub_Sampling */
	{0x47,0x2f},
	{0x02,0x0e},	/* ADC Resolution */
	{0x3d,0x06},	/* Frame ADLC */
	{0x4d,0x08},	/* Doubler Volatage */
	{0x54,0x02},	/* Double Shutter */
	{0x55,0x1e},	/* Line ADLC */
	{0x56,0x30},	/* */
	{0x59,0x00},	/* LineADLC offset */
	{0x5b,0x08},	/* R_Ref_Ctrl */
	{0x44,0x63},	/* CLP_EN */
	{0x4A,0x10},	/* Clamp Control */
	{0x42,0x02},	/* */
	{0x43,0xef},	/* */

	/*========================================================== */
	/*	Table Set for Sub-Sampling */
	/*========================================================== */
	{0xfc,0x03},
	{0x2c,0x00},	/* crcb_sel for Sub-Sampling Table */
	{0x05,0x46},	/* Output Image Size Set for Capture */
	{0x07,0xb6},
	{0x0e,0x04},
	{0x12,0x03},

	{0xfc,0x04},
	{0x32,0x04},
	{0x33,0xbc},

	{0xfc,0x04},
	{0xc5,0x26},	/* Output Image Size Set for Preview */
	{0xc7,0x5e},
	{0xce,0x04},
	{0xd2,0x04},

	{0xec,0x06},	/*CrCb sel = YCBYCR(0x06) by jsgood */
	{0xc0,0x06},
	{0xc1,0x70},
	{0xc2,0x02},
	{0xc3,0x87},

	{0xfc,0x07},
	{0x05,0x00},
	{0x06,0x00},
	{0x07,0x8b},
	{0x08,0xf5},
	{0x09,0x00},
	{0x0a,0xb4},
	{0x0b,0x00},
	{0x0c,0xea},
	{0x0d,0x00},
	{0x0e,0x40},

	{0xfc,0x00},
	{0x70,0x02},

	/* Jeongyun added still shot cbcr_sel */
	{0xfc,0x03},
	{0x2c,0x00},
	{0x5c,0x00},
	{0x8c,0x00},
	{0xbc,0x00},
	{0xfc,0x04},
	{0x5c,0x00},


	/*========================================================== */
	/*	COMMAND SET */
	/*========================================================== */
	{0xfc,0x00},
	{0x73,0x21},	/* Frmae AE Enable peter */
	{0x20,0x02},	/* Change AWB Mode */

	{0xfc,0x00},
	{0x6c,0xb0},	/* AE target */
	{0x6d,0x00},
	
	{0xfc,0x20},
	{0x16,0x5a},	/* for Prevating AE Hunting */
	
	{0xfc,0x00},
	{0x78,0x6a},	/* AGC Max */
	{0xfc,0x20},
	{0x16,0x60},	/* Frame AE Start */

	{0xfc,0x20},
	{0x57,0x18},	/* Stable_Frame_AE */
	{0x2C,0x30},	/* For Forbidden Area */
	{0x2E,0x00},	/* For Forbidden Area */
	{0x14,0x70},
	{0x01,0x00},	/* Stepless_Off */

	{0xfc,0x07},
	{0x11,0x02},	/* AWB G Gain offset */
	
	{0xfc,0x07},
	{0x3e,0x0a},	/* AWB Cut R max */
	
	{0xfc,0x01},
	{0xc8,0xd0},	/* AWB Y Max e0 */
	{0xfc,0x00},
	{0x3e,0x20},	/*30 AWB Y_min */
	{0x3d,0x10},	/* AWB Y_min Low */
	{0xfc,0x22},
	{0x8c,0x04},	/* AWB Min Y Weight */
	{0x8d,0x16},	/* AWB Max Y Weight */

	{0xfc,0x00},
	{0x32,0x04},	/* AWB moving average 8 frame */
	{0x81,0x10},	/* AWB G gain suppress Disable */
	{0xbc,0xf0},
	
	{0x29,0x04},	/* Y level H */
	{0x2a,0x00},	/* Y level L */
	{0x2b,0x03},	/* color level H */
	{0x2c,0xc8},	/* color level L */
	
	{0xfc,0x07},
	{0x37,0x00},	/* Flicker Add for 32Mhz */
	{0xfc,0x00},
	{0x72,0xa0},	/* Flicker for 32MHz */
	{0x74,0x08},	/* flicker 60Hz Fix */

	{0xfc,0x20},
	{0x02,0x02},	/* Flicker Dgain Mode */
	
	{0xfc,0x00},
	/*{0x23,0x40},  // Mirror Option */
	{0x62,0x0a},	/* Mirror Option	 	 */
	
	{0xfc,0x02},
	{0x4e,0x00},	/* IO current 8mA set */
	{0x4e,0x00},	/* IO current 8mA set */
	{0x4e,0x00},	/* IO current 8mA set */
	{0x4e,0x00},	/* IO current 8mA set */
	{0x4f,0x0a},	/* 2a IO current 48mA set */
	{0x4f,0x0a},	/* IO current 48mA set */
	{0x4f,0x0a},	/* IO current 48mA set */
	{0x4f,0x0a},	/* IO current 48mA set */
	
	{0xfc,0x01},
	{0x0c,0x03},	/* Full YC Enable */
	/*{0x0c,03},	// Full YC Enable */
	/*{0x02,02},	// crcb_sel */
	/*{0x02,02},	// crcb_sel  peter0222 */
	/*{0x01,01},	// pclk      peter0222 */
	/*{0x01,01}, */

	/*========================================================== */
	/*	COLOR MATRIX */
	/*========================================================== */
	{0xfc,0x01},	/* color matrix */
	{0x51,0x0A},
	{0x52,0x42},
	{0x53,0xF9},
	{0x54,0x80},
	{0x55,0x00},
	{0x56,0x3D},

	{0x57,0xFE},
	{0x58,0x0B},
	{0x59,0x06},
	{0x5A,0x9C},
	{0x5B,0xFF},
	{0x5C,0x59},

	{0x5D,0xFF},
	{0x5E,0xD8},
	{0x5F,0xFC},
	{0x60,0x2E},  	
	{0x61,0x07},
	{0x62,0xFA},

	/*========================================================== */
	/*	EDGE ENHANCEMENT */
	/*========================================================== */
	{0xfc,0x00},
	{0x89,0x03},	/* Edge Suppress On */
	{0xfc,0x0b},
	{0x42,0x50},	/* Edge AGC MIN */
	{0x43,0x60},	/* Edge AGC MAX */
	{0x45,0x18},	/* positive gain AGC MIN */
	{0x49,0x0a},	/* positive gain AGC MAX */
	{0x4d,0x18},	/* negative gain AGC MIN */
	{0x51,0x0a},	/* negative gain AGC MAX */
	
	{0xfc,0x05},
	{0x34,0x20},	/* APTCLP */
	{0x35,0x09},	/* APTSC */
	{0x36,0x0b},	/* ENHANCE */
	{0x3f,0x00},	/* NON-LIN */
	{0x42,0x10},	/* EGFALL */
	{0x43,0x00},	/* HLFALL */
	{0x45,0xa0},	/* EGREF */
	{0x46,0x7a},	/* HLREF */
	{0x47,0x40},	/* LLREF */
	{0x48,0x0c},
	{0x49,0x31},	/* CSSEL  EGSEL  CS_DLY */
	
	{0x40,0x41},	/* Y delay */

	/*========================================================== */
	/*	GAMMA */
	/*==========================================================                                                                                                                                         - */
	{0xfc,0x01},

	{0x6F,0x0A},	/* R */
	{0x70,0x1A},
	{0x71,0x7A},
	{0x72,0xF8},
	{0x73,0x00},

	{0x74,0xA0},
	{0x75,0x18},
	{0x76,0x65},
	{0x77,0xAD},
	{0x78,0x6A},

	{0x79,0xE2},
	{0x7A,0x12},
	{0x7B,0x3D},
	{0x7C,0x5A},
	{0x7D,0xBF},

	{0x7E,0x72},
	{0x7F,0x88},
	{0x80,0x9D},
	{0x81,0xB0},
	{0x82,0xFF},

	{0x83,0xC0},
	{0x84,0xCF}, 		
	{0x85,0xDA}, 		
	{0x86,0xFC},

	{0x87,0x08},	/*G */
	{0x88,0x12},
	{0x89,0x42}, 	
	{0x8A,0xBA}, 	
	{0x8B,0x00},

	{0x8C,0x75},
	{0x8D,0xED},
	{0x8E,0x42},
	{0x8F,0x80},
	{0x90,0x5A},

	{0x91,0xB5},
	{0x92,0xE5},
	{0x93,0x10},
	{0x94,0x35},
	{0x95,0xAF},

	{0x96,0x55},
	{0x97,0x70},
	{0x98,0x88},
	{0x99,0x9D},
	{0x9A,0xFF},

	{0x9B,0xB1},
	{0x9C,0xC4},
	{0x9D,0xD5},
	{0x9E,0xFC},

	{0x9F,0x05},	/*B */
	{0xA0,0x18},
	{0xA1,0x42},
	{0xA2,0xd7}, 		
	{0xA3,0x00},

	{0xA4,0xB6},
	{0xA5,0x3b},
	{0xA6,0x88},
	{0xA7,0xC8},
	{0xA8,0x6A},

	{0xA9,0x00},
	{0xAA,0x30},
	{0xAB,0x58},
	{0xAC,0x78},
	{0xAD,0xFF},

	{0xAE,0x90},
	{0xAF,0xA5},
	{0xB0,0xB6},
	{0xB1,0xC5},
	{0xB2,0xFF},

	{0xB3,0xD0},
	{0xB4,0xD6},
	{0xB5,0xDA},
	{0xB6,0xFC},

	/*========================================================== */
	/*	HUE CONTROL */
	/*========================================================== */
	{0xfc,0x00},
	{0x48,0x34},	/* 2000K */
	{0x49,0x34},
	{0x4a,0xf4},
	{0x4b,0x00},
	{0x4c,0x44},
	{0x4d,0x3c},
	{0x4e,0xf0},
	{0x4f,0x0c},
	
	{0x50,0x34},	/* 3000K */
	{0x51,0x34},
	{0x52,0xf4},
	{0x53,0x00},
	{0x54,0x44},
	{0x55,0x3c},
	{0x56,0xf0},
	{0x57,0x0c},
	
	{0x58,0x34},	/* 5100K */
	{0x59,0x30},
	{0x5a,0x00},
	{0x5b,0x04},
	{0x5c,0x40},
	{0x5d,0x2c},
	{0x5e,0xfc},
	{0x5f,0x04},
	/*========================================================== */
	/*	UPPRE0x0x FUNCTION */
	/*========================================================== */
	{0xfc,0x00},
	{0x7e,0xf4},
	
	/*========================================================== */
	/*	BPR */
	/*========================================================== */
	{0xfc,0x01},
	{0x3d,0x10},
	
	{0xfc,0x0b},
	{0x0b,0x00},	/* ISP BPR On start */
	{0x0c,0x20},	/* Th13 AGC Min */
	{0x0d,0x40},	/* Th13 AGC Max */
	{0x0e,0x00},	/* Th1 Max H for AGCMIN */
	{0x0f,0x20},	/* Th1 Max L for AGCMIN */
	{0x10,0x00},	/* Th1 Min H for AGCMAX */
	{0x11,0x10},	/* Th1 Min L for AGCMAX */
	{0x12,0x00},	/* Th3 Max H for AGCMIN */
	{0x13,0x00},	/* Th3 Max L for AGCMIN */
	{0x14,0xff},	/* Th3 Min H for AGCMAX */
	{0x15,0xff},	/* Th3 Min L for AGCMAX */
	{0x16,0x20},	/* Th57 AGC Min */
	{0x17,0x40},	/* Th57 AGC Max */
	{0x18,0x00},	/* Th5 Max H for AGCMIN */
	{0x19,0x00},	/* Th5 Max L for AGCMIN */
	{0x1a,0x00},	/* Th5 Min H for AGCMAX */
	{0x1b,0x20},	/* Th5 Min L for AGCMAX */
	{0x1c,0x00},	/* Th7 Max H for AGCMIN */
	{0x1d,0x00},	/* Th7 Max L for AGCMIN */
	{0x1e,0x00},	/* Th7 Min H for AGCMAX */
	{0x1f,0x20},	/* Th7 Min L for AGCMAX */

	/*========================================================== */
	/*	GR/GB CORRECTION */
	/*========================================================== */
	{0xfc,0x01},
	{0x45,0x0c},   	
	
	{0xfc,0x0b},
	{0x21,0x00},	/* start AGC */
	{0x22,0x18},	/* AGCMIN */
	{0x23,0x58},	/* AGCMAX */
	{0x24,0x0d}, 	/* G Th AGCMIN */
	{0x25,0x30}, 	/* G Th AGCMAX */
	{0x26,0x0d}, 	/* RB Th AGCMIN */
	{0x27,0x30}, 	/* RB Th AGCMAX */
	
	/*========================================================== */
	/*	NR */
	/*========================================================== */
	{0xfc,0x01},
	{0x4C,0x01},	/* NR Enable */
	{0x49,0x15},	/* Sig_Th Mult */
	{0x4B,0x0A},	/* Pre_Th Mult */
	
	{0xfc,0x0b},
	{0x28,0x00},	/* NR start AGC	 */
	{0x29,0x00},	/* SIG Th AGCMIN H */
	{0x2a,0x14},	/* SIG Th AGCMIN L */
	{0x2b,0x00},	/* SIG Th AGCMAX H */
	{0x2c,0x14},	/* SIG Th AGCMAX L */
	{0x2d,0x00},	/* PRE Th AGCMIN H */
	{0x2e,0x90},	/* PRE Th AGCMIN L */
	{0x2f,0x01},	/* PRE Th AGCMAX H */
	{0x30,0x00},	/* PRE Th AGCMAX L */
	{0x31,0x00},	/* POST Th AGCMIN H */
	{0x32,0xa0},	/* POST Th AGCMIN L */
	{0x33,0x01},	/* POST Th AGCMAX H */
	{0x34,0x10},	/* POST Th AGCMAX L */
	
	/*========================================================== */
	/*	1D-Y/C-SIGMA-LPF */
	/*========================================================== */
	{0xfc,0x01},
	{0x05,0xc0},   	
	
	{0xfc,0x0b},
	{0x35,0x00},	/* YLPF start AGC */
	{0x36,0x40},	/* YLPF01 AGCMIN */
	{0x37,0x60},	/* YLPF01 AGCMAX */
	{0x38,0x00},	/* YLPF SIG01 Th AGCMINH */
	{0x39,0x18},	/* YLPF SIG01 Th AGCMINL */
	{0x3a,0x00},	/* YLPF SIG01 Th AGCMAXH */
	{0x3b,0x40},	/* YLPF SIG01 Th AGCMAXH */
	{0x3c,0x50},	/* YLPF02 AGCMIN */
	{0x3d,0x60},	/* YLPF02 AGCMAX */
	{0x3e,0x00},	/* YLPF SIG02 Th AGCMINH */
	{0x3f,0x30},	/* YLPF SIG02 Th AGCMINL */
	{0x40,0x00},	/* YLPF SIG02 Th AGCMAXH */
	{0x41,0x40},	/* YLPF SIG02 Th AGCMAXH */
	{0xd4,0x40},	/* CLPF AGCMIN */
	{0xd5,0x60},	/* CLPF AGCMAX */
	{0xd6,0xb0},	/* CLPF SIG01 Th AGCMIN */
	{0xd7,0xf0},	/* CLPF SIG01 Th AGCMAX */
	{0xd8,0xb0},	/* CLPF SIG02 Th AGCMIN */
	{0xd9,0xf0},	/* CLPF SIG02 Th AGCMAX */

	/*========================================================== */
	/*	COLOR SUPPRESS */
	/*========================================================== */
	{0xfc,0x0b},
	{0x08,0x58},	/* Color suppress AGC MIN */
	{0x09,0x03},	/* Color suppress MIN H */
	{0x0a,0x80},	/* Color suppress MIN L */
	
	/*========================================================== */
	/*	SHADING */
	/*========================================================== */
	{0xfc,0x09},
	 /*Shading file for 3BAFX */
	/*s90000// shading off */
	/* DSP9_SH_WIDTH_H */
	{0x01,0x06},
	{0x02,0x40},
	/* DSP9_SH_HEIGHT_H */
	{0x03,0x04},
	{0x04,0xB0},
	/* DSP9_SH_XCH_R */
	{0x05,0x03},
	{0x06,0x1A},
	{0x07,0x02},
	{0x08,0x4E},
	/* DSP9_SH_XCH_G */
	{0x09,0x03},
	{0x0A,0x27},
	{0x0B,0x02},
	{0x0C,0x11},
	/* DSP9_SH_XCH_B */
	{0x0D,0x03},
	{0x0E,0x15},
	{0x0F,0x01},
	{0x10,0xE3},
	/* DSP9_SH_Del_eH_R */
	{0x1D,0x85},
	{0x1E,0x55},
	{0x1F,0x77},
	{0x20,0x9E},
	{0x23,0x7F},
	{0x24,0xE6},
	{0x21,0x7F},
	{0x22,0xE6},
	/* DSP9_SH_Del_eH_G */
	{0x25,0x82},
	{0x26,0x9A},
	{0x27,0x78},
	{0x28,0xC0},
	{0x2B,0x76},
	{0x2C,0x07},
	{0x29,0x86},
	{0x2A,0x09},
	/* DSP9_SH_Del_eH_B */
	{0x2D,0x85},
	{0x2E,0x55},
	{0x2F,0x75},
	{0x30,0x6D},
	{0x33,0x74},
	{0x34,0xA2},
	{0x31,0x84},
	{0x32,0xA2},
	/* DSP9_SH_VAL_R0H */
	{0x35,0x01},
	{0x36,0x01},
	{0x37,0x01},
	{0x38,0x14},
	{0x39,0x01},
	{0x3A,0x45},
	{0x3B,0x01},
	{0x3C,0x8A},
	{0x3D,0x01},
	{0x3E,0xA3},
	{0x3F,0x01},
	{0x40,0xB9},
	{0x41,0x01},
	{0x42,0xD9},
	{0x43,0x01},
	{0x44,0xF6},
	/* DSP9_SH_VAL_G0H */
	{0x45,0x01},
	{0x46,0x00},
	{0x47,0x01},
	{0x48,0x0E},
	{0x49,0x01},
	{0x4A,0x34},
	{0x4B,0x01},
	{0x4C,0x68},
	{0x4D,0x01},
	{0x4E,0x76},
	{0x4F,0x01},
	{0x50,0x94},
	{0x51,0x01},
	{0x52,0xAB},
	{0x53,0x01},
	{0x54,0xC3},
	/* DSP9_SH_VAL_B0H */
	{0x55,0x01},
	{0x56,0x00},
	{0x57,0x01},
	{0x58,0x0C},
	{0x59,0x01},
	{0x5A,0x2B},
	{0x5B,0x01},
	{0x5C,0x5D},
	{0x5D,0x01},
	{0x5E,0x70},
	{0x5F,0x01},
	{0x60,0x8A},
	{0x61,0x01},
	{0x62,0xA1},
	{0x63,0x01},
	{0x64,0xB3},
	/* DSP9_SH_M_R2_R1H */
	{0x65,0x00},
	{0x66,0x98},
	{0x67,0x2C},
	{0x68,0x02},
	{0x69,0x60},
	{0x6A,0xB0},
	{0x6B,0x05},
	{0x6C,0x59},
	{0x6D,0x8C},
	{0x6E,0x07},
	{0x6F,0x48},
	{0x70,0x1B},
	{0x71,0x09},
	{0x72,0x82},
	{0x73,0xC0},
	{0x74,0x0C},
	{0x75,0x09},
	{0x76,0x7B},
	{0x77,0x0E},
	{0x78,0xDC},
	{0x79,0x4D},
	/* DSP9_SH_M_R2_G1H */
	{0x7A,0x00},
	{0x7B,0xAD},
	{0x7C,0x76},
	{0x7D,0x02},
	{0x7E,0xB5},
	{0x7F,0xD7},
	{0x80,0x06},
	{0x81,0x19},
	{0x82,0x23},
	{0x83,0x08},
	{0x84,0x4C},
	{0x85,0xE2},
	{0x86,0x0A},
	{0x87,0xD7},
	{0x88,0x5C},
	{0x89,0x0D},
	{0x8A,0xB8},
	{0x8B,0x90},
	{0x8C,0x10},
	{0x8D,0xF0},
	{0x8E,0x7F},
	/* DSP9_SH_M_R2_B1H */
	{0x8F,0x00},
	{0x90,0xC1},
	{0x91,0xD0},
	{0x92,0x03},
	{0x93,0x07},
	{0x94,0x3F},
	{0x95,0x06},
	{0x96,0xD0},
	{0x97,0x4F},
	{0x98,0x09},
	{0x99,0x46},
	{0x9A,0x32},
	{0x9B,0x0C},
	{0x9C,0x1C},
	{0x9D,0xFE},
	{0x9E,0x0F},
	{0x9F,0x54},
	{0xA0,0xB1},
	{0xA1,0x12},
	{0xA2,0xED},
	{0xA3,0x4C},
	/* DSP9_SH_SUB_RR0H */
	{0xA4,0x6B},
	{0xA5,0xAA},
	{0xA6,0x23},
	{0xA7,0xE3},
	{0xA8,0x15},
	{0xA9,0x88},
	{0xAA,0x21},
	{0xAB,0x20},
	{0xAC,0x1C},
	{0xAD,0xB6},
	{0xAE,0x19},
	{0xAF,0x55},
	{0xB0,0x16},
	{0xB1,0xAA},
	/* DSP9_SH_SUB_RG0H */
	{0xB2,0x5E},
	{0xB3,0x74},
	{0xB4,0x1F},
	{0xB5,0x7C},
	{0xB6,0x12},
	{0xB7,0xE4},
	{0xB8,0x1D},
	{0xB9,0x10},
	{0xBA,0x19},
	{0xBB,0x30},
	{0xBC,0x16},
	{0xBD,0x39},
	{0xBE,0x13},
	{0xBF,0xE2},
	/* DSP9_SH_SUB_RB0H */
	{0xC0,0x54},
	{0xC1,0x89},
	{0xC2,0x1C},
	{0xC3,0x2D},
	{0xC4,0x10},
	{0xC5,0xE8},
	{0xC6,0x1A},
	{0xC7,0x02},
	{0xC8,0x16},
	{0xC9,0x8A},
	{0xCA,0x13},
	{0xCB,0xE4},
	{0xCC,0x11},
	{0xCD,0xCC},

	{0x00,0x02},  /* {0xhading on */

	/*========================================================== */
	/*	X-SHADING */
	/*========================================================== */
	{0xfc,0x1B},
	{0x80,0x01},
	{0x81,0x00},
	{0x82,0x4C},
	{0x83,0x00},
	{0x84,0x86},
	{0x85,0x03},
	{0x86,0x5E},
	{0x87,0x00},
	{0x88,0x07},
	{0x89,0xA4},
	{0x90,0x00},
	{0x91,0x12},
	{0x92,0x00},
	{0x93,0x12},
	{0x94,0x00},
	{0x95,0x12},
	{0x96,0x00},
	{0x97,0x12},
	{0x98,0x00},
	{0x99,0x12},
	{0x9A,0x00},
	{0x9B,0x12},
	{0x9C,0x00},
	{0x9D,0x12},
	{0x9E,0x00},
	{0x9F,0x12},
	{0xA0,0x00},
	{0xA1,0x12},
	{0xA2,0x00},
	{0xA3,0x12},
	{0xA4,0x00},
	{0xA5,0x12},
	{0xA6,0x00},
	{0xA7,0x12},
	{0xA8,0x00},
	{0xA9,0x12},
	{0xAA,0x00},
	{0xAB,0x12},
	{0xAC,0x00},
	{0xAD,0x12},
	{0xAE,0x00},
	{0xAF,0x12},
	{0xB0,0x00},
	{0xB1,0x12},
	{0xB2,0x00},
	{0xB3,0x12},
	{0xB4,0x00},
	{0xB5,0x12},
	{0xB6,0x00},
	{0xB7,0x15},
	{0xB8,0x00},
	{0xB9,0x12},
	{0xBA,0x00},
	{0xBB,0x12},
	{0xBC,0x00},
	{0xBD,0x12},
	{0xBE,0x00},
	{0xBF,0x12},
	{0xC0,0x00},
	{0xC1,0x12},
	{0xC2,0x00},
	{0xC3,0x12},
	{0xC4,0x00},
	{0xC5,0x12},
	{0xC6,0x00},
	{0xC7,0x12},
	{0xC8,0x00},
	{0xC9,0x12},
	{0xCA,0x00},
	{0xCB,0x12},
	{0xCC,0x00},
	{0xCD,0x12},
	{0xCE,0x00},
	{0xCF,0x12},
	{0xD0,0x00},
	{0xD1,0x12},
	{0xD2,0x00},
	{0xD3,0x12},
	{0xD4,0x00},
	{0xD5,0x12},
		 /* x-shading temp. correlation factor */
	{0xfc,0x0b},
	{0xda,0x00},	/* t0(3100K) */
	{0xdb,0xac},
	{0xdc,0x01},	/* tc(5100K) */
	{0xdd,0x30},	/* default eeh */
	
	{0xfc,0x00},
	{0x81,0x10}, 	/* xshading tem */
	
	{0xfc,0x1b},
	{0x80,0x01},	/* X-Shading On */

	/*========================================================== */
	/*	AE WINDOW WEIGHT */
	/*========================================================== */
	{0xfc,0x00},
	{0x03,0x4b},	/* AE Suppress On */
	
	{0xfc,0x06},
	{0x01,0x35},	/* UXGA AE Window */
	{0x03,0xc2},
	{0x05,0x48},
	{0x07,0xb8},
	{0x31,0x2a},	/* Subsampling AE Window */
	{0x33,0x61},
	{0x35,0x28},
	{0x37,0x5c},
	{0x39,0x28},
	{0x3B,0x5A},
	{0x3D,0x10},	/* 1c */
	{0x3F,0x44},
	
	{0xfc,0x20},
	{0x60,0x11},
	{0x61,0x11},
	{0x62,0x11},
	{0x63,0x11},
	{0x64,0x11},
	{0x65,0x22},
	{0x66,0x22},
	{0x67,0x11},
	{0x68,0x11},
	{0x69,0x33},
	{0x6a,0x33},
	{0x6b,0x11},
	{0x6c,0x12},
	{0x6d,0x55},
	{0x6e,0x55},
	{0x6f,0x21},
	{0x70,0x13},
	{0x71,0x55},
	{0x72,0x55},
	{0x73,0x31},
	{0x74,0x33},
	{0x75,0x33},
	{0x76,0x33},
	{0x77,0x33},

	/*========================================================== */
	/*	SAIT AWB */
	/*========================================================== */
	/*================================= */
	/* White Point */
	/*================================= */
	{0xfc,0x22},	/* White Point (For Hue Control & MWB) */
	{0x01,0xD0},	/* D65 */
	{0x03,0x9B},
	{0x05,0xC0},	/* 5000K */
	{0x07,0xB8},
	{0x09,0xA7},	/* CWF */
	{0x0b,0xDC},
	{0x0d,0x98},	/* 3000K */
	{0x0f,0xE0},
	{0x11,0x85},	/* A */
	{0x12,0x00},
	{0x13,0xF6},
	{0x15,0x80},	/* 2000K */
	{0x16,0x01},
	{0x17,0x00},

	/*================================= */
	/* Basic Setting */
	/*================================= */
	{0xfc,0x22},
	{0xA0,0x01},
	{0xA1,0x3F},
	{0xA2,0x0E},
	{0xA3,0x65},
	{0xA4,0x07},
	{0xA5,0xF4},
	{0xA6,0x11},
	{0xA7,0xC8},
	{0xA9,0x02},
	{0xAA,0x43},
	{0xAB,0x26},
	{0xAC,0x1F},
	{0xAD,0x02},
	{0xAE,0x2C},
	{0xAF,0x19},
	{0xB0,0x0F},
	
	{0x94,0x3C},
	{0x95,0xCC},
	{0x96,0x5C},
	{0x97,0x4D},
	{0xD0,0xA8},
	{0xD1,0x29},
	{0xD2,0x39},
	{0xD3,0x22},
	{0xD4,0x30},
	{0xDB,0x29},
	{0xDC,0x7E},
	{0xDD,0x22},

	{0xE7,0x00},
	{0xE8,0xca},
	{0xE9,0x00},
	{0xEA,0x62},
	{0xEB,0x00},
	{0xEC,0x00},
	{0xEE,0x97},
	
	/*================================= */
	/* Pixel Filter Setting */
	/*================================= */
	{0xFC,0x07},
	{0x95,0x8F},
	
	{0xfc,0x01},
	{0xD3,0x4B},
	{0xD4,0x00},
	{0xD5,0x38},
	{0xD6,0x00},
	{0xD7,0x60},
	{0xD8,0x00},
	{0xD9,0x4E},
	{0xDA,0x00},
	{0xDB,0x27},
	{0xDC,0x15},
	{0xDD,0x23},
	{0xDE,0xAD},
	{0xDF,0x24},
	{0xE0,0x01},
	{0xE1,0x17},
	{0xE2,0x4A},
	{0xE3,0x36},
	{0xE4,0x40},
	{0xE5,0x40},
	{0xE6,0x40},
	{0xE7,0x40},
	{0xE8,0x30},
	{0xE9,0x3D},
	{0xEA,0x17},
	{0xEB,0x01},

	/*================================= */
	/* Polygon AWB Region Tune */
	/*================================= */
	{0xfc,0x22},
	{0x18,0x00},	/* 1 */
	{0x19,0x5a},
	{0x1a,0xf8},
	{0x1b,0x00},	/* 2 */
	{0x1c,0x59},
	{0x1d,0xCC},
	{0x1e,0x00},	/* 3 */
	{0x1f,0x74},
	{0x20,0xB3},
	{0x21,0x00},	/* 4 */
	{0x22,0x86},
	{0x23,0xA2},
	{0x24,0x00},	/* 5 */
	{0x25,0x94},
	{0x26,0x89},
	{0x27,0x00},	/* 6 */
	{0x28,0xA6},
	{0x29,0x76},
	{0x2A,0x00},	/* 7 */
	{0x2B,0xd0},
	{0x2C,0x5e},
	{0x2D,0x00},	/* 8 */
	{0x2E,0xfa},
	{0x2F,0x47},
	{0x30,0x00},	/* 9 */
	{0x31,0xfD},
	{0x32,0x5D},
	{0x33,0x00},	/* 10 */
	{0x34,0xBB},
	{0x35,0x7c},
	{0x36,0x00},	/* 11 */
	{0x37,0xAD},
	{0x38,0x88},
	{0x39,0x00},	/* 12 */
	{0x3A,0x9A},
	{0x3B,0xA3},
	{0x3C,0x00},	/* 13 */
	{0x3D,0x7C},
	{0x3E,0xDD},
	{0x3F,0x00},	/* 14 */
	{0x40,0x00},
	{0x41,0x00},

	/*================================= */
	/* Moving Equation Weight */
	/*================================= */
	{0xfc,0x22},
	{0x98,0x07},

	/*================================= */
	/* EIT Threshold */
	/*================================= */
	{0xfc,0x22},
	{0xb1,0x00},  	/* {0xunny */
	{0xb2,0x03},
	{0xb3,0x00},
	{0xb4,0xc1},
	
	{0xb5,0x00},	/* Cloudy */
	{0xb6,0x05},
	{0xb7,0xc9},
	{0xb9,0x81},
	
	{0xd7,0x00},	/* Shade */
	{0xd8,0x35},
	{0xd9,0x20},
	{0xda,0x81},

	/*================================= */
	/* Gain Offset */
	/*================================= */
	{0xfc,0x00},
	{0x79,0xF9},
	{0x7A,0x02},	/* Global AWB gain off{0xet */
	
	{0xfc,0x22},
	{0x58,0xf6}, 	/* D65 R Off{0xet */
	{0x59,0xff}, 	/* D65 B Off{0xet */
	{0x5A,0xfa}, 	/* 5000K R Off{0xet */
	{0x5B,0xFe}, 	/* 5000K B Off{0xet */
	{0x5C,0xfb}, 	/* CWF R Off{0xet */
	{0x5D,0xFe}, 	/* CWF B Off{0xet */
	{0x5E,0xfb},	/* 3000K R Off{0xet */
	{0x5F,0xFb},	/* 3000K B Off{0xet */
	{0x60,0xfb},	/* A R Off0xet */
	{0x61,0xfb},	/* A B Off0xet */
	{0x62,0xfb}, 	/* 2000K R Off0xet */
	{0x63,0xfb}, 	/* 2000K B Off0xet */
	
	{0xde,0x00},	/* LARGE OBJECT BUG FIX */
	{0xf0,0x6a},	/* RB Ratio */
	/*================================= */
	/* Green Stablity Enhance */
	/*================================= */
	{0xfc,0x22},
	{0xb9,0x00},
	{0xba,0x00},
	{0xbb,0x00},
	{0xbc,0x00},
	{0xe5,0x01},
	{0xe6,0xff},

	{0xbd,0x90},

	/*========================================================== */
	/*	Special Effect */
	/*========================================================== */
	{0xfc,0x07},	/* Special Effect */
	{0x30,0xc0},
	{0x31,0x20},
	{0x32,0x40},
	{0x33,0xc0},
	{0x34,0x00},
	{0x35,0xb0},

	{0xfc,0x00},
	{0x73,0x21},	/* Frame AE Enable */

	{0xfc,0x04},
	{0xc0,0x06},
	{0xc1,0x70},
	{0xFF,0xFF}	/* REGISTER END */
};

#define S5K4BA_INIT_REGS	(sizeof(s5k4ba_init_reg) / sizeof(s5k4ba_init_reg[0]))

/*
 * EV bias
 */

static const struct s5k4ba_reg s5k4ba_ev_m6[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_m5[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_m4[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_m3[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_m2[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_m1[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_default[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p1[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p2[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p3[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p4[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p5[] = {
};

static const struct s5k4ba_reg s5k4ba_ev_p6[] = {
};

#ifdef S5K4BA_COMPLETE
/* Order of this array should be following the querymenu data */
static const unsigned char *s5k4ba_regs_ev_bias[] = {
	(unsigned char *)s5k4ba_ev_m6, (unsigned char *)s5k4ba_ev_m5,
	(unsigned char *)s5k4ba_ev_m4, (unsigned char *)s5k4ba_ev_m3,
	(unsigned char *)s5k4ba_ev_m2, (unsigned char *)s5k4ba_ev_m1,
	(unsigned char *)s5k4ba_ev_default, (unsigned char *)s5k4ba_ev_p1,
	(unsigned char *)s5k4ba_ev_p2, (unsigned char *)s5k4ba_ev_p3,
	(unsigned char *)s5k4ba_ev_p4, (unsigned char *)s5k4ba_ev_p5,
	(unsigned char *)s5k4ba_ev_p6,
};

/*
 * Auto White Balance configure
 */
static const struct s5k4ba_reg s5k4ba_awb_off[] = {
};

static const struct s5k4ba_reg s5k4ba_awb_on[] = {
};

static const unsigned char *s5k4ba_regs_awb_enable[] = {
	(unsigned char *)s5k4ba_awb_off,
	(unsigned char *)s5k4ba_awb_on,
};

/*
 * Manual White Balance (presets)
 */
static const struct s5k4ba_reg s5k4ba_wb_tungsten[] = {

};

static const struct s5k4ba_reg s5k4ba_wb_fluorescent[] = {

};

static const struct s5k4ba_reg s5k4ba_wb_sunny[] = {

};

static const struct s5k4ba_reg s5k4ba_wb_cloudy[] = {

};

/* Order of this array should be following the querymenu data */
static const unsigned char *s5k4ba_regs_wb_preset[] = {
	(unsigned char *)s5k4ba_wb_tungsten,
	(unsigned char *)s5k4ba_wb_fluorescent,
	(unsigned char *)s5k4ba_wb_sunny,
	(unsigned char *)s5k4ba_wb_cloudy,
};

/*
 * Color Effect (COLORFX)
 */
static const struct s5k4ba_reg s5k4ba_color_sepia[] = {
};

static const struct s5k4ba_reg s5k4ba_color_aqua[] = {
};

static const struct s5k4ba_reg s5k4ba_color_monochrome[] = {
};

static const struct s5k4ba_reg s5k4ba_color_negative[] = {
};

static const struct s5k4ba_reg s5k4ba_color_sketch[] = {
};

/* Order of this array should be following the querymenu data */
static const unsigned char *s5k4ba_regs_color_effect[] = {
	(unsigned char *)s5k4ba_color_sepia,
	(unsigned char *)s5k4ba_color_aqua,
	(unsigned char *)s5k4ba_color_monochrome,
	(unsigned char *)s5k4ba_color_negative,
	(unsigned char *)s5k4ba_color_sketch,
};

/*
 * Contrast bias
 */
static const struct s5k4ba_reg s5k4ba_contrast_m2[] = {
};

static const struct s5k4ba_reg s5k4ba_contrast_m1[] = {
};

static const struct s5k4ba_reg s5k4ba_contrast_default[] = {
};

static const struct s5k4ba_reg s5k4ba_contrast_p1[] = {
};

static const struct s5k4ba_reg s5k4ba_contrast_p2[] = {
};

static const unsigned char *s5k4ba_regs_contrast_bias[] = {
	(unsigned char *)s5k4ba_contrast_m2,
	(unsigned char *)s5k4ba_contrast_m1,
	(unsigned char *)s5k4ba_contrast_default,
	(unsigned char *)s5k4ba_contrast_p1,
	(unsigned char *)s5k4ba_contrast_p2,
};

/*
 * Saturation bias
 */
static const struct s5k4ba_reg s5k4ba_saturation_m2[] = {
};

static const struct s5k4ba_reg s5k4ba_saturation_m1[] = {
};

static const struct s5k4ba_reg s5k4ba_saturation_default[] = {
};

static const struct s5k4ba_reg s5k4ba_saturation_p1[] = {
};

static const struct s5k4ba_reg s5k4ba_saturation_p2[] = {
};

static const unsigned char *s5k4ba_regs_saturation_bias[] = {
	(unsigned char *)s5k4ba_saturation_m2,
	(unsigned char *)s5k4ba_saturation_m1,
	(unsigned char *)s5k4ba_saturation_default,
	(unsigned char *)s5k4ba_saturation_p1,
	(unsigned char *)s5k4ba_saturation_p2,
};

/*
 * Sharpness bias
 */
static const struct s5k4ba_reg s5k4ba_sharpness_m2[] = {
};

static const struct s5k4ba_reg s5k4ba_sharpness_m1[] = {
};

static const struct s5k4ba_reg s5k4ba_sharpness_default[] = {
};

static const struct s5k4ba_reg s5k4ba_sharpness_p1[] = {
};

static const struct s5k4ba_reg s5k4ba_sharpness_p2[] = {
};

static const unsigned char *s5k4ba_regs_sharpness_bias[] = {
	(unsigned char *)s5k4ba_sharpness_m2,
	(unsigned char *)s5k4ba_sharpness_m1,
	(unsigned char *)s5k4ba_sharpness_default,
	(unsigned char *)s5k4ba_sharpness_p1,
	(unsigned char *)s5k4ba_sharpness_p2,
};
#endif /* S5K4BA_COMPLETE */

#endif
