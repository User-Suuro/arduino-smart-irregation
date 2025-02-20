#include <SoftwareSerial.h>

SoftwareSerial sendSerial(13, 15);  // (D2 = 4) RX, (D3 = 0) TX pins for ESP8266 (you can use any available pins)

void setup() {
  Serial.begin(9600);     //  Begin local serial
  sendSerial.begin(9600);  // esp -> arduino
}

void loop() {
  sendSerial.write("0");
  delay(1000);
  sendSerial.write("1");
  delay(1000);

  if(Serial.available()){
    //read response
    String sent = Serial.readString();
    Serial.println(sent);
  }


}

