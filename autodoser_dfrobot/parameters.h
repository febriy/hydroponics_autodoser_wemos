// upload_data
String apiKey = "xxx";
//const char* host = "api.thingspeak.com"; //pushingbox API server
const char* ssid = "SINGTEL-xxx";
const char* password =  "xxx";

const long dataUploadInterval = 6000; // 10 minutes

// pump_activation
float phUpperThreshold = 14;
float phLowerThreshold = 0;
float ecLowerThreshold = 1.8;

const long pumpShutOffInterval = 10000;
const long pumpOnInterval = 2000;
