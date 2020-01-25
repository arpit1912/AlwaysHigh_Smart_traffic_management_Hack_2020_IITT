#include <ESP8266WiFi.h>

char* ssid="Redmi";
char* password="prathyu2001";

void setup() {
  // put your setup code here, to run once:
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println("");
    delay(500);
    
  }
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
