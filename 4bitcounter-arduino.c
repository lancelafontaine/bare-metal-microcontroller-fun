const int UPPER_BOUND = 16;

const int BUTTON_PIN = 7;
const int ZERO_PIN = 2;
const int ONE_PIN = 3;
const int TWO_PIN = 4;
const int THREE_PIN = 5;

int input = 0;
int previousInput = 0;
int count = 0;

void setup() {
  pinMode(ZERO_PIN, OUTPUT);
  pinMode(ONE_PIN, OUTPUT);
  pinMode(TWO_PIN, OUTPUT);
  pinMode(THREE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  input = digitalRead(BUTTON_PIN);
  if (input != previousInput && input == HIGH) {
    count = (count + 1) % UPPER_BOUND;
  }

  digitalWrite(THREE_PIN, count % 2);
  digitalWrite(TWO_PIN,(count/2) % 2);
  digitalWrite(ONE_PIN,(count/4) % 2);
  digitalWrite(ZERO_PIN,(count/8) % 2);

  previousInput = input;
}
