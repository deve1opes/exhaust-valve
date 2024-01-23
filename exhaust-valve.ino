double currentRead, currentLimit, offsetFor = 0.0, offsetRe = 0.0, fCurrent, rCurrent;
int motorForward = 5, motorReverse = 6, swState = 7, potRead, sensorRead;

void setup() {

  // Serial.begin(9600);
  pinMode(potRead, INPUT);
  pinMode(motorForward, OUTPUT);
  pinMode(motorReverse, OUTPUT);
  pinMode(swState, INPUT);
}

void loop() {

  potRead = analogRead(A0);
  sensorRead = analogRead(A1);
  bool swStateRead = digitalRead(swState);
  int mPotRead = map(potRead, 0, 1023, 0, 100);
  int mSensorRead = map(sensorRead, 0, 1023, 0, 100);
  currentLimit = double(mPotRead)/100;
  currentRead = double(mSensorRead)/100;

  // Forward+offset, Reverse+offset
  fCurrent = currentRead+offsetFor;
  rCurrent = currentRead+offsetRe;

  // Serial.print(offsetFor);
  // Serial.print(",");
  // Serial.println(offsetRe);
  
  // Serial.print("CurrentLimit is:");
  // Serial.println(currentLimit, 4);

  // Serial.print("CurrentRead is:");
  // Serial.println(currentRead, 4);

  // Serial.println();
  delay(500);

  if((swStateRead == true) && (fCurrent <= currentLimit)){
    //Open exhaust valve
    digitalWrite(motorReverse, LOW);
    delay(10);
    digitalWrite(motorForward, HIGH);

  }else if ((swStateRead == false) && (rCurrent <= currentLimit)){
    //Close exhaust valve
    digitalWrite(motorForward, LOW);
    delay(10);
    digitalWrite(motorReverse, HIGH);

  }else if(currentRead >= currentLimit){
    //Disable all output when current is over limit.
    digitalWrite(motorForward, LOW);
    digitalWrite(motorReverse, LOW);
  }
}
