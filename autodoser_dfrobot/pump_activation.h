const int phUpPumpPin =  7;
const int phDownPumpPin =  8;
const int ecPumpPin =  9;
const int powerPin =  4;

float pumpVal;

unsigned long previousMillis = 300000;

namespace Pump {
void initialise() {
  pinMode(phUpPumpPin, OUTPUT);
  pinMode(phDownPumpPin, OUTPUT);
  pinMode(ecPumpPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
}
}

unsigned long check_activate_pump(unsigned long currentMillis, float phSensorValue, float ecSensorValue , float phLowerThreshold, float phUpperThreshold, float ecLowerThreshold ) {
//  Serial.print("ecSensorValue:");
//  Serial.print(ecSensorValue,1);
//  Serial.print("  EC Thresh:");
//  Serial.println(ecLowerThreshold,2);
//  Serial.print("  pH:");
//  Serial.print(phSensorValue,2);
//  Serial.print("  pH Thresh:");
//  Serial.println(phUpperThreshold,2);
  
  if (ecSensorValue < ecLowerThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(ecPumpPin, HIGH);
    pumpVal = ecSensorValue;
  }
  
  if (ecSensorValue > ecLowerThreshold && phSensorValue < phLowerThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(phUpPumpPin, HIGH);
    pumpVal = phSensorValue;
  }

  if (ecSensorValue > ecLowerThreshold && phSensorValue > phUpperThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(phDownPumpPin, HIGH);
    pumpVal = phSensorValue;
  }
  return previousMillis, pumpVal;
}

void deactivate_pump() {
  digitalWrite(phUpPumpPin, LOW);
  digitalWrite(phDownPumpPin, LOW);
  digitalWrite(ecPumpPin, LOW);

}
