#include<SoftwareSerial.h>
#include<string.h>
#define TXD 3
#define RXD 2
SoftwareSerial BTserial(RXD, TXD);

char c = ' ';
boolean btConnected = false;
const int state = 7;
String str = "Hello";

void wait4Conection();

void setup() {
  pinMode(state, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino is Ready");
  Serial.println("Waiting for HC-05 to connect to Android device");

  wait4Conection();
  Serial.println("HC-05 Connected"); 
}

void loop() {
  //check for connection status every time
  if(digitalRead(state) == LOW) { // connection lost
    Serial.println("Connection lost. Wait for connection..");
    wait4Conection();
  }
  
  if(BTserial.available()) {
    c = BTserial.read();
    Serial.write(c);
  }
  
  for(unsigned int i=0; i<str.length(); i++) {
    BTserial.write(str[i]);
    delay(100);
  }
  Serial.flush();
}

void wait4Conection() {
  while(!btConnected) {
    if(digitalRead(state) == HIGH) btConnected = true;
  }
  BTserial.begin(9600); // Starting Serial communication with the Module
  return ;
}
