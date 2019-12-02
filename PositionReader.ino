void setPotRanges() {
  int baseValue = (maxValue - minValue) / 4;
  for (int i = 1; i < 4; i++) {
    steps[i] = minValue + (baseValue * i);
  }
}

int getPosition(boolean type) {
  int potValue = analogRead(potPin);

  int currentPos = map(potValue, minValue, maxValue + 5, 0, 5);

  if(type == STEP){
    return currentPos;
  } else {
   return steps[currentPos]; 
  }
}
