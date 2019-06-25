#include "WiFi.h"
#include "HTTPClient.h"
#include <DHTesp.h>

//Install DHT sensor library for ESPx by beegee library

/*Put your SSID & Password*/
const char* ssid = "CSE-WiFi";    // Enter SSID here
const char* password = "cse@dept";  //Enter Password here

const char* server = "172.16.28.134";

WiFiClient client;

/* Set GET link with channel ID */
const char* _getLink = "http://172.16.28.134:5000/submitData";

#define DHTPIN 15     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHTesp dht;

//DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  dht.setup(DHTPIN, DHTesp::DHT11);
}

String readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.getTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

void loop() {
  WiFi.mode(WIFI_STA);
  if (client.connect(server,5000))     // "184.106.153.149" or api.thingspeak.com
  {
    Serial.println("Connected");  
    String data = "temp_sensor=" + String(readDHTTemperature());
    Serial.println(data);
      
    String httpPost = _getLink;
    HTTPClient http;
    Serial.println(httpPost);
    http.begin(httpPost);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //DebugLn(data);
    int httpCode = http.POST(data);
    //int httpCode = http.GET();
    //http.writeToStream(&Serial);
    String payload = http.getString();
  
    Serial.println(httpCode);    // this return 200 when success
    Serial.println(payload);     // this will get the response
    http.end();
  }
  client.stop();
  Serial.println("Waiting…");
  delay(10000);
  delay(dht.getMinimumSamplingPeriod());
}
