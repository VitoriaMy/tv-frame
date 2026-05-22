#pragma once
#include "config.h"

void safetyInit();
void safetyUpdate();
FaultCode safetyGetFault();
bool safetyHasFault();
