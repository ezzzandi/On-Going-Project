#include <LiquidCrystal_I2C.h>
//define I2C address 0x27, 2 line
LiquidCrystal_I2C lcd(0x27, 16, 2);
long cm = 0;
long tinggiBadan;
long readUltrasonicDistance(int trig, int echo) {
  pinMode(trig, OUTPUT);  // Clear the trigger
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echo, HIGH);
}
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}
void loop()
{
  // measure the ping time in cm
  cm = (readUltrasonicDistance(3, 4) / 2) / 29.1;
  Serial.print(cm);
  Serial.println("cm");
  tinggiBadan = 200 - cm;
  lcd.setCursor(0, 0);
  lcd.print("Tinggi badan:");
  lcd.setCursor(0, 1);
  lcd.print(tinggiBadan);
  lcd.setCursor(3, 1);
  lcd.print("tinggiBadan");
  delay(500); // Wait for 500 millisecond(s)
  lcd.clear();
}
