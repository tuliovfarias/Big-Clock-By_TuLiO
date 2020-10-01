/*
   Hello world web server
   circuits4you.com
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Our HTML webpage contents

//SSID and Password of your WiFi router

const char *ssid     = "2.4 GHZ NET VIRTUA 802";
const char *password = "3203412200";


ESP8266WebServer server(80); //Server on port 80
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  Serial.println("You called root page");
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleLEDon() {
  Serial.println("LED on page");
  digitalWrite(D4, LOW); //LED is connected in reverse
  server.send(200, "text/plain", "ON"); //Send ADC value only to client ajax request
}

void handleLEDoff() {
  Serial.println("LED off page");

  digitalWrite(D4, HIGH); //LED off
  server.send(200, "text/plain", "OFF"); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void) {
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/cron_play", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/cron_reset", handleLEDoff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  server.handleClient();          //Handle client requests
}
