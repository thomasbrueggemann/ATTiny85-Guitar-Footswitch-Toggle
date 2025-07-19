// Remove OneButtonTiny includes and usage
// Pin definitions for ATTiny85
#define BUTTON1_PIN 3 // physical pin 2
#define BUTTON2_PIN 4 // physical pin 3
#define OUT1_PIN    1 // physical pin 6
#define OUT2_PIN    2 // physical pin 7

// Remove debounce settings and variables

// State variables for toggling
bool out1Active = false;
bool out2Active = false;
bool lastButton1State = HIGH;
bool lastButton2State = HIGH;

void setOut1HighOut2Low() {
  digitalWrite(OUT1_PIN, HIGH);
  digitalWrite(OUT2_PIN, LOW);
  out1Active = true;
  out2Active = false;
}

void setOut2HighOut1Low() {
  digitalWrite(OUT2_PIN, HIGH);
  digitalWrite(OUT1_PIN, LOW);
  out2Active = true;
  out1Active = false;
}

void setBothOff() {
  digitalWrite(OUT1_PIN, LOW);
  digitalWrite(OUT2_PIN, LOW);
  out1Active = false;
  out2Active = false;
}

// Counter-based debounce settings
const int debounceCount = 200; // Number of stable reads required
int button1StableCount = 0;
int button2StableCount = 0;
bool debouncedButton1State = HIGH;
bool debouncedButton2State = HIGH;

void setup() {
  // Set output pins as outputs and pull LOW at startup
  pinMode(OUT1_PIN, OUTPUT);
  pinMode(OUT2_PIN, OUTPUT);
  digitalWrite(OUT1_PIN, LOW);
  digitalWrite(OUT2_PIN, LOW);

  // Set button pins as input with internal pull-up resistors
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  // Read the current state of the buttons (active LOW)
  bool reading1 = digitalRead(BUTTON1_PIN);
  bool reading2 = digitalRead(BUTTON2_PIN);

  // Counter-based debounce for button 1
  if (reading1 != debouncedButton1State) {
    button1StableCount++;
    if (button1StableCount >= debounceCount) {
      debouncedButton1State = reading1;
      button1StableCount = 0;
    }
  } else {
    button1StableCount = 0;
  }

  // Counter-based debounce for button 2
  if (reading2 != debouncedButton2State) {
    button2StableCount++;
    if (button2StableCount >= debounceCount) {
      debouncedButton2State = reading2;
      button2StableCount = 0;
    }
  } else {
    button2StableCount = 0;
  }

  // Edge detection for button 1 (HIGH to LOW)
  if (lastButton1State == HIGH && debouncedButton1State == LOW) {
    if (!out1Active) {
      setOut1HighOut2Low();
    } else {
      setBothOff();
    }
  }
  lastButton1State = debouncedButton1State;

  // Edge detection for button 2 (HIGH to LOW)
  if (lastButton2State == HIGH && debouncedButton2State == LOW) {
    if (!out2Active) {
      setOut2HighOut1Low();
    } else {
      setBothOff();
    }
  }
  lastButton2State = debouncedButton2State;
} 