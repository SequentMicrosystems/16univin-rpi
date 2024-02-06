#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "led.h"


const CliCmdType CMD_LED_READ =
{
	"ledrd",
	2,
	&doLedRead,
	"  ledrd            Read led state\n",
	"  Usage 1:         "PROGRAM_NAME" <id> ledrd <channel[1.."STR(LED_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> ledrd\n",
	"  Example:         "PROGRAM_NAME" 0 ledrd 2  Get the state of led #2 on board #0\n"
};
int doLedRead(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERR;
	}
	if (argc == 3)
	{
		uint8_t buf[2];
		uint16_t leds = 0;
		if (OK != i2cMem8Read(dev, I2C_MEM_LEDS, buf, 2))
		{
			printf("Fail to read!\n");
			return ERR;
		}
		memcpy(&leds, buf, 2);

		for (int rel = 1; rel <= LED_CH_NO; ++rel)
		{
			if (buf[0] & (1 << (rel - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 4)
	{
		uint8_t buf[2];
		uint16_t leds = 0;
		if (OK != i2cMem8Read(dev, I2C_MEM_LEDS, buf, 2))
		{
			printf("Fail to write!\n");
			return ERR;
		}
		memcpy(&leds, buf, 2);
		int rel = atoi(argv[3]);
		if (! (1 <= rel && rel <= LED_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERR;
		}
		if (buf[0] & (1 << (rel - 1)))
		{
			printf("1\n"); /* rel ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_LED_WRITE =
{
	"ledwr",
	2,
	&doLedWrite,
	"  ledwr            Change led state\n",
	"  Usage 1:         "PROGRAM_NAME" <id> ledwr <channel[1.."STR(LED_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> ledwr <mask[0.."STR(MASK(LED_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" 0 ledwr 2 1  Set the state of led #2 to ON\n"
};
int doLedWrite(int argc, char *argv[])
{
	if (! (argc == 4 || argc == 5))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERR;
	}
	if (argc == 4)
	{
		uint16_t state = 0;
		state = (uint16_t)atoi(argv[3]);
		
		uint8_t buf[2];
		memcpy(buf, &state, 2);
		if (OK != i2cMem8Write(dev, I2C_MEM_LEDS, buf, 2))
		{
			printf("Fail to write!\n");
			return ERR;
		}
	}
	else if (argc == 5)
	{
		int state = 0;
		int rel = atoi(argv[3]);
		if (! (1 <= rel && rel <= LED_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERR;
		}
		state = atoi(argv[4]);
		uint8_t buf[1];
		buf[0] = 0xff & rel;
		if (state > 0)
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_LED_SET, buf, 1))
			{
				printf("Fail to write!\n");
				return ERR;
			}
		}
		else
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_LED_CLR, buf, 1))
			{
				printf("Fail to write!\n");
				return ERR;
			}
		}
	}
	return OK ;
}

