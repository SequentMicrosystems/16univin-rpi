#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "comm.h"
#include "data.h"
#include "digi.h"

// TODO: Add ranges in all error messages

bool badDigiCh(uint8_t ch)
{
	if (! (MIN_CH_NO <= ch && ch <= UNIV_CH_NR))
	{
		printf("Digital channel number value out of range![%d..%d]\n", MIN_CH_NO,
			UNIV_CH_NR);
		return true;
	}
	return false;
}
bool badDigiEncCh(uint8_t ch)
{
	if (! (MIN_CH_NO <= ch && ch <= UNIV_CH_NR / 2))
	{
		printf("Digital encoded channel number value out of range![%d..%d]\n",
			MIN_CH_NO, UNIV_CH_NR / 2);
		return true;
	}
	return false;
}

int digiChGet(int dev, uint8_t ch, State *state)
{
	if (NULL == state)
	{
		return ERR;
	}
	if (badDigiCh(ch))
	{
		printf("Invalid digi ch nr!\n");
		return ERR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_DRY_CONTACT, buf, 2))
	{
		return ERR;
	}
	uint16_t val = 0;
	memcpy(&val, buf, 2);
	if (val & (1 << (ch - 1)))
	{
		*state = ON;
	}
	else
	{
		*state = OFF;
	}
	return OK ;
}

int digiGet(int dev, int *val)
{
	uint8_t buff[2];
	if (NULL == val)
	{
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_DRY_CONTACT, buff, 2))
	{
		return ERR;
	}
	uint16_t val16 = 0;
	memcpy(&val16, buff, 2);
	*val = val16;
	return OK ;
}

int digiEdgeGet(int dev, uint8_t ch, uint8_t *val)
{
	if (NULL == val)
	{
		return ERR;
	}
	if (badDigiCh(ch))
	{
		printf("Invalid digital input ch nr!\n");
		return ERR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_DC_CNT_ENABLE, buf, 2))
	{
		return ERR;
	}
	uint16_t edge = 0;
	memcpy(&edge, buf, 2);
	*val = 0;
	if (edge & (1 << (ch - 1)))
	{
		*val |= 1 << 0;
	}
	return OK ;
}

int digiEdgeSet(int dev, uint8_t ch, uint8_t val)
{
	if (badDigiCh(ch))
	{
		return ERR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_DC_CNT_ENABLE, buf, 2))
	{
		return ERR;
	}
	uint16_t edge = 0;
	memcpy(&edge, buf, 2);
	uint32_t mask = 1 << (ch - 1);
	if (val > 0)
	{ //check rising
		edge |= mask;
	}
	else
	{
		edge &= ~mask;
	}
	memcpy(buf, &edge, 2);
	if (OK != i2cMem8Write(dev, I2C_MEM_DC_CNT_ENABLE, buf, 2))
	{
		return ERR;
	}
	return OK ;
}

int digiCountGet(int dev, uint8_t ch, uint32_t *val)
{
	if (badDigiCh(ch))
	{
		return ERR;
	}
	if (NULL == val)
	{
		return ERR;
	}
	uint8_t buf[4];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_DC_CNT_ADD + COUNTER_SIZE * (ch - 1), buf,
			COUNTER_SIZE))
	{
		return ERR;
	}
	memcpy(val, buf, 4);
	return OK ;
}

int digiCountReset(int dev, uint8_t ch)
{
	if (badDigiCh(ch))
	{
		return ERR;
	}
	if (OK != i2cMem8Write(dev, I2C_MEM_DC_CNT_RST_ADD, &ch, 1))
	{
		return ERR;
	}
	return OK ;
}

const CliCmdType CMD_DIGI_READ =
{
	"dird",
	2,
	&doDigiRead,
	"  dird            Read digital inputs status\n",
	"  Usage:           "PROGRAM_NAME" <id> dird <channel>\n"
	"  Usage:           "PROGRAM_NAME" <id> dird\n",
	"  Example:         "PROGRAM_NAME" 0 dird 2; Read Status of Digital input ch #2 on Board #0\n"
};
int doDigiRead(int argc, char *argv[])
{
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERR;
	}
	if (argc == 4)
	{
		int channel = atoi(argv[3]);
		if (badDigiCh(channel))
		{
			return ARG_RANGE_ERR;
		}
		State state = STATE_COUNT;
		if (OK != digiChGet(dev, channel, &state))
		{
			printf("Fail to read!\n");
			return ERR;
		}
		if (state != OFF)
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}
	else if (argc == 3)
	{
		int val;
		if (OK != digiGet(dev, &val))
		{
			printf("Fail to read!\n");
			return ERR;
		}
		printf("%d\n", val);
	}
	else
	{
		return ARG_CNT_ERR;
	}
	return OK ;
}

