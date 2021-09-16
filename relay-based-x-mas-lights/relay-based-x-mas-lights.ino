
#define PIN_COUNT 8 // the number of pins (i.e. the length of the array)

#define ANALOG_INPUT A0 //MIC audio input reading
#define MEAN 25//512  //Mean value used for centering on Zero
#define DC_OFFSET 0 // DC offset in mic signal - if unusure, leave 0
#define NOISE 10  // Noise/hum/interference in mic signal

#define PEAK_THRESOLD 70 //sensitivity
#define LED_ON_TIME 100 //100ms
#define LED_OFF_TIME 100 //100ms

int lvl = 0;  // Current "dampened" audio level

int ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9
}; // an array of pin numbers to which LEDs are attached


void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_INPUT, INPUT);
  for (int thisPin = 0; thisPin < PIN_COUNT; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);
  }
}

void loop() {
  //listen to audio input and calculate level
  int n;
  n = analogRead(ANALOG_INPUT);

  //    Serial.println(n);

  n = abs(n - MEAN - DC_OFFSET);        // Center on zero
  n = (n <= NOISE) ? 0 : (n - NOISE);  // Remove noise/hum/
  lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)

  Serial.println(lvl);

  if (lvl > PEAK_THRESOLD) { // action
    //based on lvl turn on of LED lights
    int randomPin = getRandomPinWithinRange(0, 9);
    turnPinOnAndOff(randomPin);
  }
  else {
    //turn off all LEDs
    for (int thisPin = 0; thisPin < PIN_COUNT; thisPin++) {
      digitalWrite(ledPins[thisPin], LOW);
    }
  }
}

void turnPinOnAndOff(int pinNum) {
  int randomPairBulbs =  getRandomPinWithinRange(0, 3);
  switch (randomPairBulbs) {

    case 0:
      digitalWrite(ledPins[pinNum], HIGH);
      digitalWrite(ledPins[pinNum] + 3, HIGH);
      delay(LED_ON_TIME);
      digitalWrite(ledPins[pinNum], LOW);
      digitalWrite(ledPins[pinNum] + 3, LOW);
      delay(LED_OFF_TIME);
      break;

    case 1:
      digitalWrite(ledPins[pinNum], HIGH);
      digitalWrite(ledPins[pinNum] + 2, HIGH);
      delay(LED_ON_TIME);
      digitalWrite(ledPins[pinNum], LOW);
      digitalWrite(ledPins[pinNum] + 2, LOW);
      delay(LED_OFF_TIME);
      break;

    case 2:
      digitalWrite(ledPins[pinNum], HIGH);
      digitalWrite(ledPins[pinNum] + 1, HIGH);
      delay(LED_ON_TIME);
      digitalWrite(ledPins[pinNum], LOW);
      digitalWrite(ledPins[pinNum] + 1, LOW);
      delay(LED_OFF_TIME);
      break;

    case 3:
      digitalWrite(ledPins[pinNum], HIGH);
      digitalWrite(ledPins[pinNum] + 0, HIGH);
      delay(LED_ON_TIME);
      digitalWrite(ledPins[pinNum], LOW);
      digitalWrite(ledPins[pinNum] + 0, LOW);
      delay(LED_OFF_TIME);
      break;

  }
}

int getRandomPinWithinRange(int startPin, int endPin) {
  int pinToTurnOn =  random(startPin, endPin);
  return  pinToTurnOn;
}
