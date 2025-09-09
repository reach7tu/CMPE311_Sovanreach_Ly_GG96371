const int led1Pin = 2;
const int led2Pin = 3;

unsigned long led1Interval = 0;  // default interval (time between blink)
unsigned long led2Interval = 0;

unsigned long led1PreviousTime = 0; // last blink time
unsigned long led2PreviousTime = 0;

bool led1State = false; // state of led
bool led2State = false;

enum InputState {WAIT_LED, WAIT_INTERVAL};
InputState inputState = WAIT_LED;

int tempLed = 0;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("What LED? (1 or 2)");
}

void loop() {
  unsigned long timeNow = millis(); // current time

  // Handle blinking for LED 1
  if (led1Interval > 0 && timeNow - led1PreviousTime >= led1Interval) {
    led1PreviousTime = timeNow;
    led1State = !led1State;
    digitalWrite(led1Pin, led1State);
  }

  // Handle blinking for LED 2
  if (led2Interval > 0 && timeNow - led2PreviousTime >= led2Interval) {
    led2PreviousTime = timeNow;
    led2State = !led2State;
    digitalWrite(led2Pin, led2State);
  }

  // Handle user input
  if (Serial.available()) {
    int value = Serial.parseInt();

    // handle What LED?
    if (inputState == WAIT_LED) {
      // only ask for interval if valid LED is inputted
      if (value == 1 || value == 2) {
        tempLed = value;
        Serial.println("What interval? (in ms)");
        inputState = WAIT_INTERVAL;
      }
      else {
        Serial.println("What LED? (1 or 2)");
      }
    }

    // handle What interval?
    else if (inputState == WAIT_INTERVAL) {
      // put value of interval to LED inputted
      if (tempLed == 1) {
        led1Interval = value;
      }
      else if (tempLed == 2) {
        led2Interval = value;
      }

      // Repeat
      Serial.println("What LED? (1 or 2)");
      inputState = WAIT_LED;
    }
  }
}
