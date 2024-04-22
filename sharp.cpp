#include "sharp.h"

static Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, DISPLAY_WIDTH, DISPLAY_HEIGHT); 
OlivometerDisplay::OlivometerDisplay(){
  ;
}
void OlivometerDisplay::begin(){
  display.begin();
  display.clearDisplay();
  delay(1000);
}
void OlivometerDisplay::drawLogo(const unsigned char* image){
  for (int y = 0; y < 33; y++) {
    for (int x = 0; x < 240; x++) {
      int index = (y * 240 + x) / 8;
      int bitOffset = 7 - (x % 8);
      // Extract the pixel value from the image array
      unsigned char pixel = (image[index] >> bitOffset) & 0x01;
      if (pixel == 1) {
        display.drawPixel(x, y, BLACK); // Set pixel on
      } else {
        display.drawPixel(x, y, WHITE); // Set pixel off
      }
    }
  }
  display.refresh();
}
void OlivometerDisplay::drawTable(int matrix[][8]){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setRotation(3);
  display.setCursor(0,0);
  drawLogo(olivometerLogo);
  display.setCursor(columnCursors[0], 50); display.print("f nm"); 
  display.setCursor(columnCursors[1], 50); display.print("Accesso");
  display.setCursor(columnCursors[2], 50); display.print("Spento");
  display.drawLine(0, 65,DISPLAY_WIDTH, 65, BLACK);

  uint16_t h_cursor = 80;
  for(size_t i = 0; i < 8; ++i){
    display.setCursor(columnCursors[0]+10, h_cursor); display.print(wavelengths[i]); 
    display.setCursor(columnCursors[1]+10, h_cursor); display.print(matrix[0][i]);
    display.setCursor(columnCursors[2], h_cursor); display.println(matrix[1][i]);
    h_cursor += 20;
  }  
}
void OlivometerDisplay::refreshScreen(){
  display.refresh();
}
void OlivometerDisplay::drawTime(String gps_time){
  ;}
