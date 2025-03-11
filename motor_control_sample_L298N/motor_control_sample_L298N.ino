int enA=7;
int in1=6;
int in2=5;

void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hatdog");
  directionControl();
  delay(1000);
  speedControl();
  delay(1000);
}

void directionControl (){
  analogWrite(enA,255);
  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  delay(2000);

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  delay(2000);

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

}

void speedControl() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  for (int i=0; i<256; i++){
    analogWrite(enA,i);
    delay(20);
  }

  for(int i=255; i>=0;i--){
    analogWrite(enA,i);
    delay(20);
  }

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  }

