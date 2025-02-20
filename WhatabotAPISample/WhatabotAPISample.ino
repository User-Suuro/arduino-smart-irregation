#include <WhatabotAPIClient.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>

// WIFI 
#define AP_SSID "Mhico"
#define AP_PASS "09292004"

// API 
#define WHATABOT_API_KEY "a227d1bd-9adc-4a50-af39"
#define WHATABOT_CHAT_ID "639946826707"
#define WHATABOT_PLATFORM "whatsapp"

WiFiManager wifiManager;
WhatabotAPIClient whatabotClient(WHATABOT_API_KEY, WHATABOT_CHAT_ID, WHATABOT_PLATFORM);

bool init_sms = false;

void setup() {
  Serial.begin(115200);

  while (true) {
      if (connectToWifi(AP_SSID, AP_PASS)) {
          whatabotClient.begin();
          whatabotClient.onMessageReceived(onMessageReceived); 
          whatabotClient.onServerResponseReceived(onServerResponseReceived);
          break;
      }
  }

 
}

void loop() {
  
  whatabotClient.loop(); 

  if(whatabotClient.getAPIStatus()) {
    Serial.println("hatdog");
  };
  
  delay(500);

}

// -- LIFECYCLES -- //

void onServerResponseReceived(String response) {
  // receives what the bot types
}

void onMessageReceived(String message) {
  Serial.println(message);
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
