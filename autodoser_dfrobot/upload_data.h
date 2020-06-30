#include "esp8266.h"
#include "SoftwareSerial.h"

#define serverIP  "184.106.153.149"
#define serverPort  "80"

unsigned long previousUploadMillis = 0;

String msg;

Esp8266 wifi;
SoftwareSerial mySerial(10, 11);

namespace Connection {
  
  void initialise(const char* ssid,const char* password) {
    
    delay(2000);                      // it will be better to delay 2s to wait esp8266 module OK
    Serial.begin(115200);
    mySerial.begin(115200);
    wifi.begin(&Serial, &mySerial);   //Serial is used to communicate with esp8266 module, mySerial is used to debug
    if (wifi.checkEsp8266()) {
      wifi.debugPrintln("esp8266 is online!");
    }
    if (wifi.connectAP(ssid, password)) {
      wifi.debugPrintln("esp8266 is connected to AP!");
      }
    
    if (wifi.setSingleConnect()) {
      wifi.debugPrintln("single connect!");
    }
  
    wifi.debugPrintln(wifi.getIP());
    }
}

void send_data(String apiKey,float temperature, float phSensorValue, float ecSensorValue, float pumpVal) {
  if (wifi.connectTCPServer(serverIP, serverPort)) {
    wifi.debugPrintln("connect TCP server OK!");
  }
  msg = "GET /update?key="+ apiKey +"&field1="+ (String) phSensorValue+"&field2="+ (String)ecSensorValue+"&field3="+ (String)temperature+"&field4="+ (String)pumpVal+ "\r\n";
  wifi.sendMessage(msg);
  delay(1000);
}
