#include "controller.h"

int selectMode() {
  while (!signalSNES(SNESPAD_SELECT)) {
  }
  return 0;
}

