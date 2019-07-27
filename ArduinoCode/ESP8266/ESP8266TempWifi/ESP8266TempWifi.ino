#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h" 

#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

/*Put your SSID & Password*/
const char* ssid = "CSE-WiFi";    // Enter SSID here
const char* password = "cse@dept";  //Enter Password here

const char* server = "172.16.26.43";

/* Set GET link with channel ID */
const char* _getLink = "http://172.16.26.43:5000/submitData";

WiFiClient client;

void setup() {
  Serial.begin(9600);
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
}

void loop() 
{
  WiFi.mode(WIFI_STA);
  //if (client.connect(server,5000))     // "184.106.153.149" or api.thingspeak.com
  //{
    Serial.println("Connected");  
    
    float temperature1 = dht.readTemperature();
  
    String data = "temp_sensor=" + String(temperature1);
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
  //}
  client.stop();
  Serial.println("Waiting…");
  delay(10000);
}
