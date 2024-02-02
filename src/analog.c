#include "analog.h"
#include "calib.h"
#include "comm.h"

int val16Get(int dev, int baseAddr, int ch, float scale, float* val) {
	int addr = baseAddr + ANALOG_VAL_SIZE * (ch - 1);
	// TODO: check if addr in I2C_MEM_SIZE
	uint8_t buf[ANALOG_VAL_SIZE];
	if(OK != i2cMem8Read(dev, addr, buf, ANALOG_VAL_SIZE)) {
		return ERR;
	}
	uint16_t raw = 0;
	memcpy(&raw, buf, ANALOG_VAL_SIZE);
	float fraw = raw;
	*val = fraw / scale;
	return OK;
}
int val16Set(int dev, int baseAddr, int ch, float scale, float val) {
	int addr = baseAddr + ANALOG_VAL_SIZE * (ch - 1);
	// TODO: check if addr in I2C_MEM_SIZE
	uint8_t buf[ANALOG_VAL_SIZE];
	int16_t raw = ceil(val * scale);
	memcpy(buf, &raw, 2);
	if(OK != i2cMem8Write(dev, addr, buf, ANALOG_VAL_SIZE)) {
		return ERR;
	}
	return OK;
}

// vi:fdm=marker
