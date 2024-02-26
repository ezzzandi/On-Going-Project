#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
//define I2C address 0x27, 2 line
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIG 3
#define ECHO 4
#define MAX_DISTANCE 200

long cm = 0;
long tinggiBadan;

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}
void loop()
{
  cm = sonar.ping_cm();
  tinggiBadan = 200 - cm;
  lcd.setCursor(0, 0);
  lcd.print("Tinggi badan:");
  lcd.setCursor(0, 1);
  lcd.print(tinggiBadan);
  lcd.setCursor(3, 1);
  delay(500); // Wait for 500 millisecond(s)
  lcd.clear();
}
