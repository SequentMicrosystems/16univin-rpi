#ifndef ANALOG_H
#define ANALOG_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calib.h"
#include "data.h"
#include "comm.h"

int val16Get(int dev, int baseAddr, int ch, float scale, float* val);
int val16Set(int dev, int baseAddr, int ch, float scale, float val);

#endif /* ANALOG_H */

// vi:fdm=marker
