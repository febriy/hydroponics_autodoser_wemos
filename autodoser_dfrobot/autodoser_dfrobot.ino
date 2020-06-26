  
// Code and schematics: https://www.youtube.com/watch?v=QW0YcxN3pao

//Example Sketch using multiple analog sensors into one analog input pin
//Tutorials and more at http://www.cabuu.com
#include "pump_activation.h"
#include "read_sensor.h"
#include "upload_data.h"
#include "parameters.h"
#include "U8glib.h"

const int numReadings = 10;

float phReadings[numReadings];      // the readings from the analog input
int phReadIndex = 0;              // the index of the current reading
float phTotal = 0;                  // the running total
float phAverage = 6.5;                // the average

float ecReadings[numReadings];      // the readings from the analog input
int ecReadIndex = 0;              // the index of the current reading
float ecTotal = 0;                  // the running total
float ecAverage = 2.0;                // the average

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 


void setup() {
  Serial.begin(115200);
  Pump::initialise();
  Sensors::initialise();
  Connection::initialise(ssid,password);//(MY_SSID,MY_PWD);
  for (int phThisReading = 0; phThisReading < numReadings; phThisReading++) {
    phReadings[phThisReading] = 0;
  for (int ecThisReading = 0; ecThisReading < numReadings; ecThisReading++) {
    phReadings[ecThisReading] = 0;

    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
      u8g.setColorIndex(255);     // white
    }
    else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
      u8g.setColorIndex(3);         // max intensity
    }
    else if ( u8g.getMode() == U8G_MODE_BW ) {
      u8g.setColorIndex(1);         // pixel on
    }
    else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
      u8g.setHiColorByRGB(255,255,255);
    }
  }
}}

void draw(char* to_draw) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, to_draw);
}


void loop() {
  // read sensors ~ EC and pH
  static unsigned long timepoint = millis();
    if(millis()-timepoint>5000){
      timepoint = millis();
      
      phSensorValue = read_phSensor();
      delay(100);
      ecSensorValue = read_ecSensor();
      delay(100);
      temperature = readTemperature();

      ecTotal = ecTotal - ecReadings[ecReadIndex];
      ecReadings[ecReadIndex] = read_ecSensor();
      ecTotal = ecTotal + ecReadings[ecReadIndex];
      ecReadIndex = ecReadIndex + 1;
    
      if (ecReadIndex >= numReadings) {
        // ...wrap around to the beginning:
        ecReadIndex = 0;
      }
    
      ecAverage = ecTotal / numReadings;
      Serial.print("average EC:");
      Serial.println(ecAverage);
      char ecAverageChar[8];
      dtostrf(ecAverage, 6, 2, ecAverageChar);
  
      phTotal = phTotal - phReadings[phReadIndex];
      phReadings[phReadIndex] = read_phSensor();
      phTotal = phTotal + phReadings[phReadIndex];
      phReadIndex = phReadIndex + 1;
    
      if (phReadIndex >= numReadings) {
        // ...wrap around to the beginning:
        phReadIndex = 0;
      }
    
      phAverage = phTotal / numReadings;
      Serial.print("average pH:");
      Serial.println(phAverage);
      char phAverageChar[8];
      dtostrf(phAverage, 6, 2, phAverageChar);

      u8g.firstPage();  
      do {
        draw(phAverageChar);
      } while( u8g.nextPage() );

      delay(500);
      u8g.firstPage();  
      do {
        draw(ecAverageChar);
      } while( u8g.nextPage() );
    }  



  unsigned long currentMillis = millis();

  //Send data
  if (currentMillis - previousUploadMillis >= dataUploadInterval){
    send_data(apiKey,temperature, phAverage,ecAverage);
    previousUploadMillis = currentMillis;
  }
  
  // Activate and deactivate pump

   
  if (currentMillis - previousMillis >= pumpShutOffInterval) {
    previousMillis = check_activate_pump(currentMillis, phAverage, ecAverage,phLowerThreshold, phUpperThreshold, ecLowerThreshold );
  }
  if (currentMillis - previousMillis >= pumpOnInterval) {
    deactivate_pump();
  }
  //Serial.println(currentMillis - previousMillis);
}
