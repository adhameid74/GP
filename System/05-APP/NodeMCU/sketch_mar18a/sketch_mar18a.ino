#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h>

#define ESP8266
StaticJsonBuffer<200> jsonBuffer;


SocketIOClient client;
const char* ssid     = "*****";
const char* password = "*****";
String message = "";
char host[] = "192.168.1.*";
int port = 8080;
extern String RID;
extern String Rname;
extern String Rcontent;

unsigned long previousMillis = 0;
long interval = 5000;
unsigned long lastreply = 0;
unsigned long lastsend = 0;
String JSON;
JsonObject& root = jsonBuffer.createObject();
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  root["Message"] = "LOL XD";
  root["time"] = 1234567890;
  JsonArray& data = root.createNestedArray("data");
  data.add(double_with_n_digits(48.756080, 6));
  data.add(double_with_n_digits(2.302038, 6));
  root.printTo(JSON);
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
   digitalWrite(LED_BUILTIN,HIGH);
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
if (client.connected())
  {
    client.send("connection", "message", "Connected !!!!");
  }
}

void loop() {
  client.send("stillConnected","Name","message");

  delay(1000);

  if (client.monitor())
  {
    if(RID == "diagnose")
    {
      Serial.println("----Rcontent is ----");
      Serial.println(Rcontent);
      Serial.println("----Rname is ----");
      Serial.println(Rname);
      RID = "null";
    }
   }
}
