
byte symbols[] = {
B11111100, // 0
B01100000, // 1
B11011010, // 2
B11110010, // 3
B01100110, // 4
B10110110, // 5
B10111110, // 6
B11100000, // 7
B11111110, // 8
B11110110, // 9
B11101110, // A
B00111110, // B
B10011100, // C
B01111010, // D
B10011110, // E
B10001110  // F
};

class Digits {
  private:
    byte digit[3];
    int index0, index1, index2;

  public:
    //constructor
    Digits() {
      digit[0] = symbols[0];
      digit[1] = symbols[0];
      digit[1] = symbols[0];
      index0 = 0;
      index1 = 0;
      index2 = 0;
    }

    void inc() 
    {
        if(index0 == 9)
        {
          if(index1 == 5) 
          {
            if(index2 == 9)
            {
              index2 = 0;
            } else index2++;
            
            index1 = 0;
          } else index1++;

          index0 = 0;
        } else index0++;
        
        digit[0] = symbols[index0];
        digit[1] = symbols[index1];
        digit[2] = symbols[index2];
    }

    //incrementing a particular digit
    void inc0() {
      if(index0 == 9) {
        index0 = 0;
      } else index0++;
    }
    void inc1() {
      if(index1 == 5) {
        index1 = 0;
      } else index1++;
    }
    void inc2() {
      if(index2 == 9) {
        index2 = 0;
      } else index2++;
    }
    
    byte get_num0() {
      return digit[0];
    }
    byte get_num1() {
      return digit[1];
    }
    byte get_num2() {
      return digit[2];
    }
        
};

int data_pin = 4;
int clk_pin = 3;
int cathode[] = {5,6,7};
int j = 0;
Digits clock_data; //Digit Object having all the three digits

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(cathode[j], OUTPUT);
 
}

void loop() {
   
    digitalWrite(clk_pin, LOW);
    digitalWrite(cathode[j], HIGH);
    shiftOut(data_pin, clk_pin, LSBFIRST, clock_data.get_num0());
    digitalWrite(cathode[j], LOW);
    delay(500);
    clock_data.inc();

}
