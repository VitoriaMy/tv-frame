#include "state_machine.h"
#include "config.h"
#include "motion_controller.h"
#include "bluetooth_manager.h"
#include "safety_manager.h"

extern SystemState g_state;
extern SystemConfig g_config;

void stateMachineInit() {
}

void stateMachineUpdate() {
  if (safetyHasFault()) {
    g_state = ERROR_STATE;
  }

  switch (g_state) {
    case HOMING:
      motionMoveTo(g_config.homePosition);
      if (motionAtTarget(g_config.homePosition, g_config.positionTolerance)) {
        motionStop();
        g_state = IDLE_CLOSED;
      }
      break;

    case IDLE_CLOSED:
      if (bluetoothGetState() == DEVICE_ONLINE) {
        motionMoveTo(g_config.workPosition);
        g_state = OPENING_AND_EXTENDING;
      }
      break;

    case OPENING_AND_EXTENDING:
      if (motionAtTarget(g_config.workPosition, g_config.positionTolerance)) {
        motionStop();
        g_state = IDLE_OPEN;
      }
      break;

    case IDLE_OPEN:
      if (bluetoothGetState() == DEVICE_OFFLINE) {
        motionMoveTo(g_config.homePosition);
        g_state = RETRACTING_AND_CLOSING;
      }
      break;

    case RETRACTING_AND_CLOSING:
      if (motionAtTarget(g_config.homePosition, g_config.positionTolerance)) {
        motionStop();
        g_state = IDLE_CLOSED;
      }
      break;

    case ERROR_STATE:
      motionEmergencyStop();
      break;

    case MANUAL_MODE:
      break;
  }
}
