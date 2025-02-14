#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensor pins
#define sensorPower 2
#define sensorPin A0

#define relayPin 6

// Create LCD object (address 0x27 is common for many I2C LCDs, but you might need to adjust it based on your setup)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address and size if needed

// Value for storing water level
int val = 0;

void setup() {
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  // Set to LOW so no power flows through the sensor initially
  digitalWrite(sensorPower, LOW);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin();
  lcd.backlight();  // Turn on the LCD backlight
  lcd.clear();      // Clear the display
  lcd.setCursor(0, 0); // Move cursor to the first line

}

void loop() {
  // Get the reading from the sensor
  int level = readSensor();
  
  // Print the water level to the serial monitor
  Serial.print("Water level: ");
  Serial.println(level);
  
  // Display water level on LCD
  lcd.setCursor(0, 1); // Move cursor to the second line
  lcd.print("Level: ");
  lcd.print(level); // Print the actual sensor value on the LCD

  // Check if water level is high (above 500)
  if (level > 500) {
    lcd.setCursor(0, 1); // Move cursor back to second line to overwrite
    lcd.print("Water High");  // Display message when water level is high
    
    // If you want to show a custom message like "CHC", you can replace it
    // lcd.print("CHC");
    
    // Optional: Activate relay or other actions if needed
    digitalWrite(relayPin, HIGH);  // Turn on relay if water level is high
  } else {
    // If water level is not high, just display the normal level
    lcd.setCursor(0, 1);  // Move cursor to the second line again
    lcd.print("Water Safe"); // Display message if water level is safe
    digitalWrite(relayPin, LOW);  // Turn off relay if water level is safe
  }

  delay(1000);  // Update every second
}

// Function to read the sensor and return the value
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);                        // Wait 10 milliseconds
  val = analogRead(sensorPin);      // Read the analog value from the sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;                       // Return the current reading
}
