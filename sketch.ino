// Pin definitions for traffic lights
const int trafficRed = 2;
const int trafficYellow = 3;
const int trafficGreen = 4;

// Pin definitions for pedestrian lights
const int pedRed = 5;
const int pedGreen = 6;

// Push button pins
const int button1 = 10;
const int button2 = 11;

// Buzzer pin
const int buzzer = 12;

// Timing variables (milliseconds)
int pedestrianGreenTime = 5000; // Default 5 seconds for pedestrian
const unsigned long buttonCooldown = 20000; // 20-second cooldown for lights
const unsigned long buttonWaitTime = 10000; // 10 seconds wait time
const unsigned long buttonWaitHalfTime = 5000; // 5 seconds if both buttons are pressed

// Variables to track button cooldown and state
unsigned long lastButtonPressTime = 0;
bool isCooldownActive = false;

void setup() {
  // Initialize pins as outputs or inputs
  pinMode(trafficRed, OUTPUT);
  pinMode(trafficYellow, OUTPUT);
  pinMode(trafficGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  // Initial state: traffic light is green, pedestrian light is red
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficGreen, HIGH);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);
}

void loop() {
  // Check if either button is pressed and if cooldown is not active
  if ((digitalRead(button1) == LOW || digitalRead(button2) == LOW) && !isCooldownActive) {
    // Determine the pedestrian wait time based on button conditions
    if (digitalRead(button1) == LOW && digitalRead(button2) == LOW) {
      pedestrianGreenTime = 2500; // Halve the pedestrian green time if both buttons are pressed
      delay(buttonWaitHalfTime); // Wait for 5 seconds before changing lights
    } else {
      pedestrianGreenTime = 5000; // Default time for one button
      delay(buttonWaitTime); // Wait for 10 seconds before changing lights
    }

    // Start pedestrian crossing sequence
    pedestrianCrossing();

    // Activate the cooldown
    lastButtonPressTime = millis();
    isCooldownActive = true;
  }

  // Check if the cooldown period has ended
  if (isCooldownActive && (millis() - lastButtonPressTime >= buttonCooldown)) {
    isCooldownActive = false; // Reset cooldown
  }
}

void pedestrianCrossing() {
  // Stop traffic by switching to red light
  digitalWrite(trafficGreen, LOW);
  digitalWrite(trafficRed, HIGH);

  // Turn the pedestrian red light off and green light on
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);

  // Activate the buzzer to indicate the pedestrian green light
  for (int i = 0; i < 3; i++) { // Buzzer beeps three times
    digitalWrite(buzzer, HIGH);
    delay(500); // Buzzer sounds for 500ms
    digitalWrite(buzzer, LOW);
    delay(500); // Pause for 500ms
  }

  // Keep the pedestrian light green for the set time
  delay(pedestrianGreenTime);

  // Turn the pedestrian green light off and red light on
  digitalWrite(pedGreen, LOW);
  digitalWrite(pedRed, HIGH);

  // Turn traffic light back to green
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficGreen, HIGH);
}
