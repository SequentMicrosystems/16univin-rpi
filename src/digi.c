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

int doInCfgWrite(int argc, char *argv[]);
const CliCmdType CMD_IN_CONFIG_WRITE = 
   {"incfgwr",
	 2, 
	 &doInCfgWrite,
	"\tincfgwr:		Config input type to 0-10V(0); 1k Thermistor(1) or 10k Thermistor(2)\n",
	"\tUsage:		"PROGRAM_NAME" <id> incfgwr <channel> <0/1/2>\n",
	"\tExample:		"PROGRAM_NAME" 0 incfgwr 2 1; Set channel #2 on Board #0 as 1k thermistor input\n"
	};

int doInCfgWrite(int argc, char *argv[])
{
	int pin = 0;
	int val = 0;
	int dev = 0;
	int resp = 0;
	uint8_t buff[6];
	
	if ( argc != 5)
	{
		printf("%s", CMD_IN_CONFIG_WRITE.usage);
		return ARG_CNT_ERR;
	}

	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERR;
	}
	
	pin = atoi(argv[3]);
	if ( (pin < MIN_CH_NO) || (pin > UNIV_CH_NR))
	{
		printf("Input channel number value out of range\n");
		return ARG_RANGE_ERR;
	}
	val = atoi(argv[4]);

			
	resp = i2cMem8Read(dev, I2C_MEM_UIN_SEL, buff, 6);
	if (OK != resp)
	{
		printf("Fail to read config!\n");
		return ERR;
	}
	uint16_t uin = 0;
	uint16_t r1k = 0;
	uint16_t r10k = 0;
	memcpy(&uin, buff, 2);
	memcpy(&r1k, buff+2, 2);
	memcpy(&r10k, buff+4, 2);

	switch (val)
	{
	case 0:
		uin |= 1 << (pin - 1);
		r1k &= ~(1 << (pin - 1));
		r10k &= ~(1 << (pin - 1));
		break;
	case 1:
		r1k |= 1 << (pin - 1);
		uin &= ~(1 << (pin - 1));
		r10k &= ~(1 << (pin - 1));
		break;
	case 2:
		r10k |= 1 << (pin - 1);
		r1k &= ~(1 << (pin - 1));
		uin &= ~(1 << (pin - 1));
		break;
	default:
		printf("Invalid input type (0->0-10V; 1->1K; 2->10k)!\n");
		return ARG_RANGE_ERR;
		break;
	}
	memcpy(buff, &uin, 2);
	memcpy(buff+2, &r1k, 2);
	memcpy(buff+4, &r10k, 2);

	resp = i2cMem8Write(dev, I2C_MEM_UIN_SEL, buff, 6);
	if (OK != resp)
	{
		printf("Fail to write configuration\n");
		return ERR;
	}

	return OK;
}


int doInCfgRead(int argc, char *argv[]);
const CliCmdType CMD_IN_CONFIG_READ = 
   {"incfgrd", 2, &doInCfgRead,
	"\tincfgrd:		Display input type  0-10V(0); 1k Thermistor(1) or 10k Thermistor(2)\n",
	"\tUsage:		"PROGRAM_NAME" <id> incfgrd <channel>\n",
	"\tExample:		"PROGRAM_NAME" 0 incfgrd 2; Display channel #2 on Board #0 input type\n"
	};

int doInCfgRead(int argc, char *argv[])
{
	int pin = 0;
	int dev = 0;
	int resp = 0;
	uint8_t buff[6];
	

	if ( argc != 4)
	{
		printf("%s", CMD_IN_CONFIG_READ.usage);
		return ARG_CNT_ERR;
	}

	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERR;
	}
	
	pin = atoi(argv[3]);
	if ( (pin < MIN_CH_NO) || (pin > UNIV_CH_NR))
	{
		printf("Input channel number value out of range\n");
		return ARG_RANGE_ERR;
	}
	
	resp = i2cMem8Read(dev, I2C_MEM_UIN_SEL, buff, 6);
	if (OK != resp)
	{
		printf("Fail to read config!\n");
		return ERR;
	}
	uint16_t uin = 0;
	uint16_t r1k = 0;
	uint16_t r10k = 0;
	memcpy(&uin, buff, 2);
	memcpy(&r1k, buff+2, 2);
	memcpy(&r10k, buff+4, 2);
	if(0 != (uin & (1 << (pin - 1))))
	{
		printf("0\n");
	}
	else if(0 != (r1k & (1 << (pin - 1))))
	{
		printf("1\n");
	}
	else if(0 != (r10k & (1 << (pin - 1))))
	{
		printf("2\n");
	}
	else
	{
		printf("Invalid configuration detected!\n");
	}
	return OK;
}