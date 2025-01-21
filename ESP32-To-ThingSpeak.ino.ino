#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ClassicTech Network";   // Replace with your WiFi SSID
const char* password = "helloworld@#1";    // Replace with your WiFi password
const String apiKey = "PWKX665NU4P3UAQ5";
const String baseURL = "http://api.thingspeak.com/update?api_key=" + apiKey;

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // Read until newline
    Serial.println("Received data from Arduino: " + data);
    
    // Parse the received data and send it to ThingSpeak
    sendToThingSpeak(data);
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
}
void sendToThingSpeak(String data) {
  // Extract temperature, humidity, and gas ppm from the received data
  float temperature, humidity, gasPPM;
  sscanf(data.c_str(), "T:%f,H:%f,GA:%*d,GD:%*d,PPM:%f", &temperature, &humidity, &gasPPM);

  WiFiClient client;  // Declare WiFiClient object
  
  HTTPClient http;
  
  Serial.print("Sending data to ThingSpeak... ");
  if (http.begin(client, baseURL + "&field1=" + String(temperature) +
                                    "&field2=" + String(humidity) +
                                    "&field3=" + String(gasPPM))) {
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Failed to send data. HTTP response code: " + String(httpResponseCode));
    }
    
    http.end();
  } else {
    Serial.println("Failed to connect to ThingSpeak");
  }
}
