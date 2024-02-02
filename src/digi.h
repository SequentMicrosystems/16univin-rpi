#ifndef DIGI_H
#define DIGI_H

#include "cli.h"

extern const CliCmdType CMD_DIGI_READ;
extern const CliCmdType CMD_DIGI_EDGE_WRITE;
extern const CliCmdType CMD_DIGI_EDGE_READ;
extern const CliCmdType CMD_DIGI_CNT_READ;
extern const CliCmdType CMD_DIGI_CNT_RESET;

int doDigiRead(int argc, char *argv[]);
int doDigiEdgeWrite(int argc, char *argv[]);
int doDigiEdgeRead(int argc, char *argv[]);
int doDigiCntRead(int argc, char *argv[]);
int doDigiCntReset(int argc, char *argv[]);

#endif /* DIGI_H */
