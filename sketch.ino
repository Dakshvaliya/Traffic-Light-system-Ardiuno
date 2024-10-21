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
int pedestrianGreenTime = 5000; // Default 5 seconds
const int yellowLightTime = 2000; // Yellow light duration
const int redLightTime = 5000; // Red light duration

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

  // Initial state: traffic light is red, pedestrian light is red
  digitalWrite(trafficRed, HIGH);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficGreen, LOW);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);
}

void loop() {
  // Check if either or both pedestrian buttons are pressed
  bool button1Pressed = (digitalRead(button1) == LOW);
  bool button2Pressed = (digitalRead(button2) == LOW);

  if (button1Pressed || button2Pressed) {
    // If both buttons are pressed, halve the pedestrian green time
    if (button1Pressed && button2Pressed) {
      pedestrianGreenTime = 2500; // Half the time
    } else {
      pedestrianGreenTime = 5000; // Default time
    }

    // Activate the pedestrian crossing sequence
    pedestrianCrossing();
  } else {
    // Normal traffic light cycle
    changeTrafficLights(trafficGreen, yellowLightTime, trafficRed, redLightTime);
  }
}

void changeTrafficLights(int greenLight, int yellowDuration, int redLight, int redDuration) {
  // Green light on
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(greenLight, HIGH);
  delay(yellowDuration);

  // Yellow light on
  digitalWrite(greenLight, LOW);
  digitalWrite(trafficYellow, HIGH);
  delay(redDuration);

  // Red light on
  digitalWrite(trafficYellow, LOW);
  digitalWrite(redLight, HIGH);
}

void pedestrianCrossing() {
  // Stop traffic by switching to red light
  digitalWrite(trafficGreen, LOW);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficRed, HIGH);

  // Turn the pedestrian red light off and green light on
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);

  // Activate the buzzer to indicate the pedestrian green light
  digitalWrite(buzzer, HIGH);
  delay(500); // Buzzer sounds for 500ms
  digitalWrite(buzzer, LOW);
  delay(500); // Pause for 500ms
  digitalWrite(buzzer, HIGH);
  delay(500); // Buzzer sounds for another 500ms
  digitalWrite(buzzer, LOW);

  // Keep the pedestrian light green for the set time
  delay(pedestrianGreenTime);

  // Turn the pedestrian green light off and red light on
  digitalWrite(pedGreen, LOW);
  digitalWrite(pedRed, HIGH);

  // Resume normal traffic light cycle
  delay(1000); // Small delay before resuming traffic lights
  changeTrafficLights(trafficGreen, yellowLightTime, trafficRed, redLightTime);
}
