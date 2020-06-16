# Hydroponics Autodoser + IoT 
Read pH, EC, control pumps, send data to Thingspeak.

Goal: Automate nutrient control in a hydroponics system.

# Quick Run

## Bill of Material (Coming up)

## Schematics
Schematics based on [this](https://www.youtube.com/watch?v=QW0YcxN3pao) project.

## Set-up Thingspeak
Follow this [tutorial](https://community.thingspeak.com/tutorials/arduino/send-data-to-thingspeak-with-arduino/#:~:text=Install%20ThingSpeak%20Communication%20Library%20for,and%20click%20the%20Install%20button.)

## Modify parameters in parameters.h
```
// upload_data
String apiKey = "xxx";
const char* host = "api.thingspeak.com"; //pushingbox API server
const char* MY_SSID = "SINGTEL-xxx";
const char* MY_PWD =  "xxx";

const long dataUploadInterval = 600000; // 10 minutes

// pump_activation
float phUpperThreshold = 7;
float phLowerThreshold = 5.8;
float ecLowerThreshold = 1.4;

const long pumpShutOffInterval = 10000;
const long pumpOnInterval = 2000;
```