double currentRead, currentLimit;
int motorForward = 5, motorReverse = 6, swState = 7, potRead;

void setup() {

  // Serial.begin(9600);
  pinMode(potRead, INPUT);
  pinMode(motorForward, OUTPUT);
  pinMode(motorReverse, OUTPUT);
  pinMode(swState, INPUT);
}

void loop() {

  potRead = analogRead(A0);
  int sensorRead = analogRead(A1);
  bool swStateRead = digitalRead(swState);
  int mPotRead = map(potRead, 0, 1023, 0, 100);
  int mSensorRead = map(sensorRead, 0, 1023, 0, 100);
  currentLimit = double(mPotRead)/100;
  currentRead = double(mSensorRead)/100;
  // Serial.println("CurrentLimit is:"+ String(currentLimit));
  // Serial.println("CurrentRead is:"+ String(currentRead));
  // Serial.println();
  delay(500);

  if((swStateRead == true) && (currentRead <= currentLimit)){
    //Open exhaust valve
    digitalWrite(motorReverse, LOW);
    delay(10);
    digitalWrite(motorForward, HIGH);

  }else if ((swStateRead == false) && (currentRead <= currentLimit)){
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
