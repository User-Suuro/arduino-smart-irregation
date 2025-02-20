#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define sensorPower 2    // Power for the water sensor
#define sensorPin A0     // Water level sensor analog input

// Motor Control Pins
int enA = 3;   // Motor speed control (PWM)
int in1 = 4;   // Motor direction
int in2 = 5;   // Motor direction

// LCD Setup (I2C Address: 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Water Level Variable
int waterLevel = 0;

void setup() {
  Serial.begin(9600);  // Start serial monitor for debugging

  // Set pin modes
  pinMode(sensorPower, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Ensure motor is initially off
  closeMotor();

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");

  delay(1000); // Small delay for LCD startup
}

void loop() {
  // Read water level
  waterLevel = readSensor();

  // Debugging: Print water level to Serial Monitor
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" (Raw Sensor Value)");

  // Clear LCD row before updating
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clears previous text

  // Display water level on LCD
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(waterLevel);

  // Control motor based on water level
  if (waterLevel < 389) {
    closeMotor();
    lcd.setCursor(0, 1);
    lcd.print(" MOTOR CLOSED  ");
    Serial.println("Pump OFF (Motor Closed)");
  } 
  else if (waterLevel > 390 && waterLevel <= 510) {
    halfOpenMotor();
    lcd.setCursor(0, 1);
    lcd.print("MOTOR HALF-OPEN");
    Serial.println("Pump Running at 50%");
  } 
  else {
    fullOpenMotor();
    lcd.setCursor(0, 1);
    lcd.print("MOTOR FULL OPEN");
    Serial.println("Pump Running at 100%");
  }

  delay(2000);  // Update every 2 seconds
}

// Function to read water level sensor
int readSensor() {
  digitalWrite(sensorPower, HIGH); // Power on sensor
  delay(50);  // Increased delay for stable reading
  int val = analogRead(sensorPin); // Read sensor data
  digitalWrite(sensorPower, LOW); // Power off sensor
  return val;
}

// Function to stop motor (CLOSED)
void closeMotor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);  // Motor off
}

// Function for half-open motor (LOW SPEED)
void halfOpenMotor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 128);  // 50% Speed
}

// Function for full-open motor (FULL SPEED)
void fullOpenMotor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);  // 100% Speed
}
