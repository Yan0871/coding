#include <Servo.h>
#define echoPin 34
#define trigPin 2
#include <LiquidCrystal_I2C.h>

//Ultrasonik Sensor+Speker
int buzzer = 36;
long duration;
int distance;

// deklarasi motor driver l298n kanan
int ENA_kanan = 22;
int IN1_kanan = 23;
int IN2_kanan = 24;
int IN3_kanan = 25;
int IN4_kanan = 26;
int ENB_kanan = 27;

// deklarasi motor driver l298n kiri
int ENA_kiri = 28;
int IN1_kiri = 29;
int IN2_kiri = 30;
int IN3_kiri = 31;
int IN4_kiri = 32;
int ENB_kiri = 33;

//Speed
int Speed = 1000;

//Deklarasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Mechanical Arm + GigiBiru
//Lengan paling atas (Posisi Servo)
int pin_servo6 = 10;
Servo servo6;

//dibawah Lengan atas
int pin_servo5 = 9;
Servo servo5;

//Lengan putar atas/tengah
int pin_servo4 = 8;
Servo servo4;

//dibawah Lengan putar atas/tengah
int pin_servo3 = 7;
Servo servo3;

//Lengan Tengah
int pin_servo2 = 6;
Servo servo2;

//Lengan putar bawah
int pin_servo1 = 5;
Servo servo1;

int sudut = 0;
int data;

void setup(){
  Serial.begin(9600);
  //Utrasonik Sensor+Speaker
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Arm
  servo6.attach(pin_servo6);
  servo5.attach(pin_servo5);
  servo4.attach(pin_servo4);
  servo3.attach(pin_servo3);
  servo2.attach(pin_servo2);
  servo1.attach(pin_servo1);

 // Konfigurasi pin-pin motor driver l298n sebagai output
  pinMode(ENA_kanan, OUTPUT);
  pinMode(IN1_kanan, OUTPUT);
  pinMode(IN2_kanan, OUTPUT);
  pinMode(IN3_kanan, OUTPUT);
  pinMode(IN4_kanan, OUTPUT);
  pinMode(ENB_kanan, OUTPUT);

  pinMode(ENA_kiri, OUTPUT);
  pinMode(IN1_kiri, OUTPUT);
  pinMode(IN2_kiri, OUTPUT);
  pinMode(IN3_kiri, OUTPUT);
  pinMode(IN4_kiri, OUTPUT);
  pinMode(ENB_kiri, OUTPUT);

  //LCD
  lcd.begin();
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  while(Serial.available()>0){
    data = Serial.read();
    Serial.println(data);   
  
    //Action Arm
    if(data == '1'){
      for(sudut=0; sudut <= 180; sudut +=1){
        servo6.write(sudut);
        delay(15);        
      }
    }
    else if(data == '2'){
      for(sudut=180; sudut >= 0; sudut -=1){
        servo6.write(sudut);
        delay(15);
      }
    }
    else if(data == '3'){
      for(sudut=0; sudut <= 180; sudut += 1){
        servo1.write(sudut);
        delay(15);
      }
    }
    else if(data == '4'){
      for(sudut=180; sudut >= 0; sudut -= 1){
        servo1.write(sudut);
        delay(15);
      }
    }
    else if(data == '5'){
      for(sudut=90; sudut <= 180; sudut += 1){
        servo2.write(sudut);
        delay(15);
      }
    }
    else if(data == '6'){
      for(sudut=180; sudut >= 90; sudut -= 1){
        servo2.write(sudut);
        delay(15);
      }
    }
    else if(data == '7'){
      for(sudut=0; sudut <= 180; sudut += 1){
        servo3.write(sudut);
        delay(15);
      }
    }
    else if(data == '8'){
      for(sudut=150; sudut >= 0; sudut -= 1){
        servo3.write(sudut);
        delay(15);
      }
    }
    else if(data == '9'){
      for(sudut=0; sudut <= 180; sudut += 1){
        servo4.write(sudut);
        delay(15);
      }
    }
    else if(data == 'Q'){
      for(sudut=180; sudut >= 0; sudut -= 1){
        servo4.write(sudut);
        delay(15);
      }
    }
    else if(data == 'W'){
      for(sudut=0; sudut <= 180; sudut += 1){
        servo5.write(sudut);
        delay(15);
      }
    }
    else if(data == 'R'){
      for(sudut=180; sudut >= 0; sudut -= 1){
        servo5.write(sudut);
        delay(15);
      }
    }
    else if(data == 'T'){
      for(sudut=180; sudut >= 0; sudut -= 1){
        servo5.write(sudut);
        delay(15);
      }
    }

    //Untuk Motor
    else if(data == 'w'){   //Maju
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, HIGH);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, HIGH);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, HIGH);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, HIGH);
    }
    else if(data == 's') {    //Mundur
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, HIGH);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, HIGH);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, HIGH);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, HIGH);
    }
    else if(data == 'd'){   //Kanan
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, HIGH);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, HIGH);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, HIGH);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, HIGH);
    }
    else if(data == 'a') {    //Kiri
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, HIGH);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, HIGH);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, HIGH);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, HIGH);
    }
    else if(data == 'x') {    //Berhenti
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, HIGH);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, HIGH);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, HIGH);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, HIGH);
    }
  }
  if(distance <= 10){    //Paksa Mundur
    digitalWrite(buzzer, HIGH);
    digitalWrite(IN1_kanan, LOW);
    digitalWrite(IN2_kanan, HIGH);
    digitalWrite(ENA_kanan, HIGH);

    digitalWrite(IN3_kanan, HIGH);
    digitalWrite(IN4_kanan, LOW);
    digitalWrite(ENB_kanan, HIGH);

    digitalWrite(IN1_kiri, HIGH);
    digitalWrite(IN2_kiri, LOW);
    digitalWrite(ENA_kiri, HIGH);

    digitalWrite(IN3_kiri, LOW);
    digitalWrite(IN4_kiri, HIGH);
    digitalWrite(ENB_kiri, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(IN1_kanan, LOW);
    digitalWrite(IN2_kanan, LOW);
    digitalWrite(ENA_kanan, HIGH);

    digitalWrite(IN3_kanan, LOW);
    digitalWrite(IN4_kanan, LOW);
    digitalWrite(ENB_kanan, HIGH);

    digitalWrite(IN1_kiri, LOW);
    digitalWrite(IN2_kiri, LOW);
    digitalWrite(ENA_kiri, HIGH);

    digitalWrite(IN3_kiri, LOW);
    digitalWrite(IN4_kiri, LOW);
    digitalWrite(ENB_kiri, HIGH);
  }
}