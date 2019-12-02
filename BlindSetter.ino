boolean setBlind(int pos) {
  if (pos < 1 || pos > 5) return false;

  pos = steps[pos - 1];
  int currentPos = getPosition(VALUE);
  newPos = pos;
  debug(pos, currentPos);

  if (currentPos == pos) return true; //ON SPOT

  if (currentPos < pos) { //GO UP
    setMotor(motor_UP);
    motorRunning = motor_UP;
  } else { //GO DOWN
    setMotor(motor_DOWN);
    motorRunning = motor_DOWN;
  }
  return true;
}

boolean protectGears() {
  if (analogRead(potPin) < absoluteMinValue) {
    setMotor(motor_STOP);
    return true;
  }
  if (analogRead(potPin) > absoluteMaxValue) {
    setMotor(motor_STOP);
    return true;
  }
  return false;
}
