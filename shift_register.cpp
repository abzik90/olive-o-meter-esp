#include "shift_register.h"

ShiftRegister::ShiftRegister() {
  pinMode(DS, OUTPUT);
  pinMode(DSCLK, OUTPUT);
}

void ShiftRegister::begin() {
  Wire.begin();
  ads.begin();
  shiftOutZeros();
}

// Shifts out a specified number of zeroes to the shift register.
void ShiftRegister::shiftOutZeros(int count, int delayTime) {
  for (int i = 0; i < count; i++) {
    digitalWrite(DS, LOW);  // Set data line low (0)
    digitalWrite(DSCLK, HIGH);
    delay(delayTime);
    digitalWrite(DSCLK, LOW);
  }
}

// shifts 1 in the 8-bit shift register 
// i.e: 1000 0000, 0100 0000, 0010 0000, ...
void ShiftRegister::readOlivometer() {
   byte sequential= B10000000;
   for (int bit = 0; bit < 8; ++bit) {
    this->data[0][bit] = (ads.readADC_SingleEnded(0) + ads.readADC_SingleEnded(1) + ads.readADC_SingleEnded(3) + ads.readADC_SingleEnded(4)) / 4; // get the average of all ADC channels
   
    digitalWrite(DS, (sequential >> (7-bit)) & 0x01);
    digitalWrite(DSCLK, HIGH);
    delay(5);  // Adjust delay time as needed
    digitalWrite(DSCLK, LOW);
    this->data[1][bit] = (ads.readADC_SingleEnded(0) + ads.readADC_SingleEnded(1) + ads.readADC_SingleEnded(3) + ads.readADC_SingleEnded(4)) / 4;
  }
}

void ShiftRegister::printData(){
    for(int i = 0; i < 2; ++i){
      for(int j = 0; j < 8; ++j){
        Serial.print(data[i][j]);Serial.print(" ");
      }  
      Serial.println();
    }  
}
