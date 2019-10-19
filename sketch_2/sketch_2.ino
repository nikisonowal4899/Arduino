
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
    
    byte get_num(int i) {
      if(i == 0) {
        return digit[0];
      } else if(i ==1) {
        return digit[1];
      } else return digit[2];
    }
    
        
};

const int data_pin = 4;
const int clk_pin = 3;
const int cathode[] = {5,6,7};

Digits clock_data; //Digit Object having all the three digits

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(cathode[0], OUTPUT);
  pinMode(cathode[1], OUTPUT);
  pinMode(cathode[2], OUTPUT); 
  digitalWrite(clk_pin, LOW); //synchronize clock pin [Rising edge trigger],, "Not very necessary step"
}
int index = 0;
void loop() {
  for(int i=0; i<4; i++) {
      deactivate();
      shiftOut(data_pin, clk_pin, LSBFIRST, clock_data.get_num(i));
      activate(i);
      delay(1);
    }
  index++;
  if(index == 245) {
    clock_data.inc();
    index = 0;
  }
}

/*void show_digits() {
  for(int k=0; k<67; k++) {
      for(int i=0; i<3; i++) {
        deactivate();
        shiftOut(data_pin, clk_pin, LSBFIRST, clock_data.get_num(i));
        activate(i);
        delay(5);
    }
  }
}*/

void activate(int index) {
  if(index == 0) {
    digitalWrite(cathode[0], LOW);
  } else if(index == 1) {
    digitalWrite(cathode[1], LOW);
  } else if(index == 2){
    digitalWrite(cathode[2], LOW);
  }
}

void deactivate() {
  digitalWrite(cathode[0], HIGH);
  digitalWrite(cathode[1], HIGH);
  digitalWrite(cathode[2], HIGH);
}
