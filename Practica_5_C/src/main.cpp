#include <Arduino.h>
#pragma GCC optimize ("O3")   //code optimisation controls - "O2" & "O3" code performance, "Os" code size

#include <AHT10.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define COLUMS           20   //LCD columns
#define ROWS             4    //LCD rows
#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet

uint8_t readStatus = 0;

AHT10 myAHT10(AHT10_ADDRESS_0X38);

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup()
{
  Serial.begin(115200);

    while (myAHT10.begin() != true)
  {
    Serial.println(F("AHT10 not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
    delay(5000);
  }
  Serial.println(F("AHT10 OK"));

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
  lcd.print(F("AHT10 sensor"));

  lcd.setCursor(0, 1);
  lcd.print(F("Temperature:"));

  lcd.setCursor(0, 2);
  lcd.print(F("Humidity:"));

  lcd.setCursor(0, 3);
  lcd.print(F("Josep Esquerra"));
}


void loop()
{
  /* print dynamic text */
  lcd.setCursor(15, 1);        //set 15-th colum & 3-rd row
  lcd.print(myAHT10.readTemperature());
  lcd.setCursor(15, 2);        //set 15-th colum & 3-rd row
  lcd.print(myAHT10.readHumidity());

  lcd.write(LCD_SPACE_SYMBOL); //"write()" is faster than "lcd.print()"

  delay(1000);
}
