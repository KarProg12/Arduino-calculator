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
//numbers of equation in String variable
String sNum1 = "";
bool secondNumber = false; 
String sNum2 = "";
//variables where the String variables are converted to float 
float num1 = 0;
float num2 = 0;
float equation = 0;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  char key = keypad.getKey();
  //checks if any key on keypad has been clicked if not than tohing happens it just returns NO_KEY
  if (key) {
    lcd.print(key);    
    if (key == 'C') {
      Serial.println(key);
      lcd.clear();
    }
    
  }
}