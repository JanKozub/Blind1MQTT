void setPotRanges() {
  int baseValue = (maxValue - minValue) / 4;
  for (int i = 1; i < 4; i++) {
    steps[i] = minValue + (baseValue * i);
  }
}

int getPosition(boolean type) {
  int potValue = analogRead(potPin);

  int currentPos = map(potValue, minValue, maxValue, 0, 4);
  Serial.println(currentPos);

  if(type == STEP){
    return currentPos;
  } else {
   return steps[currentPos]; 
  }
}
