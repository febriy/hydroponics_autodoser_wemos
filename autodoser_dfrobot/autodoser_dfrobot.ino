#include "pump_activation.h"
#include "read_sensor.h"
#include "U8glib.h"
#include "upload_data.h"
#include "oled.h"
#include "parameters.h"

const int numReadings = 10;

float phReadings[numReadings];      // the readings from the analog input
int phReadIndex = 0;              // the index of the current reading
float phTotal = 0;                  // the running total
float phAverage = 5.5;                // the average

float ecReadings[numReadings];      // the readings from the analog input
int ecReadIndex = 0;              // the index of the current reading
float ecTotal = 0;                  // the running total
float ecAverage = 8.0;                // the average

void setup() {
  Serial.begin(115200);
  Pump::initialise();
  Sensors::initialise();
  Connection::initialise(ssid, password); //(MY_SSID,MY_PWD);
  for (int phThisReading = 0; phThisReading < numReadings; phThisReading++) {
    phReadings[phThisReading] = 0;
  }
  for (int ecThisReading = 0; ecThisReading < numReadings; ecThisReading++) {
    phReadings[ecThisReading] = 0;
  }
}



void loop() {
  // read sensors ~ EC and pH
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 5000) {
    timepoint = millis();
    
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
    //      Serial.print("average EC:");
    //      Serial.println(ecAverage);

    phTotal = phTotal - phReadings[phReadIndex];
    phReadings[phReadIndex] = read_phSensor();
    phTotal = phTotal + phReadings[phReadIndex];
    phReadIndex = phReadIndex + 1;

    if (phReadIndex >= numReadings) {
      // ...wrap around to the beginning:
      phReadIndex = 0;
    }

    phAverage = phTotal / numReadings;
    //      Serial.print("average pH:");
    //      Serial.println(phAverage);

    unsigned long currentMillis = millis();

    //Send data
    if (currentMillis - previousUploadMillis >= dataUploadInterval) {
      //Serial.println(valPump);
      send_data(apiKey, temperature, phAverage, ecAverage, pumpVal);
      previousUploadMillis = currentMillis;
    }

    // Activate and deactivate pump
    pumpVal = 0.0;
    if (currentMillis - previousMillis >= pumpShutOffInterval) {
      previousMillis, pumpVal = check_activate_pump(currentMillis, phAverage, ecAverage, phLowerThreshold, phUpperThreshold, ecLowerThreshold );
      if ( pumpVal != 0.0) {
        send_data(apiKey, temperature, phAverage, ecAverage, pumpVal);
      }
    }
    if (currentMillis - previousMillis >= pumpOnInterval) {
      deactivate_pump();
    }
  }
}
