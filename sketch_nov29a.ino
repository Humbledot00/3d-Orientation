#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Galaxy A129E3D";
const char *password = "bhxg8697";

// Replace with your server address
const char *serverAddress = "http://192.168.149.226:3000/data-receiver";

int value = 0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Your data to be sent
  String dataToSend = randomnumber();

  // Create a WiFiClient object
  WiFiClient client;

  // Create an HTTP object with the WiFiClient
  HTTPClient http;
  http.begin(client, serverAddress);

  // Set content type header
  http.addHeader("Content-Type", "text/plain");

  // Send POST request
  int httpResponseCode = http.POST(dataToSend);

  // Check for a successful response
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println("Data sent successfully");
  } else {
    Serial.print("HTTP Error code: ");
    Serial.println(httpResponseCode);
    Serial.println("Error sending data");
  }

  // Close connection
  http.end();

  // Wait for a while before sending the next request
  delay(5000);
}

String randomnumber() {
  if (value == 0) {
    value = 1;
    return "10";
  } else {
    value = 0;
    return "0";
  }
}
