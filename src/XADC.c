#include "XADC.h"

static XAdcPs XAdcInstPot; /* XADC driver instance */

int initXADC(u16 deviceId, u8 seqMode) {
	int Status;
	XAdcPs_Config *ConfigPtr;
	XAdcPs *XAdcInstPotPtr = &XAdcInstPot;

	ConfigPtr = XAdcPs_LookupConfig(deviceId);
	if (ConfigPtr == NULL) {return XST_FAILURE;}
	XAdcPs_CfgInitialize(XAdcInstPotPtr, ConfigPtr, ConfigPtr->BaseAddress);
	Status = XAdcPs_SelfTest(XAdcInstPotPtr);
	if (Status != XST_SUCCESS) {return XST_FAILURE;}
	//any additional settings changes come here
	XAdcPs_SetSequencerMode(XAdcInstPotPtr, seqMode);
	return XST_SUCCESS;
}

u16 readXADC(u8 xadcChannel) {
	//xil_printf("ADC Read \r\n");
	return XAdcPs_GetAdcData(&XAdcInstPot, xadcChannel);

}


