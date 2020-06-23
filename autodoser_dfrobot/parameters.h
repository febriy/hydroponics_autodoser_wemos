// upload_data
String apiKey = "xxx";
const char* host = "api.thingspeak.com"; //pushingbox API server
const char* MY_SSID = "SINGTEL-xxx";
const char* MY_PWD =  "xxx";

const long dataUploadInterval = 600000; // 10 minutes

// pump_activation
float phUpperThreshold = 6.5;
float phLowerThreshold = 5.5;
float ecLowerThreshold = 1.8;

const long pumpShutOffInterval = 10000;
const long pumpOnInterval = 2000;
