#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>

ESP8266WebServer server2;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;
const int input =3;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


uint8_t pin = 16;
char* ssid = "Redmi";
char* password = "prathyu2001";
unsigned long currtime = millis();
unsigned long prevtime = 0;
const long timetime = 2000;

void setup() {
  pinMode(pin, OUTPUT);
  pinMode(input,INPUT);

  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    delay(500);

  }
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
  server2.on("/", []() {
    server2.send(200, "text/plain", "Hello World!");
  });
  server2.on("/toggle", toggle);
  //server.on("/toggle",[](){server.send(200,"working");});
  server2.begin();
}

void loop(){ 
WiFiClient client = server.available();   

  if (client) {                            
    Serial.println("New Client.");         
    String currentLine = "";                
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();         
      if (client.available()) {             
        char c = client.read();            
        Serial.write(c);                 
        header += c;
        if (c == '\n') {                  
          if (currentLine.length() == 0) {
           client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
        
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
    
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
             
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
   
    header = "";
    
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
void toggle()
{
  digitalWrite(pin, !digitalRead(pin));
  if (digitalRead(pin) == HIGH)
    server2.send(200, "text/plain", "working");
  else
    server2.send(200, "text/plain", "In off state");
  //server.send(200,"text/plain","working");
}
