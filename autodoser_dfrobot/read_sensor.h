#include "DFRobot_PH.h"
#include "DFRobot_EC.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <EEPROM.h>

#define PH_PIN A0
#define EC_PIN A1
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

float voltage,phSensorValue, ecSensorValue, temperature = 25;

DFRobot_PH ph;
DFRobot_EC ec;

namespace Sensors {
  void initialise() {
    ph.begin();
    ec.begin();
  }
}

float readTemperature()
{ 
   sensors.requestTemperatures(); // Send the command to get temperature readings 
   temperature = sensors.getTempCByIndex(0);
   return temperature;
}

float read_phSensor() {
  temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
  voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
  phSensorValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
  Serial.print("temperature:");
  Serial.print(temperature,1);
  Serial.print("^C  pH:");
  Serial.println(phSensorValue,2);
  return phSensorValue;
}

float read_ecSensor() {
  voltage = analogRead(EC_PIN)/1024.0*5000;  // read the voltage
  temperature = readTemperature();  // read your temperature sensor to execute temperature compensation
  ecSensorValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
  Serial.print("temperature:");
  Serial.print(temperature,1);
  Serial.print("^C  EC:");
  Serial.print(ecSensorValue,2);
  Serial.println("ms/cm");
  return ecSensorValue;
}
