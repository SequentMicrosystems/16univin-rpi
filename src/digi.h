#ifndef DIGI_H
#define DIGI_H

#include "cli.h"

extern const CliCmdType CMD_DIGI_READ;
extern const CliCmdType CMD_DIGI_EDGE_WRITE;
extern const CliCmdType CMD_DIGI_EDGE_READ;
extern const CliCmdType CMD_DIGI_CNT_READ;
extern const CliCmdType CMD_DIGI_CNT_RESET;
extern const CliCmdType CMD_IN_CONFIG_READ;
extern const CliCmdType CMD_IN_CONFIG_WRITE;

int doDigiRead(int argc, char *argv[]);
int doDigiEdgeWrite(int argc, char *argv[]);
int doDigiEdgeRead(int argc, char *argv[]);
int doDigiCntRead(int argc, char *argv[]);
int doDigiCntReset(int argc, char *argv[]);
int doInCfgWrite(int argc, char *argv[]);
int doInCfgRead(int argc, char *argv[]);

#endif /* DIGI_H */
