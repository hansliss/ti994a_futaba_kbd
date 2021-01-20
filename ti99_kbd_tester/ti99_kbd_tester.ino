#define COLS PORTA
#define COLSD DDRA

#define ROWS PINC
#define ROWSD DDRC

#define ALOCK A0

char *keyMatrix[6][8] = {
  {"\\", ";", "P", "0", "Z", "A", "Q", "1"},
  {".", "L", "O", "9", "X", "S", "W", "2"},
  {",", "K", "I", "8", "C", "D", "E", "3"},
  {"M", "J", "U", "7", "V", "F", "R", "4"},
  {"N", "H", "Y", "6", "B", "G", "T", "5"},
  {"=", "SPC", "ENT", "DUM1", "DUM2", "SHIFT", "CRTL", "FNCT"}
};

int keystate[6][8];

int alockState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ALOCK, INPUT);
  COLSD = B11111111;
  ROWSD = (ROWSD & ~B00111111);
  ROWS |= B00111111;
  for (int i=0; i< 8; i++) {
    for (int j=0; j<6; j++) {
      keystate[j][i] = 0;
    }
  }
  Serial.begin(9600);
}

void loop() {
  for (int i=0; i < 8; i++) {
    COLS = ~(1 << i);
    //delay(100);
    if (i == 1) {
      if (digitalRead(ALOCK) == HIGH) {
        if (!alockState) {
          Serial.println("ALOCK down");
          alockState = 1;
        }
      } else {
        if (alockState) {
          Serial.println("ALOCK up");
          alockState = 0;
        }
      }
    }
    //Serial.println(String(i, HEX) + ":" + String(~((unsigned char)(ROWS & B00111111)), HEX));
    for (int j=0; j<6; j++) {
      if (!(ROWS & (1 << j))) {
        if (!keystate[5-j][7-i]) {
          Serial.print(keyMatrix[5-j][7-i]);
          Serial.println(" down");
          keystate[5-j][7-i] = 1;
        }
      } else {
        if (keystate[5-j][7-i]) {
          Serial.print(keyMatrix[5-j][7-i]);
          Serial.println(" up");
          keystate[5-j][7-i] = 0;
        }
      }
    }
  }
  delay(10);
}
