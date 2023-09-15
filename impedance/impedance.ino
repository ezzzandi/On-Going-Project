const int sensor1 = A3;
const int sensor2 = A5;
const int sensor3 = A1;
const int sensor4 = A7;
const int sensor5 = A9;

const int WAKTU_SAMPEL = 10;
unsigned long waktu_sekarang;
unsigned long waktu_akhir = 0;
unsigned long perubahan_waktu = 0;

int buffer_sensor1 = 0;
int buffer_sensor2 = 0;
int buffer_sensor3 = 0;
int buffer_sensor4 = 0;
int buffer_sensor5 = 0;


void setup(){
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  Serial.begin(9600);
}

void loop(){
  if (digitalRead(sensor1) == LOW){
    buffer_sensor1++;
  }

  if (digitalRead(sensor2) == LOW){
    buffer_sensor2++;
  }

  if (digitalRead(sensor3) == LOW){
    buffer_sensor3++;
  }

  if (digitalRead(sensor4) == LOW){
    buffer_sensor4++;
  }

  if (digitalRead(sensor5) == LOW){
    buffer_sensor5++;
  }
  
  if (waktu_akhir > WAKTU_SAMPEL) {
    Serial.println(buffer_sensor1);
    Serial.println(buffer_sensor2);
    Serial.println(buffer_sensor3);
    Serial.println(buffer_sensor4);
    Serial.println(buffer_sensor5);
    buffer_sensor1 = 0;
    buffer_sensor2 = 0;
    buffer_sensor3 = 0;
    buffer_sensor4 = 0;
    buffer_sensor5 = 0;
    waktu_akhir = waktu_sekarang;
  }
}
