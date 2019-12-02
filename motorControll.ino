void setMotor(int direction) {
  if (direction == 0) {
    analogWrite(enablePin, 1023);
    digitalWrite(in1Pin, 1);
    digitalWrite(in2Pin, 0);
  }
  if (direction == 1) {
    analogWrite(enablePin, 1023);
    digitalWrite(in1Pin, 0);
    digitalWrite(in2Pin, 1);
  }
  if (direction == 2) {
    analogWrite(enablePin, 1023);
    digitalWrite(in1Pin, 0);
    digitalWrite(in2Pin, 0);
  }
}
