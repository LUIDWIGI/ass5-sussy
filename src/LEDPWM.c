#include "LEDPWM.h"

u32 period;
XTmrCtr led[3]; // 0 = R, 1 = G, 2 = B

int rgbled_Init(unsigned int freq, u8 width) {
  int status;
  if ((freq < 100) || (freq > 2000)) {
    return XST_FAILURE;
  }
  period = XTC_HZ_TO_NS(freq);
  u32 widthNS = (width / 100) * period;
  for (int i = 0; i < (sizeof(led) / sizeof(XTmrCtr)); i++) {
    status = PwmInit(&led[i], i);
    if (status == XST_FAILURE) {return XST_FAILURE;}
    PwmConfig(&led[i], period, widthNS);
  }
  return XST_SUCCESS;
}

void rgbled_setPWMWidths(u8 rWidth, u8 gWidth, u8 bWidth) {
  u32 rWidthNS, gWidthNS, bWidthNS;
  switch (rWidth) {
  case 0:
    rWidthNS = period / 100;
    break;
  case 100:
    rWidthNS = 99 * period / 100;
    break;
  default:
    rWidthNS = rWidth * period / 100;
    break;
  }
  switch (gWidth) {
  case 0:
    gWidthNS = period / 100;
    break;
  case 100:
    gWidthNS = 99 * period / 100;
    break;
  default:
    gWidthNS = gWidth * period / 100;
    break;
  }
  switch (bWidth) {
  case 0:
    bWidthNS = period / 100;
    break;
  case 100:
    bWidthNS = 99 * period / 100;
    break;
  default:
    bWidthNS = bWidth * period / 100;
    break;
  }
  PwmConfig(&led[0], period, rWidthNS);
  PwmConfig(&led[1], period, gWidthNS);
  PwmConfig(&led[2], period, bWidthNS);
  xil_printf("Configured LED's \r\n");
}
