#include <Arduino.h>
#pragma GCC optimize ("O3")   //code optimisation controls - "O2" & "O3" code performance, "Os" code size

#include "MAX30105.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

MAX30105 particleSensor;

#define debug Serial

#define COLUMS           20   //LCD columns
#define ROWS             4    //LCD rows
#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup()
{
  debug.begin(9600);
  debug.println("MAX30105 Basic Readings Example");

  // Initialize sensor
  if (particleSensor.begin() == false)
  {
    debug.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

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
  lcd.setCursor(0, 0);
  lcd.print(F("pulse_sensor"));

}


void loop()
{
  /* print dynamic text */
  lcd.setCursor(0, 1);
  lcd.print(F(particleSensor.getRed()));

  lcd.setCursor(0, 2);
  lcd.print(F(particleSensor.getIR()));

  lcd.setCursor(0, 2);
  lcd.print(F(particleSensor.getGreen()));
  lcd.write(LCD_SPACE_SYMBOL); //"write()" is faster than "lcd.print()"

  delay(5000);
}
