#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// -- IMPORTS -- //

LiquidCrystal_I2C lcd(0x27, 16, 2); // SDA -> 4, SCL -> 5 (swap if wrong)
SoftwareSerial SIM900(0, 1); // RX | TX

// -- CONSTANTS (PINS) -- //

// Water Well
#define WS_WELL_POW 3    // Power for the water sensor
#define WS_WELL_SIG A0   // Water level sensor analog input

// Water Ground
#define WS_GROUND_POW 4
#define WS_GROUND_SIG A1

// Motor 1
#define EN_A 5   // Motor speed control (PWM)
#define IN_1 6   // Motor direction
#define IN_2 7   // Motor direction

// Motor 2
#define EN_B 8
#define IN_3 9
#define IN_4 10

// -- CONSTANTS (VALUES) -- //

// Motor
#define SPD_CLOSE 0
#define SPD_HALF 128
#define SPD_FULL 255

// Watur
#define ADD_W_LVL 250
#define W_INDICATOR "Well: "
#define G_INDICATOR "Ground: "

// -- STATES -- //

int w_well_lvl = 0;
int w_ground_lvl = 0;

void setup() {
  Serial.begin(9600);  // Start serial monitor for debugging
  while(!Serial);
  SIM900.begin(9600);

  // Set pin modes for water sensors
  pinMode(WS_WELL_POW, OUTPUT);
  pinMode(WS_WELL_SIG, INPUT);
  pinMode(WS_GROUND_POW, OUTPUT);
  pinMode(WS_GROUND_SIG, INPUT);

  // Set pin modes for Motor Control Pins 1
  pinMode(EN_A, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

  // Set pin modes for Motor Control Pins 2
  pinMode(EN_B, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  // Ensure motors are initially off
  moveMotor(IN_1, IN_2, EN_A, SPD_CLOSE);
  moveMotor(IN_3, IN_4, EN_B, SPD_CLOSE);

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
  w_well_lvl = read_water_lvl(WS_WELL_POW, WS_WELL_SIG) + ADD_W_LVL;
  w_ground_lvl = read_water_lvl(WS_GROUND_POW, WS_GROUND_SIG) + ADD_W_LVL;

  // LCD Loop Logic

  Serial.print(W_INDICATOR + w_well_lvl);
  Serial.print(G_INDICATOR +  w_ground_lvl);

  lcd.setCursor(0, 1);
  lcd.print(W_INDICATOR + w_well_lvl);

  lcd.setCursor(0, 2);
  lcd.print(G_INDICATOR + w_ground_lvl);


  // -- SIM900 Loop Logic -- //

  if (Serial.available() > 0)
   switch(Serial.read())
  {
    case 's':
     
      break;
    case 'r':
      
      break;
  }

 if (SIM900.available() > 0) {
   Serial.write(SIM900.read());
 }

  
  
  delay(1000);  
}

// -- FUNCTIONS -- //

int read_water_lvl(int powPin, int signalPin) {
  digitalWrite(powPin, HIGH); 
  delay(50);  
  int val = analogRead(signalPin); // read signal 
  digitalWrite(powPin, LOW); // Power off sensor
  return val;
}

// in_F = forward pin (could be en1 or en3)
// in_B = backward pin (could be en2 or en4)
// en_ = accelerator pin (could be enA or enB)

void moveMotor(int in_F, int in_B, int en_, int speed) {

  int state;

  if (speed > 0) {
    state = HIGH;
  }
  else {
    state = LOW;
  }

  digitalWrite(in_F, state);
  digitalWrite(in_B, LOW);

  analogWrite(en_, speed);  
}


// SIM900 Functions
void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900.println("AT+CMGS=\"+6281542787536\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900.println("Good morning, how are you doing?");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS Selesai dikirim");
}

void RecieveMessage()
{
  Serial.println ("SIM900A Membaca SMS");
  delay (1000);
  SIM900.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
 }
