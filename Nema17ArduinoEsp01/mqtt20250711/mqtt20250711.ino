#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

const char* ssid = "Hobbitown";
const char* password = "12345678";
const char* mqtt_server = "192.168.142.85"; // IP do seu notebook

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin2 = 2; // GPIO2 do ESP-01 wifi
const int ledPin0 = 0; // GPIO0 do ESP-01 mqtt

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    delay(500);
  }
  digitalWrite(ledPin2, HIGH);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message == "on") {
    digitalWrite(ledPin0, HIGH);  // LED aceso no ESP-01
  } else if (message == "off") {
    digitalWrite(ledPin0, LOW); // LED apagado
  }
  
  Serial.write(payload, length);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP01Client")) {
      client.subscribe("esp01/led");
    } else {
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin0, LOW); // começa desligado
  digitalWrite(ledPin2, LOW); // começa desligado

  setup_wifi();
  Serial.begin(9600);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
