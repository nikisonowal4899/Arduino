#include <LiquidCrystal.h>

const int rs = 8, en = 9;
const int d4 = 7, d5 = 6, d6 = 5, d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// temperature module
const int sensorInput = A0;
double R = 10000, Rt;
double logRt;
double A = 0.001125308852122, B =  0.000235711863267, C =  0.000000085663516; // Steinhart Hart coefficients
double Temperature;
double tempModule(void); // returns the temperature in degree celcius
//

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // LCD used in 16x2 mode
  lcd.clear();

  lcd.print("Room Temperature");
  
  
}

void loop() {
  double temperature = tempModule(); // got the room temperature from the sensor
  String str = String(temperature) + " deg C";
  lcd.setCursor(0,1);
  lcd.print(str);
  delay(700); // update every 700 ms
}

double tempModule() { // take the temp reading from the sensor
  double Vin = analogRead(sensorInput);
  Vin = (5.0/1023.0) * Vin; // Now signal is in 0-5 V range
  Rt = (R*5.0/Vin) - R; // Rt is the thermistor resistance
  logRt = log(Rt);
  Temperature = 1.0/(A + B*logRt + C*logRt*logRt*logRt); // Steinhart Hart equation
  Temperature = Temperature - 273.15; // Temperature in celcius
  
  Serial.print("Temperature: "); 
  Serial.print(Temperature);
  Serial.println(" °C"); 

  return Temperature;
}
