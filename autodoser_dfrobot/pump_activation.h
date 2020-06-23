const int phUpPumpPin =  13;
const int phDownPumpPin =  12;
const int ecPumpPin =  11;


unsigned long previousMillis = 0;

namespace Pump {
void initialise() {
  pinMode(phUpPumpPin, OUTPUT);
  pinMode(phDownPumpPin, OUTPUT);
  pinMode(ecPumpPin, OUTPUT);
  
}
}

unsigned long check_activate_pump(unsigned long currentMillis, float phSensorValue, float ecSensorValue , float phLowerThreshold, float phUpperThreshold, float ecLowerThreshold ) {
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
