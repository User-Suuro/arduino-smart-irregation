#include <SoftwareSerial.h>


// D7 (RX) (ESP) -> TX (ARDUINO)
// D8 (TX) (ESP) -> RX (ARDUINO)

SoftwareSerial sendSerial(15,13);  

void setup() {
  Serial.begin(9600);     //  Begin local serial
  sendSerial.begin(9600);  // esp -> arduino
} 

void loop() {
  sendSerial.write("cheesedog#");
  sendSerial.flush();

    if(Serial.available()){
      //read response
      String sent = Serial.readString();
      Serial.println("Message:" + sent);
    }

    delay(1000);
  }

