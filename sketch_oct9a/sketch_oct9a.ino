#include <Servo.h>

// deklarasi motor servo
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // posisi saat ini
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // posisi sebelumnya
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50]; // untuk menyimpan posisi/langkah
int speedDelay = 20;
int index = 0;
String dataIn = "";

// deklarasi motor driver l298n kanan
int ENA_kanan = 22;
int IN1_kanan = 23;
int IN2_kanan = 24;
int IN3_kanan = 25;
int IN4_kanan = 26;
int ENB_kanan = 27;

// deklarasi motor driver l298n kiri
int ENA_kiri  =28;
int IN1_kiri  =29;
int IN2_kiri  =30;
int IN3_kiri  =31;
int IN4_kiri  =32;
int ENB_kiri  =33;

// deklarasi sensor jarak
#define echoPin 34
#define trigPin 35

// deklarasi buzzer
#define buzzerPin 36

int speedCar = 100;   // 50 - 255
int speed_Coeff = 4;
boolean horn = false;

void setup() {
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);
  delay(20);
  // Posisi awal lengan robot
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 150;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo4PPos = 100;
  servo04.write(servo4PPos);
  servo5PPos = 120;
  servo05.write(servo5PPos);
  servo6PPos = 60;
  servo06.write(servo6PPos);

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

  // Konfigurasi pin buzzer
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  // PROGRAM UNTUK SMART CAR ROBOT
  while (Serial.available() > 0) {
    int data = Serial.read();
    Serial.println(data);

    // Klakson
    if (data == "V") {
      digitalWrite(buzzerPin, HIGH);
    }

    if (data == "v") {
      digitalWrite(buzzerPin, LOW);
    }


    // Kontrol kemudi robot
    if (data == 'W') {
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'D') {
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'S') {
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'A') {
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'E') {
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, speedCar/speed_Coeff);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, speedCar/speed_Coeff);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'Q') {
      digitalWrite(IN1_kanan, HIGH);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, HIGH);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, HIGH);
      digitalWrite(ENA_kiri, speedCar/speed_Coeff);

      digitalWrite(IN3_kiri, HIGH);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, speedCar/speed_Coeff);
    }

    if (data == 'C') {
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, speedCar/speed_Coeff);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, speedCar/speed_Coeff);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, speedCar);
    }

    if (data == 'Z') {
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, HIGH);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, HIGH);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, HIGH);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, speedCar/speed_Coeff);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, HIGH);
      digitalWrite(ENB_kiri, speedCar/speed_Coeff);
    }

    if (data == 'X') {
      digitalWrite(IN1_kanan, LOW);
      digitalWrite(IN2_kanan, LOW);
      digitalWrite(ENA_kanan, speedCar);

      digitalWrite(IN3_kanan, LOW);
      digitalWrite(IN4_kanan, LOW);
      digitalWrite(ENB_kanan, speedCar);

      digitalWrite(IN1_kiri, LOW);
      digitalWrite(IN2_kiri, LOW);
      digitalWrite(ENA_kiri, speedCar);

      digitalWrite(IN3_kiri, LOW);
      digitalWrite(IN4_kiri, LOW);
      digitalWrite(ENB_kiri, speedCar);
    }


    // Kontrol Kecepatan Robot
    if (data = '0') {
      speedCar = 100;
    }

    if (data = '1') {
      speedCar = 115;
    }

    if (data = '2') {
      speedCar = 130;
    }

    if (data = '3') {
      speedCar = 145;
    }

    if (data = '4') {
      speedCar = 160;
    }

    if (data = '5') {
      speedCar = 175;
    }

    if (data = '6') {
      speedCar = 190;
    }

    if (data = '7') {
      speedCar = 205;
    }

    if (data = '8') {
      speedCar = 220;
    }

    if (data = '9') {
      speedCar = 235;
    }

    if (data = 'x') {
      speedCar = 255;
    }


    // PROGRAM UNTUK LENGAN ROBOT
    if (data == 'L') {
      // Periksa data yang masuk
      while (Serial.available() > 0) {
        dataIn = Serial.readString();  // Baca data sebagai string
        
        // Jika penggeser "Pinggang" telah berubah nilainya - Pindahkan Servo 1 ke posisi
        if (dataIn.startsWith("s1")) {
          String dataInS = dataIn.substring(2, dataIn.length()); // Ekstrak hanya nomornya. Misalnya. dari "s1120" ke "120"
          servo1Pos = dataInS.toInt();  // Ubah string menjadi bilangan bulat
          // Saya menggunakan loop sehingga Saya dapat mengontrol kecepatan servo
          // Jika posisi sebelumnya lebih besar dari posisi saat ini
          if (servo1PPos > servo1Pos) {
            for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Jalankan servo ke bawah
              servo01.write(j);
              delay(20);    // mendefinisikan kecepatan di mana servo berputar
            }
          }
          // Jika posisi sebelumnya lebih kecil dari posisi saat ini
          if (servo1PPos < servo1Pos) {
            for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Jalankan servo ke atas
              servo01.write(j);
              delay(20);
            }
          }
          servo1PPos = servo1Pos;   // atur posisi saat ini sebagai posisi sebelumnya
        }
        
        // Pindahkan Servo 2
        if (dataIn.startsWith("s2")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          servo2Pos = dataInS.toInt();

          if (servo2PPos > servo2Pos) {
            for ( int j = servo2PPos; j >= servo2Pos; j--) {
              servo02.write(j);
              delay(50);
            }
          }
          if (servo2PPos < servo2Pos) {
            for ( int j = servo2PPos; j <= servo2Pos; j++) {
              servo02.write(j);
              delay(50);
            }
          }
          servo2PPos = servo2Pos;
        }
        // Pindahkan Servo 3
        if (dataIn.startsWith("s3")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          servo3Pos = dataInS.toInt();
          if (servo3PPos > servo3Pos) {
            for ( int j = servo3PPos; j >= servo3Pos; j--) {
              servo03.write(j);
              delay(30);
            }
          }
          if (servo3PPos < servo3Pos) {
            for ( int j = servo3PPos; j <= servo3Pos; j++) {
              servo03.write(j);
              delay(30);
            }
          }
          servo3PPos = servo3Pos;
        }
        // Pindahkan Servo 4
        if (dataIn.startsWith("s4")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          servo4Pos = dataInS.toInt();
          if (servo4PPos > servo4Pos) {
            for ( int j = servo4PPos; j >= servo4Pos; j--) {
              servo04.write(j);
              delay(30);
            }
          }
          if (servo4PPos < servo4Pos) {
            for ( int j = servo4PPos; j <= servo4Pos; j++) {
              servo04.write(j);
              delay(30);
            }
          }
          servo4PPos = servo4Pos;
        }
        // Pindahkan Servo 5
        if (dataIn.startsWith("s5")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          servo5Pos = dataInS.toInt();
          if (servo5PPos > servo5Pos) {
            for ( int j = servo5PPos; j >= servo5Pos; j--) {
              servo05.write(j);
              delay(30);
            }
          }
          if (servo5PPos < servo5Pos) {
            for ( int j = servo5PPos; j <= servo5Pos; j++) {
              servo05.write(j);
              delay(30);
            }
          }
          servo5PPos = servo5Pos;
        }
        // Pindahkan Servo 6
        if (dataIn.startsWith("s6")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          servo6Pos = dataInS.toInt();
          if (servo6PPos > servo6Pos) {
            for ( int j = servo6PPos; j >= servo6Pos; j--) {
              servo06.write(j);
              delay(30);
            }
          }
          if (servo6PPos < servo6Pos) {
            for ( int j = servo6PPos; j <= servo6Pos; j++) {
              servo06.write(j);
              delay(30);
            }
          }
          servo6PPos = servo6Pos; 
        }
        // Jika tombol "SIMPAN" ditekan
        if (dataIn.startsWith("SAVE")) {
          servo01SP[index] = servo1PPos;  // simpan posisi ke dalam array
          servo02SP[index] = servo2PPos;
          servo03SP[index] = servo3PPos;
          servo04SP[index] = servo4PPos;
          servo05SP[index] = servo5PPos;
          servo06SP[index] = servo6PPos;
          index++;                        // Tingkatkan indeks array
        }
        // Jika tombol "RUN" ditekan
        if (dataIn.startsWith("RUN")) {
          runservo();  // Mode otomatis - jalankan langkah-langkah yang disimpan
        }
        // Jika tombol "RESET" ditekan
        if ( dataIn == "RESET") {
          memset(servo01SP, 0, sizeof(servo01SP)); // Hapus data array ke 0
          memset(servo02SP, 0, sizeof(servo02SP));
          memset(servo03SP, 0, sizeof(servo03SP));
          memset(servo04SP, 0, sizeof(servo04SP));
          memset(servo05SP, 0, sizeof(servo05SP));
          memset(servo06SP, 0, sizeof(servo06SP));
          index = 0;  // Index ke 0
        }
      }
    }
  }
}

