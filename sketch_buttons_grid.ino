// Nessesary implementations
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
#include <Keypad.h>
const byte ROWS = 4;
const byte COLUMNS = 4;

char keyMap[ROWS][COLUMNS] = {
  {"1", "2", "3", "*"};
  {"4", "5", "6", "/"};
  {"7", "8", "9", "+"};
  {"0", ".", "=", "-"};
}


void setup() {
  
  // pinMode(row1, INPUT_PULLUP);
  // pinMode(row2, INPUT_PULLUP);
  // pinMode(row3, INPUT_PULLUP);
  // pinMode(row4, INPUT_PULLUP);
  // pinMode(column1, INPUT_PULLUP);
  // pinMode(column2, INPUT_PULLUP);
  // pinMode(column3, INPUT_PULLUP);
  // pinMode(column4, INPUT_PULLUP);
  

}

void loop() {
  


}
