
/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
const int ledPin = 13; // the pin that the LED is attached to - change this if you have a separate LED connected to another pin
int incomingByte;      // a variable to read incoming serial data into

/* Set these to your desired credentials. */
const char *ssid = "G";  //ENTER YOUR WIFI SETTINGS
const char *password = "sunil000";

//Web/Server address to read/write from 
const char *host = "192.168.43.45";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  //pinMode(15,OUTPUT);
 // pinMode(13,OUTPUT);
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,HIGH);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  //Serial.println("");

  //Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //digitalWrite(13,HIGH);

  //If connection successful show IP address in serial monitor
  //Serial.println("");
  //Serial.print("Connected to ");
  //Serial.println(ssid);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  incomingByte=0;
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
      Serial.println(incomingByte);
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
      Serial.println("high");
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
  HTTPClient http;    //Declare object of class HTTPClient

  //Serial.println("//===================================================================================//");

  String ADCData,ADCData2,station, postData,remark;
//========================================================================  
  int adcvalue=digitalRead(12);
  int adcvalue2=analogRead(A0);//ead Analog value of LDR
  
  if(adcvalue==0) {ADCData="OFF";}
  else {ADCData="ON";}
  
   if(adcvalue2<280 && adcvalue==0) remark="ERROR";
  else remark="No error";

  ADCData2 = String(adcvalue2);
  
  station = "A";
  

//Serial.println(adcvalue2);

  //Post Data
  postData = "status=" + ADCData + "&status2=" + ADCData2 + "&station=" + station + "&remark=" + remark ;
  
  http.begin("http://192.168.43.45/WEB/new/postdemo.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  //Serial.println(ADCData);
  //Serial.println(ADCData2);
 // Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload
//======================================================================

//Serial.println();

//======================================================================
  
  adcvalue=digitalRead(4);
  adcvalue2=analogRead(A0);//Read Analog value of LDR
  //Serial.println(adcvalue2);
  
  if(adcvalue==0) {ADCData="OFF";}
  else {ADCData="ON";}
  
   if(adcvalue2<280 && adcvalue==0) remark="ERROR";
  else remark="No error";

  
  ADCData2 = String(adcvalue2);
  
  station = "B";

  //Post Data
  postData = "status=" + ADCData + "&status2=" + ADCData2 + "&station=" + station + "&remark=" + remark;
  
  http.begin("http://192.168.43.45/WEB/new/postdemo.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  httpCode = http.POST(postData);   //Send the request
  payload = http.getString();

  
  //Serial.println(ADCData);
  //Serial.println(ADCData2);
  //Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload

//=============================================================================  
  
 //Serial.println("//===================================================================================//");
  http.end();  //Close connection
delay(400);
  
  
 //Post Data at every 5 seconds
}
//=======================================================================
