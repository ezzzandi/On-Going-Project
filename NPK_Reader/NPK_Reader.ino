/*
  :Author: ezandi_
  :Email:ezzzandi@gmail.com
  :Date: 26/01/2024
  :Revision: version0
  :License: Public Domain
*/
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define RE 8
#define DE 7
#define DI 6
#define RO 9

const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
SoftwareSerial mod(RO, DI);

unsigned long npkMillis = 0;
unsigned long lcdMillis = 0;
unsigned long currentMillis;
unsigned long npkPeriod = 250;
unsigned long lcdPeriod = 1000;

int sensorState = 0;
int lcdState = 0;

byte N, P, K;

LiquidCrystal_I2C lcd(0x27, 16, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display

void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(0, 0);
  lcd.print("NPK Reader");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - npkMillis >= npkPeriod) {
    if (sensorState == 0) {
      N = nitrogen();
      sensorState = 1;
    }
    else if (sensorState == 1) {
      P = phosphorous();
      sensorState = 2;
    }
    else if (sensorState == 2) {
      K = potassium();
      sensorState = 0;
    }
    npkMillis = currentMillis;
  }

  if (currentMillis - lcdMillis >= lcdPeriod) {
    lcdMillis = currentMillis;
    lcd.clear();

    lcd.setCursor(0, 0);  //Move cursor to character 0 on line 1
    lcd.print("NPK Reader");
    
    lcd.setCursor(0, 1);  //Set cursor to character 0 on line 2
    lcd.print("N: " + String(N) + " kg/mg");
    
    lcd.setCursor(0, 2);  //Set cursor to character 0 on line 3
    lcd.print("P: " + String(P) + " kg/mg");

    lcd.setCursor(0, 3);  //Set cursor to character 0 on line 4
    lcd.print("K: " + String(K) + " kg/mg");
  }
}

byte nitrogen() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(nitro, sizeof(nitro)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte phosphorous() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(phos, sizeof(phos)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(pota, sizeof(pota)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}
