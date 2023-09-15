//library yang dibutuhkan
#include <WiFi.h> //library wifi
#include <WiFiClientSecure.h> //library wifi client
#include <UniversalTelegramBot.h> //library bot telegram
#include <ArduinoJson.h> //
#include <ESP32Servo.h> //Library servo
#include <LiquidCrystal_I2C.h> //Library I2C untuk LCD

Servo myServo;

//pin ultrasonic
const int trigPin = 18;
const int echoPin = 19;

// pin sensor digital
const int pirPin = 4;

//pin servo
const int servoPin = 5;

//Pin LCD I2C
// SDA to 21
// SCL to 22

//Ultrasonik
//cepat rambat suara 
#define SOUND_SPEED 0.034
long duration; // durasi gelombang suara
float distanceCm; //variable untuk menyimpan jarak
float state;  //variabel untuk cek jarak sebelumnya

//PIR
int pirVal; // variabel untuk menyimpan nilai dari sensor
int pos = 0; //parameter perulangan

//LCD
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

// Nama wifi/hotspot yang digunakan
const char* ssid = "komputer";
const char* password = "komputer123";

// Initialize Telegram BOT
#define BOTtoken "6087886617:AAEDfOj6YcSZl97gZZYbcILId98G5quA9Mg"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "5279776565" //id telegram

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

  
void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  pinMode(pirPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org 
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");

  
}

void loop() {
 // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  Serial.println(distanceCm);
  pirVal = digitalRead(pirPin); //baca sensor PIR
  Serial.println(pirVal);
  
  if(distanceCm <= 20){ //jika jarak dibawah 20cm
    if(state <= distanceCm){ //jika masih dibawah 20cm
      bot.sendMessage(CHAT_ID, "It's Full"); //kirim pesan ke telegram
      // set cursor to first column, first row
      

      state = distanceCm;
    } 
    lcd.setCursor(0, 0);
    // print message
    lcd.print("Sorry, It's full");
    
    }else{
      
      lcd.setCursor(0, 0);
      // print message
      lcd.print("Thank you for");
      lcd.setCursor(0, 1);
      lcd.print("using me :)");  
      if(pirVal == HIGH){ // jika gerakan terdeteksi
        for (pos = 0; pos <= 180; pos += 1) { //gerakan servo dengan kecepatan 10ms/derajat
          myServo.write(pos);
          delay(10);
        }
        delay(3000); // tunggu selama 3 detik
        for (pos = pos; pos >= 0; pos -= 1) {
          myServo.write(pos);
          delay(10);
        }
      }
      // clears the display to print new message
      lcd.clear();
      
    }
  delay(500);
  
}
