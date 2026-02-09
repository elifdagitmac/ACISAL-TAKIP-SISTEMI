#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pin Tanımlamaları
const int trigPin = 6;    // Trig -> Arduino Pin 6
const int echoPin = 7;    // Echo -> Arduino Pin 7
const int servoPin = 5;   // Servo Sinyal (Sarı) -> Arduino Pin 5
const int buzzerPin = 8;  // Buzzer I/O (Siyah) -> Arduino Pin 8

// Değişkenler
long duration;
int distance;
int angle = 60;
bool direction = true; 

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD SDA -> A4, SCL -> A5

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  myServo.attach(servoPin);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Radar Baslatiliyor");
  delay(1500);
  lcd.clear();
}

void loop() {
  distance = calculateDistance();

  // 30 cm ve daha yakında bir cisim algılanırsa
  if (distance > 0 && distance <= 30) {
    
    // LCD Bilgilendirme
    lcd.setCursor(0, 0);
    lcd.print("Cisim Algilandi ");
    lcd.setCursor(0, 1);
    lcd.print("Mesafe: ");
    lcd.print(distance);
    lcd.print(" cm   ");

    // Cisim uzaklaşana kadar sistem kilitlenir
    while (calculateDistance() <= 30) {
      int currentDist = calculateDistance();
      
      // Buzzer frekansını mesafeye göre ayarla (Yaklaştıkça ses incelir)
      // 2cm'de 1200Hz (ince), 30cm'de 300Hz (kalın) ses verir
      int toneFreq = map(currentDist, 2, 30, 1200, 300);
      tone(buzzerPin, toneFreq);
      
      // LCD'deki mesafeyi anlık güncelle
      lcd.setCursor(8, 1);
      lcd.print(currentDist);
      lcd.print(" cm   ");
      delay(50); 
    }
    
    // Cisim uzaklaştığında sesi kes ve ekranı temizle
    noTone(buzzerPin);
    lcd.clear();
    
  } else {
    // Taramaya devam et 
    noTone(buzzerPin); // Cisim yoksa ses yok
    
    lcd.setCursor(0, 0);
    lcd.print("Tarama Yapiliyor");
    lcd.setCursor(0, 1);
    lcd.print("Aci: ");
    lcd.print(angle);
    lcd.print(" derece  ");

    myServo.write(angle);
    
    // Açı değiştirme mantığı
    if (direction) {
      angle++;
      if (angle >= 120) direction = false;
    } else {
      angle--;
      if (angle <= 60) direction = true;
    }
    delay(35); // Tarama hızı 
  }
}

// Ultrasonik Sensör Ölçüm Fonksiyonu
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  // Ses hızı üzerinden cm hesaplama
  int d = duration * 0.034 / 2;
  return d;
}



