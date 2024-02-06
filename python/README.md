# Welcome to  lib16univin’s documentation!

# Install

```bash
sudo pip install SM16univin
```

or

```bash
sudo pip3 install SM16univin
```

# Update

```bash
sudo pip install SM16univin -U
```

or

```bash
sudo pip3 install SM16univin -U
```

# Initiate class

```console
$ python
Python 3.9.2 (default, Feb 28 2021, 17:03:44)
[GCC 10.2.1 20210110] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import lib16univin
>>> card = lib16univin.SM16univin()
>>> card.get_version()
>>>
```

# Documentation

### *class* lib16univin.SM16univin(stack=0, i2c=1)

Bases: `object`

Python class to control the 16 Universal Analog Inputs Card for Raspberry Pi.

* **Parameters:**
  * **stack** (*int*) – Stack level/device number.
  * **i2c** (*int*) – i2c bus number

#### get_all_dig_in()

Get all digital (dry contact) input status as a bitmask.

* **Returns:**
  (int) Optocoupled bitmask

#### get_all_leds()

Get all leds state as bitmask.

* **Returns:**
  (int) Leds state bitmask

#### get_button()

Get button status.

* **Returns:**
  (bool) status
  : True(ON)/False(OFF)

#### get_button_latch()

Get button latch status.

* **Returns:**
  (bool) status
  : True(ON)/False(OFF)

#### get_dig_in(channel)

Get digital (dry contact) input status.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (bool) Channel status

#### get_dig_in_cnt_en(channel)

Get digital (dry contact) input counting edges status.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (int) Counting edge status
  : 0(disable)/1(enable)

#### get_dig_in_counter(channel)

Get digital (dry contact) inputs edges counter for one channel.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (int) dry contact transitions counter

#### get_led(led)

Get led state.

* **Parameters:**
  **led** (*int*) – Led number
* **Returns:**
  (int) Led state

#### get_r10k_in(channel)

Get 10k thermistor input channel value in ohms.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (int) Input value in ohms

#### get_r1k_in(channel)

Get 1k thermistor input channel value in ohms.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (int) Input value in ohms

#### get_rtc()

Get rtc time.

* **Returns:**
  (tuple) date(year, month, day, hour, minute, second)

#### get_u_in(channel)

Get 0-10V input channel value in volts.

* **Parameters:**
  **channel** (*int*) – Channel number
* **Returns:**
  (float) Input value in volts

#### get_version()

Get firmware version.

Returns: (int) Firmware version number

#### reset_dig_in_counter(channel)

Reset optocoupled inputs edges counter.

* **Parameters:**
  **channel** (*int*) – Channel number

#### set_all_leds(val)

Set all leds states as bitmask.

* **Parameters:**
  **val** (*int*) – Leds bitmask

#### set_dig_in_cnt_en(channel, value)

Set digital (dry contact) input channel counting edges status.

* **Parameters:**
  * **channel** (*int*) – Channel number
  * **value** (*int*) – Counting edge status
    0(disable)/1(enable)

#### set_led(led, val)

Set led state.

* **Parameters:**
  * **led** (*int*) – Led number
  * **val** – 0(OFF) or 1(ON)

#### set_rtc(year, month, day, hour, minute, second)

Set rtc time.

* **Parameters:**
  * **year** (*int*) – current year
  * **month** (*int*) – current month
  * **day** (*int*) – current day
  * **hour** (*int*) – current hour
  * **minute** (*int*) – current minute
  * **second** (*int*) – current second

#### wdt_clear_reset_count()

Clear watchdog counter.

#### wdt_get_init_period()

Get watchdog initial period.

* **Returns:**
  (int) Initial watchdog period in seconds

#### wdt_get_off_period()

Get watchdog off period in seconds.

* **Returns:**
  (int) Watchfog off period in seconds.

#### wdt_get_period()

Get watchdog period in seconds.

* **Returns:**
  (int) Watchdog period in seconds

#### wdt_get_reset_count()

Get watchdog reset count.

* **Returns:**
  (int) Watchdog reset count

#### wdt_reload()

Reload watchdog.

#### wdt_set_init_period(period)

Set watchdog initial period.

* **Parameters:**
  **period** (*int*) – Initial period in second

#### wdt_set_off_period(period)

Set off period in seconds

* **Parameters:**
  **period** (*int*) – Off period in seconds

#### wdt_set_period(period)

Set watchdog period.

* **Parameters:**
  **period** (*int*) – Channel number

<!-- vi:se ts=4 sw=4 et: -->
