// big ups to Kevin Darrah > https://www.youtube.com/watch?v=Ne4Wv1kUP8w

uint8_t dataPin = 4;  //yellow
uint8_t latchPin = 5; // white
uint8_t clockPin = 6; // green / blue

unsigned long last_turn = 0;
float radius = 13.5; // inches
float circumference;
float mph;

// 1 = off, 0 = on
// blank, middle, left-top, left-bottom, bottom, right-bottom, right-top, top
const uint8_t segsB[10][8] = {
  {0, 1, 0, 0, 0, 0, 0, 0}, // 0
  {0, 1, 1, 1, 1, 0, 0, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 0}, // 2
  {0, 0, 1, 1, 0, 0, 0, 0}, // 3
  {0, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 0, 0, 1, 0, 0, 1, 0}, // 5
  {0, 0, 0, 0, 0, 0, 1, 0}, // 6
  {0, 1, 1, 1, 1, 0, 0, 0}, // 7
  {0, 0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 1, 0, 0, 0, 0} // 9
};

const uint8_t digitB[4][8] = {
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0}
};

void setup() {

//  Serial.begin(9600);
  attachInterrupt(0, magnet_detect, RISING);

  circumference = 2 * 3.14 * radius;

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

}

void loop() {

  if ((millis() - last_turn) > 2000) {
    mph = 0.00;
  }
  show(mph * 100);

}

void show (int number) {

  updateShiftRegister(number);

}

void updateShiftRegister(int num) {

  uint8_t waitTime = 5;
  int digit = 0;
  String num_st = String(num);
//  Serial.println("num " + num_st);
  while (digit < 4) {
    int index = (int)(num_st.charAt(digit)-48);
    digitalWrite(latchPin, LOW);
    shiftOut2(dataPin, clockPin, LSBFIRST, digitB[digit]);
    shiftOut2(dataPin, clockPin, LSBFIRST, segsB[index]);
    digitalWrite(latchPin, HIGH);
    digit = digit + 1;
    delay(waitTime);
  }

}

void shiftOut2(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, const uint8_t val[]) {
  uint8_t i;

  for (i = 0; i < 8; i++)  {
    if (bitOrder == LSBFIRST) {
      digitalWrite(dataPin,  val[i]);//!!(val[i] & (1 << i)));
    }
    else {
      digitalWrite(dataPin, !!(val[i] & (1 << (7 - i))));
    }
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }

}

void magnet_detect () {
  if (millis() - last_turn > 80) {
    mph = (56.8 * float(circumference)) / float(last_turn);
    last_turn = millis();
  }
}

