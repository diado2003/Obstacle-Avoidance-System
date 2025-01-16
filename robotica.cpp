#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 6;

// LED pins
const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;

// Buzzer pin
const int buzzerPin = 7;

// Number of samples for averaging
const int numSamples = 10;

// Maximum count for distance display
const int maxCount = 9999;

// LCD (I2C address - adjust based on your setup)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Use 0x27 or 0x3F depending on your I2C address

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();

  // Configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configure LED pins
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Configure buzzer pin
  pinMode(buzzerPin, OUTPUT);
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


// Calculate a smoothed (averaged) distance
int calculateSmoothedDistance() {
  long totalDistance = 0;

  for (int i = 0; i < numSamples; i++) {
    totalDistance += calculateDistance();
    delay(50); // Short delay between samples for stability
  }

  return totalDistance / numSamples; // Return the average distance
}

// Display the distance on the LCD
void displayDistanceOnLCD(int distance) {
  lcd.setCursor(0, 0);
  lcd.print("Distance:       "); // Overwrite existing text
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print(" cm");
}

// Control the LEDs and buzzer based on the distance
void controlLEDsAndBuzzer(int distance) {
  if (distance < 10) {
    // Object is too close: Red LED and buzzer ON
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH); // Turn the buzzer ON
    lcd.setCursor(1, 1);
    lcd.print("Franeaza");
  } else if (distance >= 10 && distance < 50) {
    // Object is somewhat close: Yellow LED ON
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, LOW); // Turn the buzzer OFF
    lcd.setCursor(1, 1);
    lcd.print("Apropiere");
  } else {
    // Path is clear: Green LED ON
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW); // Turn the buzzer OFF
    lcd.setCursor(1, 1);
    lcd.print("Drum liber");
  }
}


void loop() {
  int distance = calculateSmoothedDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  displayDistanceOnLCD(distance);
  controlLEDsAndBuzzer(distance);

  delay(100); // Delay for stability
}


