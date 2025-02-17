#ifndef __MDNIE_TABLE_H__
#define __MDNIE_TABLE_H__

#include "mdnie.h"

/* 2013.06.27 */

static struct mdnie_backlight_value backlight_table[4] = {
	{
		.max = 977,		/*3G/WIFI  BOE LCD SYS REV <= 0x03*/
		.mid = 531,		/*LTE  BOE LCD SYS REV <= 0x02*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1280,		/*3G/WIFI BOE LCD SYS REV >= 0x04*/
		.mid = 700,		/*LTE  BOE LCD SYS REV >= 0x03*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1056,		/*3G/WIFI SDC LCD SYS REV <= 0x03*/
		.mid = 574,		/*LTE SDC LCD SYS REV <= 0x02*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1435,		/* 3G/WIFI SDC LCD SYS REV >= 0x04*/
		.mid = 780,		/* LTE SDC LCD SYS REV >= 0x03*/
		.low = 17,
		.dim = 17,
	}
};

static const unsigned char power_lut[LUT_LEVEL_MAX][LUT_MAX][9] = {
	/* Indoor power look up table */
	{
		{0x42, 0x3d, 0x3E, 0x48, 0x42, 0x3F, 0x3A, 0x37, 0x3F},
		{0x38, 0x3d, 0x34, 0x48, 0x38, 0x35, 0x30, 0x2d, 0x35}
	},
	/* Outdoor power look up table for outdoor 1 (1k~15k) */
	{
		{0x42, 0x47, 0x3E, 0x52, 0x42, 0x3F, 0x3A, 0x37, 0x3F},
		{0x38, 0x3d, 0x34, 0x48, 0x38, 0x35, 0x30, 0x2d, 0x35}
	},
	/* Outdoor power look up table (15k ~) */
	{
		{100, 100, 100, 100, 100, 100, 100, 100, 100},
		{100, 100, 100, 100, 100, 100, 100, 100, 100}
	}
};

