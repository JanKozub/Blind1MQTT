void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Blind1";

    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      client.publish("blind1,", "1");
      client.subscribe("blind1Sub");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String output = "";
  for (int i = 0; i < length; i++) {
    output = output + (char)payload[i];
  }
  debugPayload(topic, output);
  if (output.equals("UPDATE")) {
    String msg = "blind1," + String(state);
    client.publish("blind1", msg.c_str());
  } else if (output.equals("ACTIVE")) {
  } else {
    state = output.toInt();
    Serial.println(setBlind(state));
  }
}
