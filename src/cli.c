#include "analog.h"

#include "u10in.h"
#include "calib.h"
#include "cli.h"
#include "comm.h"
#include "data.h"
#include "digi.h"
#include "led.h"
#include "help.h"
#include "rs485.h"
#include "rtc.h"
#include "wdt.h"
#include "rin.h"

const CliCmdType *gCmdArray[] = {
	&CMD_HELP,
	&CMD_VERSION,
	&CMD_BOARD,
	&CMD_DIGI_READ,
	&CMD_DIGI_EDGE_WRITE,
	&CMD_DIGI_EDGE_READ,
	&CMD_DIGI_CNT_READ,
	&CMD_DIGI_CNT_RESET,
	&CMD_CAL_STATUS,
	&CMD_LED_READ,
	&CMD_LED_WRITE,
	&CMD_RTC_GET,
	&CMD_RTC_SET,
	&CMD_WDT_RELOAD,
	&CMD_WDT_SET_PERIOD,
	&CMD_WDT_GET_PERIOD,
	&CMD_WDT_SET_INIT_PERIOD,
	&CMD_WDT_GET_INIT_PERIOD,
	&CMD_WDT_SET_OFF_PERIOD,
	&CMD_WDT_GET_OFF_PERIOD,
	&CMD_WDT_GET_RESET_COUNT,
	&CMD_WDT_CLR_RESET_COUNT,
	&CMD_U10_IN_READ,
	&CMD_U10_IN_CAL,
	&CMD_R1K_IN_READ,
	&CMD_R1K_IN_CAL,
	&CMD_R10K_IN_READ,
	&CMD_R10K_IN_CAL,
	&CMD_CFG485_READ,
	&CMD_CFG485_WRITE,
	&CMD_IN_CONFIG_READ,
	&CMD_IN_CONFIG_WRITE,
	0
};
