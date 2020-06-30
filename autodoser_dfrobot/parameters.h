// upload_data
String apiKey = "xxx";
//const char* host = "api.thingspeak.com"; //pushingbox API server
const char* ssid = "SINGTEL-xxx";
const char* password =  "xxx";

const long dataUploadInterval = 60000; // 1 minute

// pump_activation
float phUpperThreshold = 6.3;
float phLowerThreshold = 0;
float ecLowerThreshold = 1.8;

const long pumpShutOffInterval = 350000;// 5+ mins
const long pumpOnInterval = 7000;
