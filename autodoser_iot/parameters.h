// upload_data
String apiKey = "xxx";
const char* host = "api.thingspeak.com"; //pushingbox API server
const char* MY_SSID = "SINGTEL-xxx";
const char* MY_PWD =  "xxx";

const long dataUploadInterval = 600000; // 10 minutes

// pump_activation
float phUpperThreshold = 700;
float phLowerThreshold = 200;
float ecLowerThreshold = 100;

const long pumpShutOffInterval = 10000;
const long pumpOnInterval = 2000;
