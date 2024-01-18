#ifndef __XADC_H_
#define __XADC_H_

#include "xadcps.h"

#define XADC_DEVICE_ID XPAR_XADCPS_0_DEVICE_ID

/****************************************************************************/
/**
*
* Initialise the XADC for measurements
*
* @param	deviceID is a string that specifies the device ID of the XADC
* @param	seqMode is the mode in which the XADC should be reading
*
* @return	An integer that shows if the function failed.
*
*****************************************************************************/
int initXADC(u16 deviceId, u8 seqMode);

/****************************************************************************/
/**
*
* Get the measured data from the XADC.
*
* @param	xadcObj is a reference to the created XADC object.
* @param	The channel the XADC should be measuring.
*
* @return	The data measured by the XADC in volts.
*
*****************************************************************************/
u16 readXADC(u8 xadcChannel);

#endif
