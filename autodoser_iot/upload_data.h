#include <ESP8266WiFi.h>
#include <Wire.h>

unsigned long previousUploadMillis = 0;



namespace Connection {
  void initialise(const char* MY_SSID,const char* MY_PWD  ) {
    Wire.begin();
    //Serial.begin(115200);
    Serial.print("Connecting to " + *MY_SSID);
    WiFi.begin(MY_SSID, MY_PWD);
    Serial.println("going into wl connect");
  
    while (WiFi.status() != WL_CONNECTED) //not connected,..waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("wl connected");
    Serial.println("");
    Serial.println("Credentials accepted! Connected to wifi\n ");
    Serial.println("");
  }
}

void send_data(String apiKey,const char* host, float phSensorValue,float ecSensorValue){
  WiFiClient client;  //Instantiate WiFi object

  //Start or API service using our WiFi Client through PushingBox
  if (client.connect(host, 80))

  {
    String postStr = apiKey
                 + "&field1=" + (String) phSensorValue
                 + "&field2="      + (String) ecSensorValue
                 + "\r\n\r\n";

    // Serial.print("Requesting URL: " + url);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.print("Data Sent!");
    }

    Serial.println();
    Serial.println("closing connection");
  }
}
