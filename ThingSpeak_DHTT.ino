#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<DHT.h>
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
HTTPClient http;
String thingSpeakAddress="http://api.thingspeak.com/update.json?";
String url;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
dht.begin();
WiFi.disconnect();//disconnect from existing connection
WiFi.begin("aparanji","aparanji@123");
while((!(WiFi.status()==WL_CONNECTED)))
{
  Serial.println("Connecting.....");
  delay(300);
}
Serial.println("connected");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
delay(2000);
float t=dht.readTemperature();
float h=dht.readHumidity();
Serial.println(t);
Serial.println(h);
if(client.connect("api.thingspeak.com",80)){
  url=thingSpeakAddress;
  url+="api_key=";
  url+="1H4XN0BQF1P6XRX2";//Write API Key
  url+="&field1=";
  url+=t;
  url+="&field2=";
  url+=h;
  //url+="&field3=";
  //url+=analogRead(A0);
  Serial.println(url);
  http.begin(url);
  http.GET();
  http.end();
}
}
