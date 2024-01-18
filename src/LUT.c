#include "LUT.h"

static const u8 LUT[4][3] =
{	{0, 0, 100},
	{0, 50, 50},
	{50, 50, 0},
	{0, 0, 100}	};

static u8 retDuty[3];

u8* readLUT(u16 val) {
	// 65536 amount of numbers in u16
	switch(val) {
	case 0 ... 16383:
	  for (u8 i = 0; i < 3; i++) {
	    retDuty[i] = LUT[1][i];
	  }
	break;

	case 16384 ... 32767:
	  for (u8 i = 0; i < 3; i++) {
	    retDuty[i] = LUT[2][i];
	  }
	break;

	case 32768 ... 49151:
	  for (u8 i = 0; i < 3; i++) {
	    retDuty[i] = LUT[3][i];
	  }
	break;

	default:
	  for (u8 i = 0; i < 3; i++) {
	    retDuty[i] = LUT[4][i];
	  }
	break;
	}
	return (u8*)retDuty;

}

