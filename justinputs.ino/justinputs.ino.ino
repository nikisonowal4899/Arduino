#define clockPin 0
#define dataPin 7
#define digitOne 1
#define digitTwo 2
#define digitThree 3
#define onLed 7
#define offLed 8
#define otherLed 6

#define onRelay 9
#define offRelay 8
#define buzzer 10


#define slideSwitch A3
#define pot A5
#define pushButton 2

// initializing variables to avoid garbage
int on_minutes=15, on_hours=1, off_minutes=45, off_hours=2;
int var_index=0, pot_before=0, update_allowed=0;

const byte digit_pattern[16] =
{
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B01110111,  // A
  B01111100,  // b
  B00111001,  // C
  B01011110,  // d
  B01111001,  // E
  B01110001   // F
};     


void setup() {
  Serial.begin(9600);
  
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(digitOne, OUTPUT);
  pinMode(digitTwo, OUTPUT);
  pinMode(digitThree, OUTPUT);
  pinMode(onLed, OUTPUT);
  pinMode(offLed, OUTPUT);
  pinMode(otherLed, OUTPUT);
  
  pinMode(slideSwitch, INPUT);
  pinMode(pot, INPUT);
  pinMode(pushButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButton), buttonPushed, RISING);
  
  
  digitalWrite(digitOne, HIGH);
  digitalWrite(digitTwo, HIGH);
  digitalWrite(digitThree, HIGH);
}

void loop() {
  //if(digitalRead(slideSwitch)){
    pot_before=analogRead(pot);
    takeReadings();
  //}
}
void buttonPushed(){
  var_index=(++var_index)%4;
  pot_before=analogRead(pot);
  update_allowed=0;
}
void takeReadings(){
  for(;;){
    for(int i=0; i<35; i++){
      flashDisplay(true);
      updateVariables();
      Serial.print(var_index); Serial.print(":: "); Serial.print(on_minutes); Serial.print(" "); Serial.print(on_hours); Serial.print(" "); Serial.print(off_minutes); Serial.print(" "); Serial.println(off_hours);
    }
    for(int i=0; i<35; i++){
      flashDisplay(false);
      updateVariables();
      Serial.print(var_index); Serial.print(":: "); Serial.print(on_minutes); Serial.print(" "); Serial.print(on_hours); Serial.print(" "); Serial.print(off_minutes); Serial.print(" "); Serial.println(off_hours);
    }
  }
}
void updateVariables(){
  
  int value=analogRead(pot);
  if(abs(value-pot_before)>20)
    update_allowed=1;
  if(update_allowed==1){
    if(var_index==0)
      on_minutes=map(value, 0, 1023, 0, 59);
    if(var_index==1)
      on_hours=map(value, 0, 1023, 0, 9);
    if(var_index==2)
      off_minutes=map(value, 0, 1023, 0, 59);
    if(var_index==3)
      off_hours=map(value, 0, 1023, 0, 9);
  }
}
void flashDisplay(bool state){
  if(state==true){
    if(var_index==0 || var_index==1){
      digitalWrite(onLed, HIGH);
      digitalWrite(offLed, LOW);
      
      int onesM=on_minutes%10;
      int tensM=(on_minutes-onesM)/10;
      int onesH=on_hours;
      showDigit(onesH, 1, true);
      delay(5);
      showDigit(tensM, 2, false);
      delay(5);
      showDigit(onesM, 3, false);
      delay(5);
    }
    if(var_index==2 || var_index==3){
    digitalWrite(onLed, LOW);
      digitalWrite(offLed, HIGH);
      
      int onesM=off_minutes%10;
      int tensM=(off_minutes-onesM)/10;
      int onesH=off_hours;
      showDigit(onesH, 1, true);
      delay(5);
      showDigit(tensM, 2, false);
      delay(5);
      showDigit(onesM, 3, false);
      delay(5);
    }
  }
  if(state==false){
    digitalWrite(onLed, LOW);
    digitalWrite(offLed, LOW);
      
    if(var_index==0){
      int onesH=on_hours;
      showDigit(onesH, 1, true);
      delay(5);
      deActivate();
      delay(10);
    }
    if(var_index==1){
      int onesM=on_minutes%10;
      int tensM=(on_minutes-onesM)/10;
      
      deActivate();
      delay(5);
      showDigit(tensM, 2, false);
      delay(5);
      showDigit(onesM, 3, false);
      delay(5);
    }
    if(var_index==2){
      
      int onesH=off_hours;
      showDigit(onesH, 1, true);
      delay(5);
      deActivate();
      delay(10);
    }
    if(var_index==3){
      int currentMinutes=off_minutes;
      int onesM=currentMinutes%10;
      int tensM=(currentMinutes-onesM)/10;
      deActivate();
      delay(5);
    showDigit(tensM, 2, false);
      delay(5);
      showDigit(onesM, 3, false);
      delay(5);
    }
  }
}



////////////////////////////////////////////////////////////////////////////////////////////


//show a value on a given Digit
void showDigit(int value, int index, bool includeDP){
  byte outputBits = digit_pattern[value]; // fetch the corresponding byte for a integer 
  if(includeDP == true)
    outputBits = outputBits | B10000000; // perform a bitwise OR to include decimal point
  deActivate();
  shiftOut(dataPin, clockPin, MSBFIRST, outputBits);  // shiftOut takes the byte, performs SIPO on the shift register
  activateDigit(index);
}

/////////////////////////////////////////////////////////////////////////////////////////////////


void activateDigit(int index){
  if(index==1){
    digitalWrite(digitOne, LOW);
    digitalWrite(digitTwo, HIGH);
    digitalWrite(digitThree, HIGH);
  }
  else if(index==2){
    digitalWrite(digitOne, HIGH);
    digitalWrite(digitTwo, LOW);
    digitalWrite(digitThree, HIGH);
  }
  else if(index==3){
    digitalWrite(digitOne, HIGH);
    digitalWrite(digitTwo, HIGH);
    digitalWrite(digitThree, LOW);
  }
  else{
    ;
  }
}
void deActivate(){
  digitalWrite(digitOne, HIGH);
  digitalWrite(digitTwo, HIGH);
  digitalWrite(digitThree, HIGH);
}
