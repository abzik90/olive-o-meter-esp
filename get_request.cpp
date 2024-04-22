#include "get_request.h"

WiFiMulti wifiMulti;

GetRequest::GetRequest(){
  ;
  }
void GetRequest::begin(){
   wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD); 
}

String GetRequest::sendGet(String url){
  String response = "response:";  
  if((wifiMulti.run() == WL_CONNECTED)) {
      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
        response += String(httpCode);
        // httpCode will be negative on error
        if(httpCode > 0) {
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                response += ("http code ok: "+payload+"\n");
            }
        } else {
            response +=("[HTTP] GET... failed, error: "); response += http.errorToString(httpCode).c_str(); response+=+"\n";
        }

        http.end();
        return response;
    }  
  
}

String GetRequest::sendPost(String url, String postData){
  String response = "response:";  
  if((wifiMulti.run() == WL_CONNECTED)) {
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpCode = http.POST(postData);
        response += String(httpCode);
        // httpCode will be negative on error
        if(httpCode > 0) {
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                response += ("http code ok: "+payload+"\n");
            }
        } else {
            response +=("[HTTP] GET... failed, error: "); response += http.errorToString(httpCode).c_str(); response+=+"\n";
        }

        http.end();
        return response;
    }  
}
