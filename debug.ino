void debug(int goTo, int from) {
  Serial.println("---------------------------------");
  Serial.print("AnalogRead: ");
  Serial.println(analogRead(potPin));
  Serial.print("getPos(): ");
  Serial.println(getPosition(VALUE));
  Serial.print("currentPos: ");
  Serial.println(from);
  Serial.print("set pos: ");
  Serial.println(goTo);
}

void debugMotor(int from, int to) {
  Serial.print(from);
  Serial.print(" -> ");
  Serial.println(to);
}
void debugPayload(char* topic, String data) {
  Serial.print("Received ");
  Serial.print(topic);
  Serial.print(" w data: ");
  Serial.println(data.c_str());
}
