#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//CONFIG
#define enablePin D2
#define in1Pin D1
#define in2Pin D3
#define potPin A0

int currentPos = 0;
int incomingByte = 0;
int minValue = 100;
int maxValue = 950;
int steps[] = {minValue, 0, 0, 0, maxValue};
int absoluteMinValue = 30;
int absoluteMaxValue = 970;
const char* ssid;
const char* password;
const char* mqtt_server;
volatile int state = 0;
long lastReconnectAttempt = 0;
//END OF CONFIG

WiFiClient espClient;
PubSubClient client(espClient);

#define motor_STOP 2
#define motor_UP 1
#define motor_DOWN 0
#define STEP true
#define VALUE false

int motorRunning = 2; //positions same as in #define
int newPos = 0; //new position set in blindSetter

void setup() {
  importPrivateData();

  Serial.begin(115200);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(potPin, INPUT);

  setup_wifi();
  setPotRanges();
  state = getPosition(STEP);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop() {
  long now = millis();

  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();

    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      String msg = "blind1" + String(state);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish("blind1", msg.c_str());
    }

    if (motorRunning != motor_STOP) {
      protectGears();
      currentPos = analogRead(potPin);
      if (motorRunning == motor_UP) {
        if (currentPos > newPos - 5) {
          setMotor(motor_STOP);
          motorRunning = motor_STOP;
        }
      } else {
        if (motorRunning == motor_DOWN) {
          if (currentPos < newPos + 5) {
            setMotor(motor_STOP);
            motorRunning = motor_STOP;
          }
        }
      }
    }
    delay(15);
  }
}
