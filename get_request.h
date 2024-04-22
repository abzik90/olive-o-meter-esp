
#ifndef GET_REQ_H
#define GET_REQ_H

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define WIFI_SSID "Redmi Note 8 Pro"
#define WIFI_PASSWORD "fuwafuwa"
//#define WIFI_SSID "TP-Link_4CD6_5G"
//#define WIFI_PASSWORD "05396337"

class GetRequest{
public:
    GetRequest();
    void begin();
    String sendGet(String url);
    String sendPost(String url, String postData);
};



#endif
