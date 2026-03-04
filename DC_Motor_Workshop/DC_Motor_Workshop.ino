#include <Arduino.h>
#include "driver/ledc.h"

// ================= L298N #1 =================
#define ENA 25
#define IN1 26
#define IN2 27

#define ENB 33
#define IN3 32
#define IN4 14

#define ENA_CH 3
#define ENB_CH 4

#define MOTOR_FREQ 20000
#define MOTOR_RES 8

// ================= DC MOTOR FUNCTION =================
void driveMotor(int EN_CH, int pin1, int pin2, int speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else if (speed < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  ledcWrite(EN_CH, speed);
}


void setup() {
  // Set motor direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set PWM pins
  ledcSetup(ENA_CH, MOTOR_FREQ, MOTOR_RES);
  ledcAttachPin(ENA, ENA_CH);
  ledcSetup(ENB_CH, MOTOR_FREQ, MOTOR_RES);
  ledcAttachPin(ENB, ENB_CH);

}

void loop() {
  // Drive motor to move forward and backward
  driveMotor(ENA_CH, IN1, IN2, 200);
  delay(1000);
  driveMotor(ENA_CH, IN1, IN2, 0);
  delay(1000);
  driveMotor(ENB_CH, IN3, IN4, 200);
  delay(1000);
  driveMotor(ENB_CH, IN3, IN4, 0);
  delay(1000);
  
  driveMotor(ENA_CH, IN1, IN2, -200);
  delay(1000);
  driveMotor(ENA_CH, IN1, IN2, 0);
  delay(1000);
  driveMotor(ENB_CH, IN3, IN4, -200);
  delay(1000);
  driveMotor(ENB_CH, IN3, IN4, 0);
  delay(1000);

}
