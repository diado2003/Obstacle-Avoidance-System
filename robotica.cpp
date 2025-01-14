#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// 7-segment display setup
Adafruit_7segment matrix = Adafruit_7segment();
const int maxCount = 9999;

// Ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 6;

// LED pins
const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;

// DC motor pin
const int motorPin = 7;

// Number of samples for averaging
const int numSamples = 10;

// Function Prototypes
int calculateDistance();
void displayDistance(int distance);
void controlLEDs(int distance);
void controlDCMotor(int distance);

void setup() {
  Serial.begin(9600);

  // Initialize 7-segment display
  matrix.begin(0x70);
  matrix.println(0);
  matrix.writeDisplay();

  // Configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configure LED pins
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Configure motor pin
  pinMode(motorPin, OUTPUT);
}

void loop() {
  int distance = calculateDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  displayDistance(distance);
  controlLEDs(distance);
  controlDCMotor(distance);

  delay(100); // Delay for stability
}

// Calculate distance using the ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration / 29 / 2; // Convert duration to distance in cm
}

int calculateSmoothedDistance() {
  long totalDistance = 0;

  for (int i = 0; i < numSamples; i++) {
    totalDistance += calculateDistance();
    delay(50); // Short delay between samples for stability
  }

  return totalDistance / numSamples; // Return the average distance
}


// Display the distance on the 7-segment display
void displayDistance(int distance) {
  if (distance <= maxCount) {
    matrix.println(distance);
    matrix.writeDisplay();
  }
}

// Control the LEDs based on the distance
void controlLEDs(int distance) {
  if (distance < 10) {
    // Object is too close: Red LED ON
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
  } else if (distance >= 10 && distance < 50) {
    // Object is somewhat close: Yellow LED ON
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  } else {
    // Path is clear: Green LED ON
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
}

// Control the DC motor based on distance
void controlDCMotor(int distance) {
  if (distance < 10) {
    analogWrite(motorPin, 0); // Stop the motor if too close
  } else {
    analogWrite(motorPin, 255); // Run the motor at full speed otherwise
  }
}
