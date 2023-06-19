int analogPin = A15;
double sensorValue;
double t1, t2, delT;

void setup() {
 Serial.begin(19200);
}

// the loop routine runs over and over again forever:
void loop() {

 while(true) {
   sensorValue = analogRead(analogPin);
   sensorValue = sensorValue * (5.0/1023.0);
   if(sensorValue > 1) {
     t1 = millis();
     break;
   }
   delay(10);
 }

 while(true) {
   sensorValue = analogRead(analogPin);
   sensorValue = sensorValue * (5.0/1023.0);
   if(sensorValue < 1) {
     t2 = millis();
     break;
   }
   delay(10);
 }

 delT = t2 - t1;
 Serial.println(1000/(2*delT));


}














