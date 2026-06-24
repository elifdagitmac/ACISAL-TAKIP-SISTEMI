# Angular Tracking System

A radar-based angular tracking system that scans between 60–120 degrees and detects 
objects within 30 cm range, providing both visual and auditory alerts in real time.

## Features
- Servo-controlled angular scanning (60°–120°)
- Ultrasonic distance detection (trigger threshold: 30 cm)
- Real-time LCD display feedback
- Auditory alert via active buzzer

## Hardware Components
| Component | Model |
|---|---|
| Microcontroller | Arduino UNO R3 |
| Distance Sensor | HC-SR04 Ultrasonic |
| Actuator | SG90 Servo Motor |
| Display | 16x2 I2C LCD |
| Alert | MH-FMD Active Buzzer |

## Wiring
| Component | Pin |
|---|---|
| HC-SR04 Trig | Pin 6 |
| HC-SR04 Echo | Pin 7 |
| Servo Motor Signal | Pin 5 |
| Buzzer I/O | Pin 8 |
| LCD SDA | A4 |
| LCD SCL | A5 |

## Getting Started
1. Connect components according to the wiring table above
2. Open `sketch_dec24a_copy_...ino` in Arduino IDE
3. Select **Arduino UNO** as board and your COM port
4. Upload the sketch

## Results
Tested across various environments. All functions performed correctly 
and consistently within defined parameters.




