#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char keyBinds[ROWS][COLS] = {
  { '7', '8', '9', '/' },
  { '4', '5', '6', '*' },
  { '1', '2', '3', '-' },
  { 'C', '0', '=', '+' }
};

byte rowPins[ROWS] = { 5, 4, 3, 2 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keyBinds), rowPins, colPins, ROWS, COLS);
//initialize lcd lcd
LiquidCrystal_I2C lcd(0x27, 2, 16);

float num1;
String mathOperator = "";
float num2;
float equation = 0;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    lcd.print(key);
    num1 += key;
  }
  if (key == '/' || key == '*' || key == '-' || key == '+') {
    Serial.print(key);
    lcd.print(key);
    mathOperator += key;
  }
  if (key) {
    Serial.println(key);
    lcd.print(key);
    num2 += key;
  }
  if (key == '=') {
    num1
  } 
  if (key == 'C') {
    Serial.println(key);
    lcd.clear();
  }
}