#include <Arduino.h>

// ===== SERVO PINS =====
#define SERVO1 22   // SCL
#define SERVO2 17
#define SERVO3 16

// ===== PWM SETTINGS =====
#define SERVO_FREQ 50
#define SERVO_RES 16

#define SERVO_MIN 3277
#define SERVO_MAX 6554

// ===== CHANNELS =====
#define CH1 0
#define CH2 1
#define CH3 2

// ===== FUNCTION =====
void setServoAngle(int channel, int angle) {
  angle = constrain(angle, 0, 180);
  uint32_t duty = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  ledcWrite(channel, duty);
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  // Setup PWM channels
  ledcSetup(CH1, SERVO_FREQ, SERVO_RES);
  ledcSetup(CH2, SERVO_FREQ, SERVO_RES);
  ledcSetup(CH3, SERVO_FREQ, SERVO_RES);

  // Attach pins
  ledcAttachPin(SERVO1, CH1);
  ledcAttachPin(SERVO2, CH2);
  ledcAttachPin(SERVO3, CH3);

  Serial.println("3 Servo Test Ready");
}

// ===== LOOP =====
void loop() {

  Serial.println("All → 0°");
  setServoAngle(CH1, 0);
  setServoAngle(CH2, 0);
  setServoAngle(CH3, 0);
  delay(2000);

  Serial.println("All → 90°");
  setServoAngle(CH1, 90);
  setServoAngle(CH2, 90);
  setServoAngle(CH3, 90);
  delay(2000);

  Serial.println("All → 180°");
  setServoAngle(CH1, 180);
  setServoAngle(CH2, 180);
  setServoAngle(CH3, 180);
  delay(2000);

  // Fun extra: wave motion
  Serial.println("Wave motion");
  setServoAngle(CH1, 0);
  setServoAngle(CH2, 90);
  setServoAngle(CH3, 180);
  delay(2000);
}
