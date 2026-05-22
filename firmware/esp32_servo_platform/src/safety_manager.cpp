#include "safety_manager.h"

static FaultCode currentFault = FAULT_NONE;

void safetyInit() {
}

void safetyUpdate() {
}

FaultCode safetyGetFault() {
  return currentFault;
}

bool safetyHasFault() {
  return currentFault != FAULT_NONE;
}
