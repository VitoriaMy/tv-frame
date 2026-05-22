#include "config.h"
#include "state_machine.h"
#include "motion_controller.h"
#include "bluetooth_manager.h"
#include "safety_manager.h"
#include "ui_feedback.h"

SystemState g_state = HOMING;

void setup() {
  uiInit();
  motionInit();
  bluetoothInit();
  safetyInit();
  stateMachineInit();
}

void loop() {
  bluetoothUpdate();
  safetyUpdate();
  stateMachineUpdate();
  uiUpdate();
}
