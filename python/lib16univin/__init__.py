#!/usr/bin/python3

from smbus2 import SMBus
import struct
import datetime

import lib16univin.lib16univin_data as data
I2C_MEM = data.I2C_MEM
CHANNEL_NO = data.CHANNEL_NO


class SM16univin: 
    """Python class to control the 16 Universal Analog Inputs Card for Raspberry Pi.

    Args:
        stack (int): Stack level/device number.
        i2c (int): i2c bus number
    """
    def __init__(self, stack=0, i2c=1):
        if stack < 0 or stack > data.STACK_LEVEL_MAX:
            raise ValueError("Invalid stack level!")
        self._hw_address_ = data.SLAVE_OWN_ADDRESS_BASE + stack
        self._i2c_bus_no = i2c
        self.bus = SMBus(self._i2c_bus_no)
        try:
            self._card_rev_major = self.bus.read_byte_data(self._hw_address_, I2C_MEM.REVISION_HW_MAJOR_ADD)
            self._card_rev_minor = self.bus.read_byte_data(self._hw_address_, I2C_MEM.REVISION_HW_MINOR_ADD)
        except Exception:
            print("{} not detected!".format(data.CARD_NAME))
            raise

    def _get_byte(self, address):
        return self.bus.read_byte_data(self._hw_address_, address)
    def _get_word(self, address):
        return self.bus.read_word_data(self._hw_address_, address)
    def _get_i16(self, address):
        buf = self.bus.read_i2c_block_data(self._hw_address_, address, 2)
        i16_value = struct.unpack("h", bytearray(buf))[0]
        return i16_value
    def _get_float(self, address):
        buf = self.bus.read_i2c_block_data(self._hw_address_, address, 4)
        float_value = struct.unpack("f", bytearray(buf))[0]
        return float_value
    def _get_i32(self, address):
        buf = self.bus.read_i2c_block_data(self._hw_address_, address, 4)
        i32_value = struct.unpack("i", bytearray(buf))[0]
        return i32_value
    def _get_u32(self, address):
        buf = self.bus.read_i2c_block_data(self._hw_address_, address, 4)
        u32_value = struct.unpack("I", bytearray(buf))[0]
        return u32_value
    def _get_block_data(self, address, byteno=4):
        return self.bus.read_i2c_block_data(self._hw_address_, address, byteno)
    def _set_byte(self, address, value):
        self.bus.write_byte_data(self._hw_address_, address, value)
    def _set_word(self, address, value):
        self.bus.write_word_data(self._hw_address_, address, value)
    def _set_float(self, address, value):
        ba = bytearray(struct.pack("f", value))
        self.bus.write_block_data(self._hw_address_, address, ba)
    def _set_i32(self, address, value):
        ba = bytearray(struct.pack("i", value))
        self.bus.write_block_data(self._hw_address_, address, ba)
    def _set_block(self, address, ba):
        self.bus.write_i2c_block_data(self._hw_address_, address, ba)

    @staticmethod
    def _check_channel(channel_type, channel):
        if not (0 <= channel and channel <= CHANNEL_NO[channel_type]):
            raise ValueError("Invalid {} channel number. Must be [1..{}]!".format(channel_type, CHANNEL_NO[channel_type]))
    

    def get_version(self):
        """Get firmware version.

        Returns: (int) Firmware version number
        """
        version_major = self._get_byte(I2C_MEM.REVISION_MAJOR_ADD)
        version_minor = self._get_byte(I2C_MEM.REVISION_MINOR_ADD)
        version = str(version_major) + "." + str(version_minor)
        return version

    def get_led(self, led):
        """Get led state.

        Args:
            led (int): Led number

        Returns:
            (int) Led state
        """
        self._check_channel("led", led)
        val = self._get_byte(I2C_MEM.LEDS)
        if (val & (1 << (led - 1))) != 0:
            return 1
        return 0
    def get_all_leds(self):
        """Get all leds state as bitmask.

        Returns:
            (int) Leds state bitmask
        """
        val = self._get_byte(I2C_MEM.LEDS)
        return val
    def set_led(self, led, val):
        """Set led state.

        Args:
            led (int): Led number
            val: 0(OFF) or 1(ON)
        """
        self._check_channel("led", led)
        if val == 0:
            self._set_byte(I2C_MEM.LED_CLR, led)
        elif val == 1:
            self._set_byte(I2C_MEM.LED_SET, led)
        else:
            raise ValueError("Invalid led value[0-1]")
    def set_all_leds(self, val):
        """Set all leds states as bitmask.

        Args:
            val (int): Leds bitmask
        """
        if(not (0 <= val and val <= (1 << CHANNEL_NO["leds"]) - 1)):
            raise ValueError("Invalid led mask!")
        self._set_byte(I2C_MEM.LEDS, 0xff & val)

    def get_u_in(self, channel):
        """Get 0-10V input channel value in volts.

        Args:
            channel (int): Channel number

        Returns:
            (float) Input value in volts
        """
        self._check_channel("u_in", channel)
        value = self._get_word(I2C_MEM.U_IN + (channel - 1) * 2)
        return value / data.VOLT_TO_MILIVOLT

    def get_r1k_in(self, channel):
        """Get 1k thermistor input channel value in ohms.

        Args:
            channel (int): Channel number

        Returns:
            (int) Input value in ohms
        """
        self._check_channel("r1k_in", channel)
        value = self._get_word(I2C_MEM.R1K_IN + (channel - 1) * 2)
        return value

    def get_r10k_in(self, channel):
        """Get 10k thermistor input channel value in ohms.

        Args:
            channel (int): Channel number

        Returns:
            (int) Input value in ohms
        """
        self._check_channel("r10k_in", channel)
        value = self._get_word(I2C_MEM.R10K_IN + (channel - 1) * 2)
        return value

    def wdt_reload(self):
        """Reload watchdog."""
        self._set_byte(I2C_MEM.WDT_RESET_ADD, data.WDT_RESET_SIGNATURE)
    def wdt_get_period(self):
        """Get watchdog period in seconds.

        Returns:
            (int) Watchdog period in seconds
        """
        return self._get_word(I2C_MEM.WDT_INTERVAL_GET_ADD)
    def wdt_set_period(self, period):
        """Set watchdog period.

        Args:
            period (int): Channel number
        """
        return self._set_word(I2C_MEM.WDT_INTERVAL_SET_ADD, period)
    def wdt_get_init_period(self):
        """Get watchdog initial period.

        Returns:
            (int) Initial watchdog period in seconds
        """
        return self._get_word(I2C_MEM.WDT_INIT_INTERVAL_GET_ADD)
    def wdt_set_init_period(self, period):
        """Set watchdog initial period.

        Args:
            period (int): Initial period in second
        """
        return self._set_word(I2C_MEM.WDT_INIT_INTERVAL_SET_ADD, period)

    def wdt_get_off_period(self):
        """Get watchdog off period in seconds.

        Returns:
            (int) Watchfog off period in seconds.
        """
        return self._get_i32(I2C_MEM.WDT_POWER_OFF_INTERVAL_GET_ADD)
    def wdt_set_off_period(self, period):
        """Set off period in seconds

        Args:
            period (int): Off period in seconds
        """
        return self._set_i32(I2C_MEM.WDT_POWER_OFF_INTERVAL_SET_ADD, period)
    def wdt_get_reset_count(self):
        """Get watchdog reset count.

        Returns:
            (int) Watchdog reset count
        """
        return self._get_word(I2C_MEM.WDT_RESET_COUNT_ADD)
    def wdt_clear_reset_count(self):
        """Clear watchdog counter. """
        return self._set_i32(I2C_MEM.WDT_CLEAR_RESET_COUNT_ADD, data.WDT_RESET_COUNT_SIGNATURE)

    def get_rtc(self):
        """Get rtc time.

        Returns:
            (tuple) date(year, month, day, hour, minute, second)
        """
        buf = self._get_block_data(I2C_MEM.RTC_YEAR_ADD, 6)
        buf[0] += 2000
        return tuple(buf)
    def set_rtc(self, year, month, day, hour, minute, second):
        """Set rtc time.

        Args:
            year (int): current year
            month (int): current month
            day (int): current day
            hour (int): current hour
            minute (int): current minute
            second (int): current second
        """
        if year > 2000:
            year -= 2000
        if(not(0 <= year and year <= 255)):
            raise ValueError("Invalid year!")
        datetime.datetime(
                year=2000+year, month=month, day=day,
                hour=hour, minute=minute, second=second)
        ba = bytearray(struct.pack(
            "6B B",
            year, month, day, hour, minute, second,
            data.CALIBRATION_KEY))
        self._set_block(I2C_MEM.RTC_SET_YEAR_ADD, ba)
        
    def get_dig_in(self, channel):
        """Get digital (dry contact) input status. 

        Args:
            channel (int): Channel number

        Returns:
            (bool) Channel status
        """
        self._check_channel("dig_in", channel)
        opto_mask = self._get_byte(I2C_MEM.DRY_CONTACT)
        if(opto_mask & (1 << (channel - 1))):
            return True
        else:
            return False
    def get_all_dig_in(self):
        """Get all digital (dry contact) input status as a bitmask.

        Returns:
            (int) Optocoupled bitmask
        """
        return self._get_word(I2C_MEM.DRY_CONTACT)
    def get_dig_in_cnt_en(self, channel):
        """Get digital (dry contact) input counting edges status.

        Args:
            channel (int): Channel number

        Returns:
            (int) Counting edge status
                0(disable)/1(enable)
        """
        self._check_channel("dig_in", channel)
        counting = self._get_word(I2C_MEM.CNT_ENABLE)
       
        channel_bit = 1 << (channel - 1)
        value = 0
        if(counting & channel_bit):
            value |= 1
        return value
    
    def set_dig_in_cnt_en(self, channel, value):
        """Set digital (dry contact) input channel counting edges status.

        Args:
            channel (int): Channel number
            value (int): Counting edge status
                0(disable)/1(enable)
        """
        self._check_channel("dig_in", channel)
        counting = self._get_word(I2C_MEM.CNT_ENABLE)
        channel_bit = 1 << (channel - 1)
        if(value & 1):
            counting |= channel_bit
        else:
            counting &= ~channel_bit
        self._set_word(I2C_MEM.CNT_ENABLE, counting)
        
    def get_dig_in_counter(self, channel):
        """Get digital (dry contact) inputs edges counter for one channel.

        Args:
            channel (int): Channel number

        Returns:
            (int) dry contact transitions counter
        """
        self._check_channel("dig_in", channel)
        return self._get_u32(I2C_MEM.DC_CNT_ADD + (channel - 1) * 4)
    def reset_dig_in_counter(self, channel):
        """Reset optocoupled inputs edges counter.

        Args:
            channel (int): Channel number
        """
        self._check_channel("dig_in", channel)
        return self._set_byte(I2C_MEM.DC_CNT_RST, channel)
  
    def get_button(self):
        """Get button status.

        Returns:
            (bool) status
                True(ON)/False(OFF)
        """
        state = self._get_byte(I2C_MEM.BUTTON)
        if(state & 1):
            return True
        else:
            return False
    def get_button_latch(self):
        """Get button latch status.

        Returns:
            (bool) status
                True(ON)/False(OFF)
        """
        state = self._get_byte(I2C_MEM.BUTTON)
        if(state & 2):
            state &= ~2
            self._set_byte(I2C_MEM.BUTTON, state)
            return True
        else:
            return False
