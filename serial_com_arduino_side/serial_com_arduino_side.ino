#include <SoftwareSerial.h>

SoftwareSerial sendSerial(2, 3);  // RX, TX (connect to ESP8266 TX, RX)

void setup() {
  // beging local serial
  Serial.begin(9600);
  // arduino -> esp
  sendSerial.begin(9600);

}

void loop() {

  if(Serial.available()) {
    int state = Serial.parseInt();

    if (state == 1) {
      Serial.println("Command Received: 1");
      // send response
      sendSerial.println("1 daw sabi ng arduino");
    }

    if (state == 0) {
      Serial.println("Command Received: 0");
       // send response
      sendSerial.println("0 daw sabi ng arduino");
    }

  }
  Serial.println("a");
  delay(1000);
}

