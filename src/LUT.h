#ifndef __LUT_H_
#define __LUT_H_
#include "xil_types.h"

/****************************************************************************************/
/**
*
* Initialise the XADC for measurements
*
* @param	val is the value that needs to be looked up in the lookup table.
*
* @return	An byte pointer to a array consisting of 3 bytes that contain the RGB value's
*
*****************************************************************************************/
u8* readLUT(u16 val);

#endif