static unsigned short tune_ebook[] = {
	/*start KONA ebook cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f5,	/*SCR KgWg*/
	0x00ec, 0x00ef,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_ebook_cabc[] = {
	/*start KONA ebook cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f5,	/*SCR KgWg*/
	0x00ec, 0x00ef,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_email[] = {
	/*start KONA email cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00fe,	/*SCR KgWg*/
	0x00ec, 0x00fe,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_email_cabc[] = {
	/*start KONA email cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00fe,	/*SCR KgWg*/
	0x00ec, 0x00fe,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_camera[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0028,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_ui[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_video[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0080,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_gallery[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0020,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_vt[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00e0,	/*DE pe*/
	0x0093, 0x00e0,	/*DE pf*/
	0x0094, 0x00e0,	/*DE pb*/
	0x0095, 0x00e0,	/*DE ne*/
	0x0096, 0x00e0,	/*DE nf*/
	0x0097, 0x00e0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_ui[] = {
	/*start KONA standard ui cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_video[] = {
	/*start KONA standard video cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_gallery[] = {
	/*start KONA standard gallery cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_vt[] = {
	/*start KONA standard vtcall cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_ui[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_video[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0000,	/*DE pf*/
	0x0094, 0x0000,	/*DE pb*/
	0x0095, 0x0000,	/*DE ne*/
	0x0096, 0x0000,	/*DE nf*/
	0x0097, 0x0000,	/*DE nb*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1004,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_gallery[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_vt[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x002e,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x0040,	/*DE pe*/
	0x0093, 0x0040,	/*DE pf*/
	0x0094, 0x0040,	/*DE pb*/
	0x0095, 0x0040,	/*DE ne*/
	0x0096, 0x0040,	/*DE nf*/
	0x0097, 0x0040,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1204,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_ui_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_video_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0080,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_gallery_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0020,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_vt_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00e0,	/*DE pe*/
	0x0093, 0x00e0,	/*DE pf*/
	0x0094, 0x00e0,	/*DE pb*/
	0x0095, 0x00e0,	/*DE ne*/
	0x0096, 0x00e0,	/*DE nf*/
	0x0097, 0x00e0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_ui_cabc[] = {
	/*start KONA standard ui cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_video_cabc[] = {
	/*start KONA standard video cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_gallery_cabc[] = {
	/*start KONA standard gallery cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_vt_cabc[] = {
	/*start KONA standard vtcall cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_ui_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_video_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0000,	/*DE pf*/
	0x0094, 0x0000,	/*DE pb*/
	0x0095, 0x0000,	/*DE ne*/
	0x0096, 0x0000,	/*DE nf*/
	0x0097, 0x0000,	/*DE nb*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1004,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_gallery_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_vt_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x022e,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x0040,	/*DE pe*/
	0x0093, 0x0040,	/*DE pf*/
	0x0094, 0x0040,	/*DE pb*/
	0x0095, 0x0040,	/*DE ne*/
	0x0096, 0x0040,	/*DE nf*/
	0x0097, 0x0040,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1204,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_browser[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_browser[] = {
	/*start KONA standard browser cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_browser[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_ui[] = {
	/*start KONA auto ui cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_video[] = {
	/*start KONA auto video cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_gallery[] = {
	/*start KONA auto gallery cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_vt[] = {
	/*start KONA auto vtcall cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_browser[] = {
	/*start KONA auto browser cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_camera[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0028,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_browser_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_browser_cabc[] = {
	/*start KONA standard browser cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_browser_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_ui_cabc[] = {
	/*start KONA auto ui cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_video_cabc[] = {
	/*start KONA auto video cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_gallery_cabc[] = {
	/*start KONA auto gallery cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_vt_cabc[] = {
	/*start KONA auto vtcall cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_browser_cabc[] = {
	/*start KONA auto browser cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

struct mdnie_tuning_info tuning_table[CABC_MAX][MODE_MAX][OUTDOOR_MAX][SCENARIO_MAX] = {
	{
		{
		    {
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_video",	tune_dynamic_video},
		    	{"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"camera",		tune_camera},
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_gallery",	tune_dynamic_gallery},
			    {"dynamic_vt",		tune_dynamic_vt},
			    {"dynamic_browser",	tune_dynamic_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    }, {
		        //Outdoor
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"camera",		tune_camera},
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_gallery",	tune_dynamic_gallery},
			    {"dynamic_vt",		tune_dynamic_vt},
			    {"dynamic_browser",	tune_dynamic_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			    }
		},
		{
		    {
			    {"standard_ui",		tune_standard_ui},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"camera",		tune_camera},
			    {"standard_ui",		tune_standard_ui},
			    {"standard_gallery",	tune_standard_gallery},
			    {"standard_vt",		tune_standard_vt},
			    {"standard_browser",	tune_standard_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		        }, {
		        //Outdoor
			    {"standard_ui",		tune_standard_ui},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"camera",		tune_camera},
			    {"standard_ui",		tune_standard_ui},
			    {"standard_gallery",	tune_standard_gallery},
			    {"standard_vt",		tune_standard_vt},
			    {"standard_browser",	tune_standard_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			    }
		},
		{
		    {
			    {"movie_ui",		tune_movie_ui},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"camera",		tune_camera},
			    {"movie_ui",		tune_movie_ui},
			    {"movie_gallery",	tune_movie_gallery},
			    {"movie_vt",		tune_movie_vt},
			    {"movie_browser",	tune_movie_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    }, {
		        //Outdoor
			    {"movie_ui",		tune_movie_ui},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"camera",		tune_camera},
			    {"movie_ui",		tune_movie_ui},
			    {"movie_gallery",	tune_movie_gallery},
			    {"movie_vt",		tune_movie_vt},
			    {"movie_browser",	tune_movie_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			}
		},
		{
		    {
			    {"auto_ui",		tune_auto_ui},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_camera",		tune_auto_camera},
			    {"auto_ui",		tune_auto_ui},
			    {"auto_gallery",	tune_auto_gallery},
			    {"auto_vt",		tune_auto_vt},
			    {"auto_browser",	tune_auto_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    },
		    {
		        //Outdoor
			    {"auto_ui",		tune_auto_ui},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_camera",		tune_auto_camera},
			    {"auto_ui",		tune_auto_ui},
			    {"auto_gallery",	tune_auto_gallery},
			    {"auto_vt",		tune_auto_vt},
			    {"auto_browser",	tune_auto_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			}
		},
		{
		    {
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"camera",			tune_camera},
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_gallery_cabc",	tune_dynamic_gallery_cabc},
			    {"dynamic_vt_cabc",		tune_dynamic_vt_cabc},
			    {"dynamic_browser_cabc",	tune_dynamic_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    },{
		        //Outdoor
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"camera",			tune_camera},
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_gallery_cabc",	tune_dynamic_gallery_cabc},
			    {"dynamic_vt_cabc",		tune_dynamic_vt_cabc},
			    {"dynamic_browser_cabc",	tune_dynamic_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		 {
		    {
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"camera",			tune_camera},
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_gallery_cabc",	tune_standard_gallery_cabc},
			    {"standard_vt_cabc",		tune_standard_vt_cabc},
			    {"standard_browser_cabc",	tune_standard_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    }, {
		        //Outdoor
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"camera",			tune_camera},
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_gallery_cabc",	tune_standard_gallery_cabc},
			    {"standard_vt_cabc",		tune_standard_vt_cabc},
			    {"standard_browser_cabc",	tune_standard_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		{
		    {
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"camera",			tune_camera},
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_gallery_cabc",		tune_movie_gallery_cabc},
			    {"movie_vt_cabc",		tune_movie_vt_cabc},
			    {"movie_browser_cabc",		tune_movie_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    }, {
		        //Outdoor
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"camera",			tune_camera},
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_gallery_cabc",		tune_movie_gallery_cabc},
			    {"movie_vt_cabc",		tune_movie_vt_cabc},
			    {"movie_browser_cabc",		tune_movie_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		{
		    {
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_camera",			tune_auto_camera},
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_gallery_cabc",		tune_auto_gallery_cabc},
			    {"auto_vt_cabc",		tune_auto_vt_cabc},
			    {"auto_browser_cabc",		tune_auto_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    },
		    {
		     //Outdoor
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_camera",			tune_auto_camera},
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_gallery_cabc",		tune_auto_gallery_cabc},
			    {"auto_vt_cabc",		tune_auto_vt_cabc},
			    {"auto_browser_cabc",		tune_auto_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		}
	},
};

#endif /* __MDNIE_TABLE_H__ */
#ifndef __MDNIE_TABLE_H__
#define __MDNIE_TABLE_H__

#include "mdnie.h"

/* 2013.06.27 */

static struct mdnie_backlight_value backlight_table[4] = {
	{
		.max = 977,		/*3G/WIFI  BOE LCD SYS REV <= 0x03*/
		.mid = 531,		/*LTE  BOE LCD SYS REV <= 0x02*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1280,		/*3G/WIFI BOE LCD SYS REV >= 0x04*/
		.mid = 700,		/*LTE  BOE LCD SYS REV >= 0x03*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1056,		/*3G/WIFI SDC LCD SYS REV <= 0x03*/
		.mid = 574,		/*LTE SDC LCD SYS REV <= 0x02*/
		.low = 16,
		.dim = 16,
	}, {
		.max = 1435,		/* 3G/WIFI SDC LCD SYS REV >= 0x04*/
		.mid = 780,		/* LTE SDC LCD SYS REV >= 0x03*/
		.low = 17,
		.dim = 17,
	}
};

static const unsigned char power_lut[LUT_LEVEL_MAX][LUT_MAX][9] = {
	/* Indoor power look up table */
	{
		{0x42, 0x3d, 0x3E, 0x48, 0x42, 0x3F, 0x3A, 0x37, 0x3F},
		{0x38, 0x3d, 0x34, 0x48, 0x38, 0x35, 0x30, 0x2d, 0x35}
	},
	/* Outdoor power look up table for outdoor 1 (1k~15k) */
	{
		{0x42, 0x47, 0x3E, 0x52, 0x42, 0x3F, 0x3A, 0x37, 0x3F},
		{0x38, 0x3d, 0x34, 0x48, 0x38, 0x35, 0x30, 0x2d, 0x35}
	},
	/* Outdoor power look up table (15k ~) */
	{
		{100, 100, 100, 100, 100, 100, 100, 100, 100},
		{100, 100, 100, 100, 100, 100, 100, 100, 100}
	}
};

static unsigned short tune_ebook[] = {
	/*start KONA ebook cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f5,	/*SCR KgWg*/
	0x00ec, 0x00ef,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_ebook_cabc[] = {
	/*start KONA ebook cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f5,	/*SCR KgWg*/
	0x00ec, 0x00ef,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_email[] = {
	/*start KONA email cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00fe,	/*SCR KgWg*/
	0x00ec, 0x00fe,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_email_cabc[] = {
	/*start KONA email cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a0,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00ff,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00fe,	/*SCR KgWg*/
	0x00ec, 0x00fe,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_camera[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0028,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_ui[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_video[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0080,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_gallery[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0020,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_vt[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00e0,	/*DE pe*/
	0x0093, 0x00e0,	/*DE pf*/
	0x0094, 0x00e0,	/*DE pb*/
	0x0095, 0x00e0,	/*DE ne*/
	0x0096, 0x00e0,	/*DE nf*/
	0x0097, 0x00e0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_ui[] = {
	/*start KONA standard ui cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_video[] = {
	/*start KONA standard video cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_gallery[] = {
	/*start KONA standard gallery cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_vt[] = {
	/*start KONA standard vtcall cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_ui[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_video[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0000,	/*DE pf*/
	0x0094, 0x0000,	/*DE pb*/
	0x0095, 0x0000,	/*DE ne*/
	0x0096, 0x0000,	/*DE nf*/
	0x0097, 0x0000,	/*DE nb*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1004,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_gallery[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_vt[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x002e,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x0040,	/*DE pe*/
	0x0093, 0x0040,	/*DE pf*/
	0x0094, 0x0040,	/*DE pb*/
	0x0095, 0x0040,	/*DE ne*/
	0x0096, 0x0040,	/*DE nf*/
	0x0097, 0x0040,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1204,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_ui_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_video_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0080,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_gallery_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0020,	/*DE pe*/
	0x0093, 0x0080,	/*DE pf*/
	0x0094, 0x0080,	/*DE pb*/
	0x0095, 0x0080,	/*DE ne*/
	0x0096, 0x0080,	/*DE nf*/
	0x0097, 0x0080,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_vt_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00e0,	/*DE pe*/
	0x0093, 0x00e0,	/*DE pf*/
	0x0094, 0x00e0,	/*DE pb*/
	0x0095, 0x00e0,	/*DE ne*/
	0x0096, 0x00e0,	/*DE nf*/
	0x0097, 0x00e0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_ui_cabc[] = {
	/*start KONA standard ui cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_video_cabc[] = {
	/*start KONA standard video cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_gallery_cabc[] = {
	/*start KONA standard gallery cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_vt_cabc[] = {
	/*start KONA standard vtcall cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_ui_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_video_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0000,	/*DE pf*/
	0x0094, 0x0000,	/*DE pb*/
	0x0095, 0x0000,	/*DE ne*/
	0x0096, 0x0000,	/*DE nf*/
	0x0097, 0x0000,	/*DE nb*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1004,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_gallery_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_vt_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x022e,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x0040,	/*DE pe*/
	0x0093, 0x0040,	/*DE pf*/
	0x0094, 0x0040,	/*DE pb*/
	0x0095, 0x0040,	/*DE ne*/
	0x0096, 0x0040,	/*DE nf*/
	0x0097, 0x0040,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1204,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_browser[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_browser[] = {
	/*start KONA standard browser cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_browser[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0020,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_ui[] = {
	/*start KONA auto ui cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_video[] = {
	/*start KONA auto video cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_gallery[] = {
	/*start KONA auto gallery cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_vt[] = {
	/*start KONA auto vtcall cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_browser[] = {
	/*start KONA auto browser cabcoff*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x00a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_camera[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0028,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_dynamic_browser_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1a04,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r	 0*/
	0x0021, 0x0b94,	/*CC lut r	16 144*/
	0x0022, 0x18a6,	/*CC lut r	32 160*/
	0x0023, 0x28b8,	/*CC lut r	48 176*/
	0x0024, 0x3ac9,	/*CC lut r	64 192*/
	0x0025, 0x4cd9,	/*CC lut r	80 208*/
	0x0026, 0x5ee7,	/*CC lut r	96 224*/
	0x0027, 0x70f4,	/*CC lut r 112 240*/
	0x0028, 0x82ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_standard_browser_cabc[] = {
	/*start KONA standard browser cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_movie_browser_cabc[] = {
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x0220,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00f6,	/*SCR KgWg*/
	0x00ec, 0x00f2,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_ui_cabc[] = {
	/*start KONA auto ui cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_video_cabc[] = {
	/*start KONA auto video cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0060,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_gallery_cabc[] = {
	/*start KONA auto gallery cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ac,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x0090, 0x0080,	/*DE egth*/
	0x0092, 0x0000,	/*DE pe*/
	0x0093, 0x0060,	/*DE pf*/
	0x0094, 0x0060,	/*DE pb*/
	0x0095, 0x0060,	/*DE ne*/
	0x0096, 0x0060,	/*DE nf*/
	0x0097, 0x0060,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_vt_cabc[] = {
	/*start KONA auto vtcall cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02ae,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0005,	/*FA cs1 de8 hdr2 fa1*/
	0x0039, 0x0080,	/*FA dnrWeight*/
	0x0080, 0x0fff,	/*DNR dirTh*/
	0x0081, 0x19ff,	/*DNR dirnumTh decon7Th*/
	0x0082, 0xff16,	/*DNR decon5Th maskTh*/
	0x0083, 0x0000,	/*DNR blTh*/
	0x0092, 0x00c0,	/*DE pe*/
	0x0093, 0x00c0,	/*DE pf*/
	0x0094, 0x00c0,	/*DE pb*/
	0x0095, 0x00c0,	/*DE ne*/
	0x0096, 0x00c0,	/*DE nf*/
	0x0097, 0x00c0,	/*DE nb*/
	0x0098, 0x1000,	/*DE max ratio*/
	0x0099, 0x0100,	/*DE min ratio*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

static unsigned short tune_auto_browser_cabc[] = {
	/*start KONA auto browser cabcon*/
	0x0000, 0x0000,	/*BANK 0*/
	0x0008, 0x02a8,	/*Dither8 UC4 ABC2 CP1 | CC8 MCM4 SCR2 SCC1 | CS8 DE4 DNR2 HDR1*/
	0x0030, 0x0000,	/*FA cs1 de8 hdr2 fa1*/
	0x00b0, 0x1010,	/*CS hg ry*/
	0x00b1, 0x1010,	/*CS hg gc*/
	0x00b2, 0x1010,	/*CS hg bm*/
	0x00b3, 0x1804,	/*CS weight grayTH*/
	0x00e1, 0xff00,	/*SCR RrCr*/
	0x00e2, 0x00ff,	/*SCR RgCg*/
	0x00e3, 0x00ff,	/*SCR RbCb*/
	0x00e4, 0x00ff,	/*SCR GrMr*/
	0x00e5, 0xff00,	/*SCR GgMg*/
	0x00e6, 0x00ff,	/*SCR GbMb*/
	0x00e7, 0x00ff,	/*SCR BrYr*/
	0x00e8, 0x00f0,	/*SCR BgYg*/
	0x00e9, 0xff00,	/*SCR BbYb*/
	0x00ea, 0x00ff,	/*SCR KrWr*/
	0x00eb, 0x00ff,	/*SCR KgWg*/
	0x00ec, 0x00ff,	/*SCR KbWb*/
	0x0000, 0x0001,	/*BANK 1*/
	0x001f, 0x0080,	/*CC chsel strength*/
	0x0020, 0x0000,	/*CC lut r   0*/
	0x0021, 0x0a82,	/*CC lut r  16 144*/
	0x0022, 0x1693,	/*CC lut r  32 160*/
	0x0023, 0x23a4,	/*CC lut r  48 176*/
	0x0024, 0x32b6,	/*CC lut r  64 192*/
	0x0025, 0x41c8,	/*CC lut r  80 208*/
	0x0026, 0x50da,	/*CC lut r  96 224*/
	0x0027, 0x60ed,	/*CC lut r 112 240*/
	0x0028, 0x71ff,	/*CC lut r 128 255*/
	0x0075, 0x0000,	/*CABC dgain*/
	0x0076, 0x0000,
	0x0077, 0x0000,
	0x0078, 0x0000,
	0x007f, 0x0002,	/*dynamic lcd*/
	0x00ff, 0x0000,	/*Mask Release*/
	/*end*/
	END_SEQ, 0x0000
};

struct mdnie_tuning_info tuning_table[CABC_MAX][MODE_MAX][OUTDOOR_MAX][SCENARIO_MAX] = {
	{
		{
		    {
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_video",	tune_dynamic_video},
		    	{"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"camera",		tune_camera},
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_gallery",	tune_dynamic_gallery},
			    {"dynamic_vt",		tune_dynamic_vt},
			    {"dynamic_browser",	tune_dynamic_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    }, {
		        //Outdoor
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"dynamic_video",	tune_dynamic_video},
			    {"camera",		tune_camera},
			    {"dynamic_ui",		tune_dynamic_ui},
			    {"dynamic_gallery",	tune_dynamic_gallery},
			    {"dynamic_vt",		tune_dynamic_vt},
			    {"dynamic_browser",	tune_dynamic_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			    }
		},
		{
		    {
			    {"standard_ui",		tune_standard_ui},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"camera",		tune_camera},
			    {"standard_ui",		tune_standard_ui},
			    {"standard_gallery",	tune_standard_gallery},
			    {"standard_vt",		tune_standard_vt},
			    {"standard_browser",	tune_standard_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		        }, {
		        //Outdoor
			    {"standard_ui",		tune_standard_ui},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"standard_video",	tune_standard_video},
			    {"camera",		tune_camera},
			    {"standard_ui",		tune_standard_ui},
			    {"standard_gallery",	tune_standard_gallery},
			    {"standard_vt",		tune_standard_vt},
			    {"standard_browser",	tune_standard_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			    }
		},
		{
		    {
			    {"movie_ui",		tune_movie_ui},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"camera",		tune_camera},
			    {"movie_ui",		tune_movie_ui},
			    {"movie_gallery",	tune_movie_gallery},
			    {"movie_vt",		tune_movie_vt},
			    {"movie_browser",	tune_movie_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    }, {
		        //Outdoor
			    {"movie_ui",		tune_movie_ui},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"movie_video",		tune_movie_video},
			    {"camera",		tune_camera},
			    {"movie_ui",		tune_movie_ui},
			    {"movie_gallery",	tune_movie_gallery},
			    {"movie_vt",		tune_movie_vt},
			    {"movie_browser",	tune_movie_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			}
		},
		{
		    {
			    {"auto_ui",		tune_auto_ui},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_camera",		tune_auto_camera},
			    {"auto_ui",		tune_auto_ui},
			    {"auto_gallery",	tune_auto_gallery},
			    {"auto_vt",		tune_auto_vt},
			    {"auto_browser",	tune_auto_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
		    },
		    {
		        //Outdoor
			    {"auto_ui",		tune_auto_ui},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_video",		tune_auto_video},
			    {"auto_camera",		tune_auto_camera},
			    {"auto_ui",		tune_auto_ui},
			    {"auto_gallery",	tune_auto_gallery},
			    {"auto_vt",		tune_auto_vt},
			    {"auto_browser",	tune_auto_browser},
			    {"ebook",		tune_ebook},
			    {"email",		tune_email}
			}
		},
		{
		    {
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"camera",			tune_camera},
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_gallery_cabc",	tune_dynamic_gallery_cabc},
			    {"dynamic_vt_cabc",		tune_dynamic_vt_cabc},
			    {"dynamic_browser_cabc",	tune_dynamic_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    },{
		        //Outdoor
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"dynamic_video_cabc",		tune_dynamic_video_cabc},
			    {"camera",			tune_camera},
			    {"dynamic_ui_cabc",		tune_dynamic_ui_cabc},
			    {"dynamic_gallery_cabc",	tune_dynamic_gallery_cabc},
			    {"dynamic_vt_cabc",		tune_dynamic_vt_cabc},
			    {"dynamic_browser_cabc",	tune_dynamic_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		 {
		    {
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"camera",			tune_camera},
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_gallery_cabc",	tune_standard_gallery_cabc},
			    {"standard_vt_cabc",		tune_standard_vt_cabc},
			    {"standard_browser_cabc",	tune_standard_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    }, {
		        //Outdoor
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"standard_video_cabc",		tune_standard_video_cabc},
			    {"camera",			tune_camera},
			    {"standard_ui_cabc",		tune_standard_ui_cabc},
			    {"standard_gallery_cabc",	tune_standard_gallery_cabc},
			    {"standard_vt_cabc",		tune_standard_vt_cabc},
			    {"standard_browser_cabc",	tune_standard_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		{
		    {
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"camera",			tune_camera},
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_gallery_cabc",		tune_movie_gallery_cabc},
			    {"movie_vt_cabc",		tune_movie_vt_cabc},
			    {"movie_browser_cabc",		tune_movie_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    }, {
		        //Outdoor
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"movie_video_cabc",		tune_movie_video_cabc},
			    {"camera",			tune_camera},
			    {"movie_ui_cabc",		tune_movie_ui_cabc},
			    {"movie_gallery_cabc",		tune_movie_gallery_cabc},
			    {"movie_vt_cabc",		tune_movie_vt_cabc},
			    {"movie_browser_cabc",		tune_movie_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		},
		{
		    {
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_camera",			tune_auto_camera},
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_gallery_cabc",		tune_auto_gallery_cabc},
			    {"auto_vt_cabc",		tune_auto_vt_cabc},
			    {"auto_browser_cabc",		tune_auto_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
		    },
		    {
		     //Outdoor
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_video_cabc",		tune_auto_video_cabc},
			    {"auto_camera",			tune_auto_camera},
			    {"auto_ui_cabc",		tune_auto_ui_cabc},
			    {"auto_gallery_cabc",		tune_auto_gallery_cabc},
			    {"auto_vt_cabc",		tune_auto_vt_cabc},
			    {"auto_browser_cabc",		tune_auto_browser_cabc},
			    {"ebook_cabc",			tune_ebook_cabc},
			    {"email_cabc",			tune_email_cabc}
			}
		}
	},
};

#endif /* __MDNIE_TABLE_H__ */
