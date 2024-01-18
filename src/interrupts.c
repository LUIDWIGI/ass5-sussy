#include "interrupts.h"
#include "xstatus.h"

#define SCU_TIMER_VALUE   (0x8235) // 100ms @ 650MHz/2 (3ns)

static XScuTimer controlTimer;
static XScuGic myGic;
static u16 adcData;
static u8 LEDValues[3] = {0};
static u8* LEDValuesPtr = &LEDValues;

int InitGic(void) {
  XScuGic_Config *gicConfig= NULL;
  int status;

  gicConfig = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
  if (gicConfig == NULL) {status = XST_FAILURE; return status;}

  status = XScuGic_CfgInitialize(&myGic, gicConfig, gicConfig->CpuBaseAddress);
  status = XScuGic_SelfTest(&myGic);
  if (status != XST_SUCCESS){xil_printf("GIC config init failed \r\n"); return XST_FAILURE;}

  Xil_ExceptionInit();
  Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &myGic);

  return XST_SUCCESS;
}

int initSCU(void) {
  XScuTimer_Config *Timer_Config = NULL;
  int status;

  Timer_Config= XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
  if (Timer_Config == NULL) {status = XST_FAILURE; return status;}

  status = XScuTimer_CfgInitialize(&controlTimer, Timer_Config, Timer_Config->BaseAddr);
  if (status != XST_SUCCESS){xil_printf("SCU Timer cfg init failed \r\n"); return status;}

  status = XScuTimer_SelfTest(&controlTimer);
  if (status != XST_SUCCESS){xil_printf("SCU Timer cfg init failed \r\n"); return status;}

  XScuTimer_EnableInterrupt(&controlTimer);
  XScuTimer_EnableAutoReload(&controlTimer);
  XScuTimer_LoadTimer(&controlTimer, SCU_TIMER_VALUE);

  return XST_SUCCESS;
}

int addSCUTimerToInterrupt(void) {
  int status;

  status = XScuGic_Connect(&myGic, XPAR_PS7_SCUTIMER_0_INTR, (Xil_ExceptionHandler) myTimerInterruptHandler, (void *) &controlTimer);
    if (status != XST_SUCCESS) {return XST_FAILURE;}

  XScuGic_Enable(&myGic, XPAR_PS7_SCUTIMER_0_INTR);

  return status;
}

static void myTimerInterruptHandler(void* CallBackRef) {

    XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;
    if( XScuTimer_IsExpired(TimerInstancePtr)) {
      XScuTimer_ClearInterruptStatus(TimerInstancePtr);
    }
  // Dummy delay
    adcData = readXADC(XADCPS_CH_AUX_MIN);
    LEDValuesPtr = readLUT(adcData);
    rgbled_setPWMWidths(LEDValues[0], LEDValues[1], LEDValues[2]);
    //xil_printf("One second has elapsed; SCU Timer interrupt OCCURED \r\n");
}

int initInterrupt(void) {
      // Setup interrupt
      /* Initialise SCUGIC */
      if (InitGic() != XST_SUCCESS) {return XST_FAILURE;}

      /* Initialise SCU Timer */
      if (initSCU() != XST_SUCCESS) {return XST_FAILURE;}

      /* Add SCU Timer to interrupt system */
      if (addSCUTimerToInterrupt() != XST_SUCCESS) {return XST_FAILURE;}

      /* Enable interrupts */
      xil_printf("Enabling interrupts \r\n");
      // Initialise exception handling in the ARM processor
      Xil_ExceptionEnable();
      // Xil_ExceptionDisable(); //disable all interrupts on both CPUs
      /* Start SCU timer */
      XScuTimer_Start(&controlTimer);
      return XST_SUCCESS;
}


