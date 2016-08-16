#include "Arglib.h"

Arduboy arduboy;

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(12);
  SPI.begin();

  // all clear (x:0,y:0 -> x:127,y:63)
  // * Please read 38 page
  // http://www.eimodule.com/download/SSD1306-OLED-Controller.pdf
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(0);    // Setup page start address
  SPI.transfer(7);    // Setup page end address
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(0);    // Setup column start address
  SPI.transfer(127);  // Setup column end address
  arduboy.LCDDataMode();
  for(uint8_t p = 0; p < 8; p++){
    for(uint8_t c = 0; c < 128; c++){
      SPI.transfer(0x00); // set data
    }
  }
  
  // box full (x:0,y:0 -> x:15,y:15)
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(0);    // Setup page start address
  SPI.transfer(1);    // Setup page end address
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(0);   // Setup column start address
  SPI.transfer(15);   // Setup column end address
  arduboy.LCDDataMode();
  for(uint8_t p = 0; p < 2; p++){
    for(uint8_t c = 0; c < 16; c++){
      SPI.transfer(0xff); // set data
    }
  }
  
  // box full (x:60,y:56 -> x:75,y:63)
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(6);    // Setup page start address
  SPI.transfer(7);    // Setup page end address
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(60);   // Setup column start address
  SPI.transfer(75);   // Setup column end address
  arduboy.LCDDataMode();
  for(uint8_t p = 0; p < 2; p++){
    for(uint8_t c = 0; c < 16; c++){
      SPI.transfer(0xff); // set data
    }
  }
  
  // horizontal scroll
  // * Please read 30 page
  // http://www.eimodule.com/download/SSD1306-OLED-Controller.pdf
  arduboy.LCDCommandMode();
  SPI.transfer(0x27);//Left horizontal scroll
  SPI.transfer(0x00);//Dummy byte
  SPI.transfer(0x00);//Define PAGE0 as startpage address
  SPI.transfer(0x03);//Set time interval between each scrolls sleep as 256 frames
  SPI.transfer(0x07);//Define PAGE7 as startpage address
  SPI.transfer(0x00);//Dummy byte
  SPI.transfer(0xff);//Dummy byte
}

void loop()
{
  if (!(arduboy.nextFrame())) return;

  // Deactivate scroll
  // * Please read 31 page
  // http://www.eimodule.com/download/SSD1306-OLED-Controller.pdf
  arduboy.LCDCommandMode();
  SPI.transfer(0x2E);

  /*
   * It rewrites the display while the scroll is stopped
   */
  // (x:61,y:24 -> x:64,y:31)
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(3);    // Setup page start address
  SPI.transfer(3);    // Setup page end address
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(61);   // Setup column start address
  SPI.transfer(64);   // Setup column end address
  arduboy.LCDDataMode();
  // set data
  SPI.transfer(0x00); // x:61
  SPI.transfer(0x00); // x:62
  SPI.transfer(0x00); // x:63
  SPI.transfer(0xff); // x:64

  // Activate scrolling
  // * Please read 31 page
  // http://www.eimodule.com/download/SSD1306-OLED-Controller.pdf
  arduboy.LCDCommandMode();
  SPI.transfer(0x2f);
}
