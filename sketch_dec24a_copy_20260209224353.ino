#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pin Tanımlamaları
const int trigPin = 6;    // Trig -> Arduino Pin 6
const int echoPin = 7;    // Echo -> Arduino Pin 7
const int servoPin = 5;   // Servo Signal (Yellow) -> Arduino Pin 5
const int buzzerPin = 8;  // Buzzer I/O (Black) -> Arduino Pin 8

// Variables
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

  // İf it recognize an object closer than 30 cm or in 30 cm
  if (distance > 0 && distance <= 30) {
    
    // LCD Information
    lcd.setCursor(0, 0);
    lcd.print("Cisim Algilandi ");
    lcd.setCursor(0, 1);
    lcd.print("Mesafe: ");
    lcd.print(distance);
    lcd.print(" cm   ");

    // System locks itself until the object goes 
    while (calculateDistance() <= 30) {
      int currentDist = calculateDistance();
      
      // Adjust the buzzer frequency according to the distance (The sound gets higher as you get closer)
      // It makes a 1200Hz (high) sound at 2cm and a 300Hz (low) sound at 30cm
      int toneFreq = map(currentDist, 2, 30, 1200, 300);
      tone(buzzerPin, toneFreq);
      
      // Update the distance in LCD for every moment 
      lcd.setCursor(8, 1);
      lcd.print(currentDist);
      lcd.print(" cm   ");
      delay(50); 
    }
    
    // Cut the sound and clear the screen when the object moves away
    noTone(buzzerPin);
    lcd.clear();
    
  } else {
    // Keep scanning 
    noTone(buzzerPin); // No object No sound
    
    lcd.setCursor(0, 0);
    lcd.print("Tarama Yapiliyor");
    lcd.setCursor(0, 1);
    lcd.print("Aci: ");
    lcd.print(angle);
    lcd.print(" derece  ");

    myServo.write(angle);
    
    // Angle changing logic
    if (direction) {
      angle++;
      if (angle >= 120) direction = false;
    } else {
      angle--;
      if (angle <= 60) direction = true;
    }
    delay(35); // Speed of scanning 
  }
}

// Ultrasonic Sensor Measurement Function
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  // Calculating cm based on sound speed
  int d = duration * 0.034 / 2;
  return d;
}



