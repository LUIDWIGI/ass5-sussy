#ifndef __INTERRUPTS_H_
#define __INTERRUPTS_H_

#include <stdio.h>
#include "platform.h"
#include "xscugic.h"
#include "xtmrctr.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xtime_l.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xscutimer.h"
#include "xiicps.h"
#include "xil_exception.h"
#include "xstatus.h"
#include "XADC.h"
#include "LUT.h"
#include "LEDPWM.h"

int InitGic(void);

int initSCU(void);

int addSCUTimerToInterrupt(void);

static void myTimerInterruptHandler(void* CallBackRef);

int initInterrupt(void);


#endif
