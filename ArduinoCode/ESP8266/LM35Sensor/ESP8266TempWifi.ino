#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/*Put your SSID & Password*/
const char* ssid = "DIGISOL";    // Enter SSID here
const char* password = "";  //Enter Password here

const char* server = "172.16.33.227";

/* Set GET link with channel ID */
const char* _getLink = "http://172.16.33.227:5000/submitData";

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
  if (client.connect(server,5000))     // "184.106.153.149" or api.thingspeak.com
  {
    Serial.println("Connected");  
    
    float temperature1 = 0;
    double analogValue1 = 0.0;
    double analogVolts1 = 0.0;
    analogValue1 = analogRead(A0);
    Serial.println(String(analogValue1));
    // convert the analog signal to voltage
    // the ESP2866 A0 reads between 0 and ~3 volts, producing a corresponding value
    // between 0 and 1024. The equation below will convert the value to a voltage value.
    temperature1 = (analogValue1 * 0.322265625);
    Serial.println(String(analogVolts1));
    //temperature1 = (analogVolts1) * 100; //converting from 10 mv per degree wit 500 mV offset
    //to degrees ((voltage - 500mV) times 100)
  
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
  }
  client.stop();
  Serial.println("Waiting…");
  delay(10000);
}