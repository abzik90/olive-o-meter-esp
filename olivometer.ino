
#include "sharp.h"
#include "shift_register.h"
#include "get_request.h"

#define REFRESH_INTERVAL 250 // 250 ms or 4Hz
#define BUTTONPIN 19 // D19

unsigned long previousMillis = millis();

ShiftRegister sr;
OlivometerDisplay sharp;
GetRequest req;

void buttonClick(){
  Serial.println("clicked!");
  sr.readOlivometer();
  sr.printData();
  sharp.drawTable(sr.data);
  String requestToSend="?";
  for(size_t i = 0; i < 8; ++i){
      if (i != 0) requestToSend += "&";
      requestToSend += String(wavelengths[i]) + "nm=" + String(sr.data[1][i]);
      requestToSend += "&" + String(wavelengths[i]) + "nm_amb=" + String(sr.data[0][i]);
  }
  requestToSend += "&latitude=51.08750176951251&longitude=71.39752817807408&tree_pos=middle";
  Serial.println(req.sendGet("http://192.168.59.253:5000/new"+requestToSend));
  Serial.println("http://192.168.59.253:5000/new" + requestToSend);
  Serial.println("\n\n\n");
}

void setup() {
  Serial.begin(115200);
  sr.begin();
  sharp.begin();
  req.begin();
  pinMode(BUTTONPIN, INPUT_PULLUP);
 }

void loop() {
  if(digitalRead(BUTTONPIN) == HIGH) buttonClick();
  // Refresh the display at 4Hz to avoid screen burn-ins
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= REFRESH_INTERVAL) {
      previousMillis = currentMillis;
      sharp.refreshScreen();
  }
}
