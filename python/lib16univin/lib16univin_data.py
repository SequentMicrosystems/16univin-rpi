CARD_NAME = "Sixteen Analog/Digital Inputs"
VERSION = "1.0.1"

SLAVE_OWN_ADDRESS_BASE = 0x58
STACK_LEVEL_MAX = 7

CALIBRATION_KEY = 0xaa
RESET_CALIBRATION_KEY  = 0x55
WDT_RESET_SIGNATURE     = 0xca
WDT_RESET_COUNT_SIGNATURE    = 0xbe

VOLT_TO_MILIVOLT = 1000
MILIAMPER_TO_MICROAMPER = 1000

# i2c memory addresses
class I2C_MEM:
    LEDS = 0
    LED_SET = 2
    LED_CLR = 3
    DRY_CONTACT = 4
    U_IN = 6
    R1K_IN = 38
    R10K_IN = 70
    DIAG_TEMPERATURE_ADD = 102
    CNT_ENABLE = 103
    DC_CNT_RST = 105

    DC_CNT_ADD = 106

    CALIB_VALUE = 171
    CALIB_CHANNEL = 175
    CALIB_KEY = 176
    CALIB_STATUS = 177
    WDT_RESET_ADD = 191
    WDT_INTERVAL_SET_ADD = 192
    WDT_INTERVAL_GET_ADD = 194
    WDT_INIT_INTERVAL_SET_ADD = 196
    WDT_INIT_INTERVAL_GET_ADD = 198
    WDT_RESET_COUNT_ADD = 200
    WDT_CLEAR_RESET_COUNT_ADD = 202
    WDT_POWER_OFF_INTERVAL_SET_ADD = 203
    WDT_POWER_OFF_INTERVAL_GET_ADD = 207
    REVISION_HW_MAJOR_ADD = 219
    REVISION_HW_MINOR_ADD = 220
    REVISION_MAJOR_ADD = 221
    REVISION_MINOR_ADD = 222
    BUTTON = 211
    RTC_YEAR_ADD = 178
    RTC_MONTH_ADD = 179
    RTC_DAY_ADD = 180
    RTC_HOUR_ADD = 181
    RTC_MINUTE_ADD = 182
    RTC_SECOND_ADD = 183
    RTC_SET_YEAR_ADD = 184
    RTC_SET_MONTH_ADD = 185
    RTC_SET_DAY_ADD = 186
    RTC_SET_HOUR_ADD = 187
    RTC_SET_MINUTE_ADD = 188
    RTC_SET_SECOND_ADD = 189
    RTC_CMD_ADD = 190
    SLAVE_BUFF_SIZE = 255

class CALIB:
    IN_PROGRESS = 0
    DONE = 1
    ERROR = 2
    RTD_CH1 = 1
    U_IN_CH1 = 3
    I_IN_CH1 = 5
    U_OUT_CH1 = 7
    I_OUT_CH1 = 9
    LAST_CH = 10

CHANNEL_NO = {
    "led": 16,
    "dig_in": 16,
    "u_in": 16,
    "r1k_in": 16,
    "r10k_in": 16,
}

