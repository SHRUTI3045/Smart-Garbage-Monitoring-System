#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define trigPin D4
#define echoPin D5

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883  
#define AIO_USERNAME    "your_aio_username"
#define AIO_KEY         "your_aio_key"
#define MAX_DISTANCE 100

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

WiFiClientSecure client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish dustbinlevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dustbinlevel");

long duration;
int distance;
float dustbinPercentage;

void setup() {
  Serial.begin(9600);
  delay(1000);

  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retries++;
    if (retries > 10) {
      Serial.println("WiFi connection failed. Restarting...");
      ESP.restart();
    }
  }
  Serial.println();
  Serial.println("WiFi connected");

  if (!mqtt.connect()) {
    Serial.println("Connection to Adafruit IO failed");
    return;
  }
  Serial.println("Connected to Adafruit IO");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 10000);
  if (duration == 0) {
    Serial.println("Error: pulseIn timeout");
    return;
  }

  distance = duration * 0.034 / 2;
  dustbinPercentage = ((float)distance / MAX_DISTANCE) * 100;
  dustbinPercentage = constrain(dustbinPercentage, 0, 100);

  if (!publishData()) {
    Serial.println("Error: publishing data to Adafruit IO");
    return;
  }

  Serial.print("Dustbin Percentage: ");
  Serial.print(dustbinPercentage);
  Serial.println();

  delay(1000);
}

bool publishData() {
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["dustbin_percentage"] = dustbinPercentage;

  String jsonData;
  serializeJson(jsonDoc, jsonData);
  if (!mqtt.publish(AIO_USERNAME "/feeds/dustbinlevel", jsonData.c_str())) {
    return false;
  }
  return true;
}
