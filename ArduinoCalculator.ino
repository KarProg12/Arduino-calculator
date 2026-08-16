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
  { '.', '0', '=', '+' }
};

byte rowPins[ROWS] = { 5, 4, 3, 2 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keyBinds), rowPins, colPins, ROWS, COLS);

//initialize lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

//numbers of equation in String variable
String sNum1 = "";
String mathOperator = "";
String sNum2 = "";
bool secondNum = false;

//variables where the String variables are converted to float
float num1 = 0;
float num2 = 0;
float equation = 0;

bool backlit = true;
bool lastButtonState = HIGH;
#define backlitButton 11


void setup() {

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(backlitButton, INPUT_PULLUP);
}

void loop() {

  char key = keypad.getKey();
  //checks if any key on keypad has been clicked if not than nothing happens it just returns NO_KEY
  if (key) {
    Serial.println(key);

    if (key == '/' || key == '*' || key == '-' || key == '+') {
      lcd.print(key);
      mathOperator = String(key);
      secondNum = true;

      lcd.setCursor(0, 1);  //second number in operation will be in row 1 on display
    }
    //converts String numbers to float
    else if (key == '=') {
      num1 = sNum1.toFloat();
      num2 = sNum2.toFloat();

      if (mathOperator == "*") equation = num1 * num2;
      if (mathOperator == "-") equation = num1 - num2;
      if (mathOperator == "+") equation = num1 + num2;
      if (mathOperator == "/") {
        if (num2 != 0) {
          equation = num1 / num2;
        } else {
          lcd.clear();
          lcd.print("Err:ZeroDivision");
          sNum1 = "";
          sNum2 = "";
          mathOperator = "";
          secondNum = false;
          lcd.setCursor(0, 0);  //after a mistake cursor returns to row 0
          return;
        }
      }
      //clear display from operation before showing the equation
      lcd.clear();
      //display equation of operation
      //check if num is integer(e.g if 17.00 is equal to 17?)
      if (equation == (int)equation) {
        lcd.print((int)equation);       //display on LCD only clear 17
        sNum1 = String((int)equation);  //save in memory WITHOUT dot (e.g "17")
      } else {
        lcd.setCursor(0, 0);
        lcd.print(equation, 4);       //display as a fraction with 4 places ofter dot (e.g 17.5000)
        sNum1 = String(equation, 4);  //save in memory WITH dot (e.g "17.5000")
      }

      sNum2 = "";
      mathOperator = "";
      secondNum = false;
    }
    //collecting numbers to String
    else {
      //if user is in phase of entering the first num of math operation
      if (secondNum == false) {
        if (key == '.') {
          if (sNum1.indexOf('.') == -1) {
            sNum1 += key;
            lcd.print(key);
          }
        } else {
          sNum1 += key;
          lcd.print(key);
        }
      }
      //if user is in phase of entering the second num of math operation
      else {
        if (key == '.') {
          if (sNum2.indexOf('.') == -1) {
            sNum2 += key;
            lcd.print(key);
          }
        } else {
          sNum2 += key;
          lcd.print(key);
        }
      }
    }  //curly brace closing main block 'else' of collecting chars
  }    //curly brace closing 'if (key == '.')'
  /*read state of the button (HIGH or LOW) because this button's using
  INPUT_PULLUP these values are swapped LOW = HIGH, HIGH = LOW*/
  bool buttonState = digitalRead(backlitButton);
  
  //if state of button = clicked and last button state was "not clicked"
  if (buttonState == LOW && lastButtonState == HIGH) {
    //backlit val true -> false
    backlit = !backlit;
    if (backlit == true) {
      lcd.backlight();
    } 
    //when backlit == false
    else {
      lcd.noBacklight();
    }
    delay(100);
  }
  //save current button state as last button state
  lastButtonState = buttonState;
}  //curly brace closing func 'void loop()'
