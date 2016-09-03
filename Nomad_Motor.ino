//PIN CONFIGURATION
const int pinEnable = 17;
const int pinStep = 32;
const int pinDir = 33;
const int limitPin = 0; //NEED

const int LOW_POS = 100;
const long HIGH_POS = 5000;

void setup() {
  pinMode(pinEnable, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);

  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDir, HIGH);

  delay(1000);
  long stepCount = 0;


  //Lower until limit switch is triggered
  int pulseTime=10;
  while(digitalRead(limitPin)==LOW){
    digitalWrite(pinStepLeft, HIGH);
    digitalWrite(pinStepRight, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStepLeft, LOW);
    digitalWrite(pinStepRight, LOW);
    delayMicroseconds(pulseTime);
  }

//Raise to "Low" position
for(int i=0; i<LOW_POS; i++){
    digitalWrite(pinStepLeft, HIGH);
    digitalWrite(pinStepRight, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStepLeft, LOW);
    digitalWrite(pinStepRight, LOW);
    delayMicroseconds(pulseTime);
  }



  double rate = startingRate;
  while(rate < finalRate){
    int pulseTime = (int)(1000000.0/rate);
    digitalWrite(pinStepLeft, HIGH);
    digitalWrite(pinStepRight, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStepLeft, LOW);
    digitalWrite(pinStepRight, LOW);
    delayMicroseconds(pulseTime);
    stepCount++;
    rate += accelRate;
  }

  while(stepCount < endCruise){
    int pulseTime = (int)(1000000.0/finalRate);
    digitalWrite(pinStepLeft, HIGH);
    digitalWrite(pinStepRight, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStepLeft, LOW);
    digitalWrite(pinStepRight, LOW);
    delayMicroseconds(pulseTime);
    stepCount++;
    delayMicroseconds(20);
  }

  rate = finalRate;
  while(rate > startingRate){
    int pulseTime = (int)(1000000.0/rate);
    digitalWrite(pinStepLeft, HIGH);
    digitalWrite(pinStepRight, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStepLeft, LOW);
    digitalWrite(pinStepRight, LOW);
    delayMicroseconds(pulseTime);
    stepCount++;
    rate -= accelRate;
  }
}

void loop(){


}

