#include "bluetooth_manager.h"

static DeviceConnectionState currentState = DEVICE_OFFLINE;

void bluetoothInit() {
}

void bluetoothUpdate() {
}

DeviceConnectionState bluetoothGetState() {
  return currentState;
}
