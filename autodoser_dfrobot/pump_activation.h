const int phUpPumpPin =  13;
const int phDownPumpPin =  12;
const int ecPumpPin =  11;
const int powerPin =  4;

unsigned long previousMillis = 0;

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
  Serial.print("ecSensorValue:");
  Serial.print(ecSensorValue,1);
  Serial.print("  EC Thresh:");
  Serial.println(ecLowerThreshold,2);
  Serial.print("  pH:");
  Serial.print(phSensorValue,2);
  Serial.print("  pH Thresh:");
  Serial.println(phUpperThreshold,2);
  
  
  if (ecSensorValue < ecLowerThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(ecPumpPin, HIGH);
  }
  
  if (ecSensorValue > ecLowerThreshold && phSensorValue < phLowerThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(phUpPumpPin, HIGH);
  }

  if (ecSensorValue > ecLowerThreshold && phSensorValue > phUpperThreshold)  {
    previousMillis = currentMillis;
    digitalWrite(phDownPumpPin, HIGH);
  }
  return previousMillis;
}

void deactivate_pump() {
  digitalWrite(phUpPumpPin, LOW);
  digitalWrite(phDownPumpPin, LOW);
  digitalWrite(ecPumpPin, LOW);

}
