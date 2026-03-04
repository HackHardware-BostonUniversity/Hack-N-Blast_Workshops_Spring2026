#include <Arduino.h>
#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];


// ================= CONTROLLER CALLBACKS =================
void onConnectedController(ControllerPtr ctl) {
  Serial.println("Controller connected!");
  myControllers[0] = ctl;
}

void onDisconnectedController(ControllerPtr ctl) {
  Serial.println("Controller disconnected!");
  myControllers[0] = nullptr;
}

// ================= PROCESS CONTROLLER =================

void processControllers() {
  for (auto ctl : myControllers) {
    if (ctl && ctl->isConnected() && ctl->hasData()) {
      if (ctl->isGamepad()) {
        processGamepad(ctl);
      }
    }
  }
}

void processGamepad(ControllerPtr ctl) {

  // ================= BUTTONS =================
  uint16_t buttons = ctl->buttons();

  if (buttons) {
    if (buttons & BUTTON_A) Serial.println("A pressed");
    if (buttons & BUTTON_B) Serial.println("B pressed");
    if (buttons & BUTTON_X) Serial.println("X pressed");
    if (buttons & BUTTON_Y) Serial.println("Y pressed");
    if (buttons & BUTTON_L1) Serial.println("L1 pressed");
    if (buttons & BUTTON_R1) Serial.println("R1 pressed");
    if (buttons & BUTTON_START) Serial.println("Start pressed");
    if (buttons & BUTTON_SELECT) Serial.println("Select pressed");
  }

  // ================= TRIGGERS =================
  int throttle = ctl->throttle();   // R2 (0–1023)
  int brake    = ctl->brake();      // L2 (0–1023)

  if (abs(throttle) > 10) {
    Serial.printf("Throttle (R2): %d\n", throttle);
  }

  if (abs(brake) > 10) {
    Serial.printf("Brake (L2): %d\n", brake);
  }

  // ================= JOYSTICKS =================
  int lx = ctl->axisX();   // -511 to 512
  int ly = ctl->axisY();
  int rx = ctl->axisRX();
  int ry = ctl->axisRY();

  int deadzone = 25;

  if (abs(lx) > deadzone || abs(ly) > deadzone) {
    Serial.printf("Left Stick -> X: %d  Y: %d\n", lx, ly);
  }

  if (abs(rx) > deadzone || abs(ry) > deadzone) {
    Serial.printf("Right Stick -> X: %d  Y: %d\n", rx, ry);
  }
}


// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  // Bluepad32 Setup
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.enableVirtualDevice(false);

  Serial.println("Ready. Press PS button to connect.");
}

// ================= LOOP =================
void loop() {
  if (BP32.update()) {
    processControllers();
  }

  delay(10);
}
