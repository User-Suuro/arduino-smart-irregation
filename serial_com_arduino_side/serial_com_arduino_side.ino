#include <SoftwareSerial.h>

// D3(TX) (ARDUINO) -> RX (ESP)
// D2(RX) (ARDUINO) -> TX (ESP) 

SoftwareSerial sendSerial(2, 3);  

void setup() {
  // beging local serial
  Serial.begin(9600);
  // arduino -> esp
  sendSerial.begin(9600);

}

void loop() {
  sendSerial.println("hatdog");
  sendSerial.flush();

  
   if(Serial.available()){
    //read response
    String sent = Serial.readStringUntil('#');
    Serial.println(sent);
  }
  delay(1000);
}

