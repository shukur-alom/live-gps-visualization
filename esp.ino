#include <TinyGPS++.h>
#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>

#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600

TinyGPSPlus gps;  // the TinyGPS++ object

float latitude = 23.7840857;
float longitude = 90.3452895;
int count_se = 0;
unsigned long startTime_1;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  //mqttClient.setCallback(callback);

}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("Connected.");

    }
  }
}




//const char* ssid = "Home Garden";
const char* ssid = "Home";
const char* password = "53384208@#sR";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUDRATE);
  initWiFi();
  setupMQTT();

}

void loop() {

  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    WiFi.disconnect();
    previousMillis = currentMillis;
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.disconnect();
      initWiFi();

    }

    if (!mqttClient.connected()) {
      reconnect();

    }
    mqttClient.loop();
  }

  //start coding
  else {
    if (!mqttClient.connected()) {
      mqttClient.disconnect();
      reconnect();
    }
    mqttClient.loop();

    String stringOne = "";

    if (Serial2.available() > 0) {
      if (gps.encode(Serial2.read())) {
        if (gps.location.isValid()) {
          Serial.print(F("- latitude: "));
          Serial.println(gps.location.lat());

          Serial.print(F("- longitude: "));
          Serial.println(gps.location.lng());

          Serial.print("set.:");
          Serial.println(gps.satellites.value());

          latitude = gps.location.lat();
          longitude = gps.location.lng();
          count_se = gps.satellites.value();

        }
      }
      stringOne = stringOne + String(latitude , 7) + "," + String(longitude , 7);
      String count_se_str = String(count_se);

      mqttClient.publish("gps/53384", stringOne.c_str());
      mqttClient.publish("gps/count/53384", count_se_str.c_str());
    }
  }
}