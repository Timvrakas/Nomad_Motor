//PIN CONFIGURATION
const int pinEnable = 17;
const int pinStep = 32;
const int pinDir = 33;
const int limitPin = 0; //NEED

const int LOW_POS = 100;
const long HIGH_POS = 5000;
unsigned long pos;
boolean dir;

const bool UP = 1;
const bool DOWN = 0;

void setup() {
  pinMode(pinEnable, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);

  digitalWrite(pinEnable, LOW);

  delay(1000);
  long stepCount = 0;

  //Lower until limit switch is triggered
  dir = DOWN;
  digitalWrite(pinDir, dir);
  int pulseTime = 10;
  while (digitalRead(limitPin) == LOW) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(pulseTime);
  }

  //Raise to "Low" position
  dir = UP;
  pulseTime = 10;
  digitalWrite(pinDir, dir);
  for (int i = 0; i < LOW_POS; i++) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(pulseTime);
  }
  pos = 0;
}

void loop() {
  //convert to radians
  float angle = float(map(pos, LOW_POS, HIGH_POS, 0, 180)) / 114.59;
  long pulseTime = 1000000 / long((sin(angle) + 0.1));
  int increment;
  if (dir == UP) {
    increment = 1;
  } else {
    increment = -1;
  }

  digitalWrite(pinDir, dir);
  for (int i = 0; i < 100; i++) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(pulseTime);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(pulseTime);
    pos += increment;
  }

  if (pos >= HIGH_POS) {
    dir = DOWN;
  } else if (pos <= LOW_POS) {
    dir = UP;
  }
}
