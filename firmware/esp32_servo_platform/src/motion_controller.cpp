#include "motion_controller.h"

static long currentPosition = 0;
static bool busy = false;

void motionInit() {
}

void motionMoveTo(long target) {
  currentPosition = target;
  busy = true;
}

void motionStop() {
  busy = false;
}

void motionEmergencyStop() {
  busy = false;
}

bool motionAtTarget(long target, int tolerance) {
  long diff = currentPosition - target;
  if (diff < 0) diff = -diff;
  return diff <= tolerance;
}

long motionGetPosition() {
  return currentPosition;
}

bool motionIsBusy() {
  return busy;
}
