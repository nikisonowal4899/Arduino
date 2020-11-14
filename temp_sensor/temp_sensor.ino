const int sensorInput = A0;
double R = 10000, Rt;
double logRt;
double A = 0.001125308852122, B =  0.000235711863267, C =  0.000000085663516; // Steinhart Hart coefficients
double Temperature;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  double Vin = analogRead(sensorInput);
  Vin = (5.0/1023.0) * Vin; // Now signal is in 0-5 V range
  Rt = (R*5.0/Vin) - R; // Rt is the thermistor resistance
  logRt = log(Rt);
  Temperature = 1.0/(A + B*logRt + C*logRt*logRt*logRt);
  Temperature = Temperature - 273.15; // Temperature in celcius

  Serial.print("Temperature: "); 
  Serial.print(Temperature);
  Serial.println(" °C"); 


  
  delay(1000);
}
