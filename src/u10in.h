#ifndef U5IN_H_
#define U5IN_H_

#include "cli.h"

extern const CliCmdType CMD_U10_IN_READ;

extern const CliCmdType CMD_U10_IN_CAL;


int doU10InRead(int argc, char *argv[]);

int doU10InCal(int argc, char *argv[]);

#endif /* U5IN_H_ */
