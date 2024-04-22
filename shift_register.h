#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

#define DS 2 // D2 yellow
#define DSCLK 4 //  D3 orange

class ShiftRegister {
public:
    ShiftRegister();  // Constructor
    void begin(); // Initialize ADS1115
    void shiftOutZeros(int count = 10, int delayTime = 10);
    void readOlivometer();
    void printData();

    int data[2][8];
private:
    Adafruit_ADS1115 ads;
};



#endif