// Fungsi kustom mode otomatis - jalankan langkah-langkah yang disimpan
void runservo() {
  while (dataIn != "RESET") {   // Jalankan langkah berulang-ulang sampai tombol "RESET" ditekan
    for (int i = 0; i <= index - 2; i++) {  // Jalankan melalui semua langkah (indeks)
      if (Serial.available() > 0) {      // Periksa data yang masuk
        dataIn = Serial.readString();
        if ( dataIn == "PAUSE") {           // Jika tombol "PAUSE" ditekan
          while (dataIn != "RUN") {         // Tunggu sampai "RUN" ditekan lagi
            if (Serial.available() > 0) {
              dataIn = Serial.readString();
              if ( dataIn == "RESET") {     
                break;
              }
            }
          }
        }
        // Jika penggeser kecepatan diubah
        if (dataIn.startsWith("ss")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          speedDelay = dataInS.toInt(); // Ubah kecepatan servo (waktu tunda)
        }
      }
      // Servo 1
      if (servo01SP[i] == servo01SP[i + 1]) {
      }
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo02SP[i] == servo02SP[i + 1]) {
      }
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo03SP[i] == servo03SP[i + 1]) {
      }
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo04SP[i] == servo04SP[i + 1]) {
      }
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }

      // Servo 5
      if (servo05SP[i] == servo05SP[i + 1]) {
      }
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }

      // Servo 6
      if (servo06SP[i] == servo06SP[i + 1]) {
      }
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}