#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>



// D7 (RX) (ESP) -> TX (ARDUINO)
// D8 (TX) (ESP) -> RX (ARDUINO)

//SoftwareSerial espSerial(4, 0);  // (D2 = 4) RX, (D3 = 0) TX pins for ESP8266 (you can use any available pins)
SoftwareSerial sendSerial(15, 13);  


// WIFI static const char *AP_SSID = "Mhico"
#define AP_PASS "09292004"

// API
#define account_ssid = "85a60303-ff84-4d30-ac54"
#define auth_token = "639946826707"

#define from_number = "+18573805833"
#define to_number = "+639946826707"

WiFiManager wifiManager;

Twilio *twilio;


bool init_sms = false;

void setup() {
  Serial.begin(9600);
  sendSerial.begin(9600);
  //espSerial.begin(9600);

  while (true) {
       if (connectToWifi(AP_SSID, AP_PASS)) {
          
          break;
      } 
  }



  
 
}

void loop() {
  
  if(Serial.available()){
 
  }




  
  delay(1000);

}



// -- FUNCTIONS -- //

bool connectToWifi(String ssid, String password) {

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  int maxAttempts = 20;  // Set a timeout (10 seconds)

  while (WiFi.status() != WL_CONNECTED && maxAttempts > 0) {
    delay(500);
    Serial.print(".");
    maxAttempts--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWi-Fi connection failed!");
    return false;
  }

  Serial.println("\nWi-Fi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  return true;
}
