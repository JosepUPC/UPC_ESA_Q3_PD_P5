#include <Arduino.h>
#pragma GCC optimize ("O3")   //code optimisation controls - "O2" & "O3" code performance, "Os" code size

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define COLUMS           20   //LCD columns
#define ROWS             4    //LCD rows
#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup()
{
  Serial.begin(115200);

  while (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) //colums, rows, characters size
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);   
  }

  lcd.print(F("PCF8574 is OK..."));    //(F()) saves string to flash & keeps dynamic memory free
  delay(2000);

  lcd.clear();

  /* prints static text */
  lcd.setCursor(0, 1);                 //set 1-st colum & 2-nd row
  lcd.print(F("Hello world!"));

  lcd.setCursor(0, 2);
  lcd.print(F("Random number: 1"));
}


void loop()
{
  /* print dynamic text */
  lcd.setCursor(14, 2);        //set 15-th colum & 3-rd row

  lcd.print(random(10, 1000));
  lcd.write(LCD_SPACE_SYMBOL); //"write()" is faster than "lcd.print()"

  delay(1000);
}
