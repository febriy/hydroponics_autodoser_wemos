// upload_data
String apiKey = "xxx";
//const char* host = "api.thingspeak.com"; //pushingbox API server
const char* ssid = "SINGTEL-xxx";
const char* password =  "xxx";

const long dataUploadInterval = 300000; // 5 minutes

// pump_activation
float phUpperThreshold = 6.3;
float phLowerThreshold = 0;
float ecLowerThreshold = 1.8;

const long pumpShutOffInterval = 1250000;// 20 mins
const long pumpOnInterval = 2000;
