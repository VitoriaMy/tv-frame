#pragma once

void motionInit();
void motionMoveTo(long target);
void motionStop();
void motionEmergencyStop();
bool motionAtTarget(long target, int tolerance);
long motionGetPosition();
bool motionIsBusy();
