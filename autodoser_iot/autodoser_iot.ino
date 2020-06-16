// Code and schematics: https://www.youtube.com/watch?v=QW0YcxN3pao

//Example Sketch using multiple analog sensors into one analog input pin
//Tutorials and more at http://www.cabuu.com
#include "pump_activation.h"
#include "read_sensor.h"
#include "upload_data.h"
#include "parameters.h"


void setup() {
  Serial.begin(9600);
  Pump::initialise();
  Sensors::initialise();
  Connection::initialise(MY_SSID,MY_PWD);
}

void loop() {
  // read sensors ~ EC and pH
  phSensorValue = read_phSensor();
  ecSensorValue = read_ecSensor();

  //Print the results to the serial monitor
  Serial.print("phSensorValue = ");
  Serial.print(phSensorValue);
  Serial.print(" / ecSensorValue = ");
  Serial.println(ecSensorValue);

  unsigned long currentMillis = millis();

  //Send data
  if (currentMillis - previousUploadMillis >= dataUploadInterval){
    send_data(apiKey,host, phSensorValue,ecSensorValue);
    previousUploadMillis = currentMillis;
  }
  
  // Activate and deactivate pump
  
  if (currentMillis - previousMillis >= pumpShutOffInterval) {
    previousMillis = check_activate_pump(currentMillis, phSensorValue, ecSensorValue,phLowerThreshold, phUpperThreshold, ecLowerThreshold );
  }
  if (currentMillis - previousMillis >= pumpOnInterval) {
    deactivate_pump();
  }
  
}