const CliCmdType CMD_DIGI_EDGE_READ =
{
	"cntenrd",
	2,
	&doDigiEdgeRead,
	"  cntenrd        Read digital inputs counting function 0 - disabled; 1 - enabled\n",
	"  Usage:           "PROGRAM_NAME" <id> cntenrd <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 cntenrd 2; Read counting edges of digicoupled channel #2 on Board #0\n"
};
int doDigiEdgeRead(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERR;
	}
	uint8_t channel = (uint8_t)atoi(argv[3]);
	if (badDigiCh(channel))
	{
		return ARG_RANGE_ERR;
	}
	uint8_t val;
	if (OK != digiEdgeGet(dev, channel, &val))
	{
		printf("Fail to read!\n");
		return ERR;
	}
	printf("%d\n", val);
	return OK ;
}

const CliCmdType CMD_DIGI_EDGE_WRITE =
{
	"cntenwr",
	2,
	&doDigiEdgeWrite,
	"  cntenwr        Set digital input channel counting transitions  0- count disable; 1-count enable\n",
	"  Usage:           "PROGRAM_NAME" <id> cntenwr <channel> <0/1> \n",
	"  Example:         "PROGRAM_NAME" 0 cntenwr 2 1; Set Digital input channel #2 on Board #0 to count transitions\n"
};
int doDigiEdgeWrite(int argc, char *argv[])
{
	if ( (argc != 5))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERR;
	}
	int channel = atoi(argv[3]);
	if (badDigiCh(channel))
	{
		return ARG_RANGE_ERR;
	}
	uint8_t state = 0;
	if (strcasecmp(argv[4], "none") == 0)
	{
		state = 0;
	}
	else if (strcasecmp(argv[4], "up") == 0
		|| strcasecmp(argv[4], "rising") == 0)
	{
		state = 1;
	}
	else
	{
		state = (uint8_t)atoi(argv[4]);
		// TODO: FIXME: bug: atoi returns 0 even if argv[4] is not a number
		if (! (state <= 1))
		{
			printf("Invalid edge counting type [0/1]!\n");
			return ARG_RANGE_ERR;
		}
	}
	if (OK != digiEdgeSet(dev, channel, state))
	{
		printf("Fail to write digital input ch edge counting \n");
		return ERR;
	}
	return OK ;
}

const CliCmdType CMD_DIGI_CNT_READ =
{
	"dicntrd",
	2,
	&doDigiCntRead,
	"  dicntrd         Read digital inputs edges count for one channel\n",
	"  Usage:           "PROGRAM_NAME" <id> dicntrd <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 dicntrd 2; Read contor of digi input #2 on Board #0\n"
};
int doDigiCntRead(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERR;
	}
	uint8_t channel = 0;
	channel = atoi(argv[3]);
	if (badDigiCh(channel))
	{
		printf("Digital input ch number value out of range!\n");
		return ARG_RANGE_ERR;
	}
	uint32_t val = 0;
	if (OK != digiCountGet(dev, channel, &val))
	{
		printf("Fail to read!\n");
		return ERR;
	}
	printf("%u\n", val);
	return OK ;
}

const CliCmdType CMD_DIGI_CNT_RESET =
{
	"dicntrst",
	2,
	&doDigiCntReset,
	"  dicntrst        Reset digital inputs edges count for one channel\n",
	"  Usage:           "PROGRAM_NAME" <id> dicntrst <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 dicntrst 2; Reset contor of digi input #2 on Board #0\n"
};
int doDigiCntReset(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERR;
	}
	uint8_t channel = 0;
	channel = atoi(argv[3]);
	if (badDigiCh(channel))
	{
		printf("Digital ch number value out of range!\n");
		return ARG_RANGE_ERR;
	}
	if (OK != digiCountReset(dev, channel))
	{
		printf("Fail to reset!\n");
		return ERR;
	}
	return OK ;
}
