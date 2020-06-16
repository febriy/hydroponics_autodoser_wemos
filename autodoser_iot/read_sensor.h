int phSensorValue;
int ecSensorValue;
int phPin_D8 = 15;
int ecPin_D7 = 13;

namespace Sensors {
  void initialise() {
    pinMode(phPin_D8, OUTPUT);
    pinMode(ecPin_D7, OUTPUT);
    pinMode(A0, INPUT);
  }
}



float read_phSensor() {
  digitalWrite(phPin_D8, HIGH);     //Turn D7 On
  delay(100);                     //Wait for sensor
  phSensorValue = analogRead(0);       //Read Analog pin as D7
  digitalWrite(phPin_D8, LOW);      //Turn D7 Off
  delay(100);
  return phSensorValue;
}

float read_ecSensor() {
  //Repeat for D8
  digitalWrite(ecPin_D7, HIGH);     //Turn D8 On
  delay(100);                     //Wait for sensor
  ecSensorValue = analogRead(0);       //Read Analog pin as D8
  digitalWrite(ecPin_D7, LOW);      //Turn D8 Off
  delay(100);                     //Wait for sensor
  return ecSensorValue;
}
