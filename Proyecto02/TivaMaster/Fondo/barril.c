#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfa, 0xa0, 0x00, 0x1f, 0x00, 0x1f, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfa, 0xa0, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0xfd, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif