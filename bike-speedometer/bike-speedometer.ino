// Bike Speedometer using Hall Sensor and multiplexed 595.

uint8_t dataPin = 4;  //yellow
uint8_t latchPin = 5; // white
uint8_t clockPin = 6; // green / blue

unsigned long last_turn = 0;
float radius = 13.5; // inches
float circumference;
float mph;

// 1 = off, 0 = on
// blank, middle, left-top, left-bottom, bottom, right-bottom, right-top, top
const uint8_t segsB[11][8] = {
  {0, 1, 0, 0, 0, 0, 0, 0}, // 0
  {0, 1, 1, 1, 1, 0, 0, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 0}, // 2
  {0, 0, 1, 1, 0, 0, 0, 0}, // 3
  {0, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 0, 0, 1, 0, 0, 1, 0}, // 5
  {0, 0, 0, 0, 0, 0, 1, 0}, // 6
  {0, 1, 1, 1, 1, 0, 0, 0}, // 7
  {0, 0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 1, 0, 0, 0, 0}, // 9
  {1, 1, 1, 1, 1, 1, 1, 1} // blank
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
//  show(mph * 100);
  show(mph);

}

void show (int number) {

  updateShiftRegister(number);

}

void updateShiftRegister(int num) {

  uint8_t waitTime = 5;
  uint8_t digit = 0;
  String num_st = String(num);

  while (num_st.length() < 4) {
    num_st = "-" + num_st;
  }

  while (digit < 4) {
    char c = num_st.charAt(digit);
    const int index = (c == '-') ? 10 : (int)(c-48);
    digitalWrite(latchPin, LOW);
    shiftOut2(dataPin, clockPin, digitB[digit]);
    shiftOut2(dataPin, clockPin, segsB[index]);
    digitalWrite(latchPin, HIGH);
    digit = digit + 1;
    delay(waitTime);
  }

}

void shiftOut2(uint8_t dataPin, uint8_t clockPin, const uint8_t val[]) {

  uint8_t i;
  for (i = 0; i < 8; i++)  {
    digitalWrite(dataPin,  val[i]);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }

}

void magnet_detect () {

  const float span = float(millis() - last_turn);
  if (span > 80) {
//    mph = 2.050/((float)(millis()-last_turn)/1000)*3.6;
    mph = (56.8 * float(circumference)) / span;
    last_turn = millis();
  }
  
}

// Credit
// RE: 595s, big ups to Kevin Darrah > https://www.youtube.com/watch?v=Ne4Wv1kUP8w
// RE: mph calculation, http://www.instructables.com/id/Arduino-Bike-Speedometer/
