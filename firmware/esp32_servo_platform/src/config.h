#pragma once

enum SystemState {
  IDLE_CLOSED,
  HOMING,
  OPENING_AND_EXTENDING,
  IDLE_OPEN,
  RETRACTING_AND_CLOSING,
  ERROR_STATE,
  MANUAL_MODE
};

enum DeviceConnectionState {
  DEVICE_OFFLINE,
  DEVICE_ONLINE,
  DEVICE_UNCERTAIN
};

enum FaultCode {
  FAULT_NONE,
  FAULT_HOME_TIMEOUT,
  FAULT_OPEN_TIMEOUT,
  FAULT_CLOSE_TIMEOUT,
  FAULT_LIMIT_TRIGGERED,
  FAULT_POSITION_NOT_REACHED,
  FAULT_BLUETOOTH_UNSTABLE,
  FAULT_MANUAL_ABORT
};

struct SystemConfig {
  long homePosition = 0;
  long workPosition = 29000;
  int positionTolerance = 20;
  unsigned long homingTimeoutMs = 10000;
  unsigned long openTimeoutMs = 15000;
  unsigned long closeTimeoutMs = 15000;
  unsigned long bluetoothStableDelayMs = 3000;
  int manualSpeed = 100;
  bool buzzerEnable = true;
};

extern SystemConfig g_config;
