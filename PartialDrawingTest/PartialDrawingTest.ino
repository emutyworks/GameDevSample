#include "Arglib.h"
#include "status.h"

Arduboy arduboy;

void setup() {
  uint8_t pb;

  arduboy.start();
  arduboy.setFrameRate(60);
  SPI.begin();

  /*
   * OLED Partial drawing test
   */
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
      SPI.transfer(0x00);
    }
  }
  
  // Draw (x:89,y:24 -> x:127,y:39)
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(3);    // Setup page start address (y:24)
  SPI.transfer(4);    // Setup page end address (y:39)
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(89);   // Setup column start address (x:89)
  SPI.transfer(127);  // Setup column end address (x:127)
  arduboy.LCDDataMode();
  for(uint8_t i = 0; i < 39 * 2; i++){
    pb = pgm_read_byte_near(b_status + i); // get draw data
    SPI.transfer(pb);                     // set draw data
  }  

  // Draw (x:89,y:48 -> x:127,y:63)
  arduboy.LCDCommandMode();
  SPI.transfer(0x22); // Set Page Address (22h)
  SPI.transfer(6);    // Setup page start address (y:48)
  SPI.transfer(7);    // Setup page end address (y:63)
  SPI.transfer(0x21); // Set Column Address (21h)
  SPI.transfer(89);   // Setup column start address (x:89)
  SPI.transfer(127);  // Setup column end address (x:127)
  arduboy.LCDDataMode();
  for(uint8_t i = 0; i < 39 * 2; i++){
    pb = pgm_read_byte_near(b_status + 78 + i); // get draw data
    SPI.transfer(pb);                          // set draw data
  }
}

void loop() {
  if (!(arduboy.nextFrame())) return;
}
