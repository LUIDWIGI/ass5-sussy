#ifndef __LEDPWM_H_
#define __LEDPWM_H_

#include "timer_f.h"
#include "xtmrctr.h"
#include "xstatus.h"

/* ==================================================================== */
/* function: rgbled_Init                                                */
/*                                                                      */
/* description: initialises the RGB LED connected to pwm1(R), pwm2 (G)  */
/*              and pwm3 (B) at a given width each. The repetition      */
/*              frequency of the PWM signals can be set using the       */
/*              freq argument.                                          */
/*                                                                      */
/* pre:  freq – repetition frequency of the PWM signals in Hz.          */
/*              The range of frequencies is 100 Hz – 2 kHz.             */
/*       width – default width of the 3 channels in %.                  */
/*                                                                      */
/* post: returns XST_FAILURE if initting 1 of the LED fails             */
/* ==================================================================== */
int rgbled_Init(unsigned int freq, u8 width);

/* ================================================================= */
/* function: rgbled_setPWMWidths                                     */
/*                                                                   */
/* description: sets the PWM widths for each of the channels of the  */
/*              RGB LED.                                             */
/*                                                                   */
/* pre: rWidth – width of the R channel in %.                        */
/*      gWidth – width of the G channel in %.                        */
/*      bWidth – width of the B channel in %.                        */
/*                                                                   */
/* post: none                                                        */
/* ================================================================= */
void rgbled_setPWMWidths(u8 rWidth, u8 gWidth, u8 bWidth);

#endif
