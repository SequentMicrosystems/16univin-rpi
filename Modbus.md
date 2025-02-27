[![16univin-rpi](res/sequent.jpg)](https://sequentmicrosystems.com)

# Sixteen Universal Inputs Modbus Registers Map

The [Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi) can be accessed thru Modbus RTU protocol over RS-485 port.
You can set-up the RS-485 port with **16univin** command.

Example:
```bash
~$ 16univin 0 rs485wr 1 9600 1 0 1
```
Set Modbus RTU , Baudrate: 9600bps, 1 Stop Bit,  parity: None, slave address offset: 1
```bash
~$ 16univin -h rs485wr
```
display the full set of options

## Slave Address
The slave address is add with the "stack level" jumpers. For example the jumpers configuration for stack level 1  (one jumper in position ID0) slave address offset to 1 corespond to slave address 2.

## Modbus object types
All modbus RTU object type with standard addresses are implemented : Coils, Discrete Inputs, Input registers, Holding registers.

### Coils

Acces level Read/Write, Size 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |

### Discrete Inputs

Access level Read Only, Size 1 bit

| Device function | Register Address | Modbus Address |
| --- | --- | --- |
| DRY_CONTACT_1 | 10001 | 0x00 |
| DRY_CONTACT_2 | 10002 | 0x01 |
| DRY_CONTACT_3 | 10003 | 0x02 |
| DRY_CONTACT_4 | 10004 | 0x03 |
| DRY_CONTACT_5 | 10005 | 0x04 |
| DRY_CONTACT_6 | 10006 | 0x05 |
| DRY_CONTACT_7 | 10007 | 0x06 |
| DRY_CONTACT_8 | 10008 | 0x07 |
| DRY_CONTACT_9 | 10009 | 0x08 |
| DRY_CONTACT_10 | 10010 | 0x09 |
| DRY_CONTACT_11 | 10011 | 0x0A |
| DRY_CONTACT_12 | 10012 | 0x0B |
| DRY_CONTACT_13 | 10013 | 0x0C |
| DRY_CONTACT_14 | 10014 | 0x0D |
| DRY_CONTACT_15 | 10015 | 0x0E |
| DRY_CONTACT_16 | 10016 | 0x0F |

### Input registers

Access level Read Only, Size 16 bits

| Device function | Register Address | Description | Measurement Unit |
| --- | --- | --- | --- |
| 0-10V_IN_1 | 30001 | 0 - 10V input channel 1 | mV |
| 0-10V_IN_2 | 30002 | 0 - 10V input channel 2 | mV |
| 0-10V_IN_3 | 30003 | 0 - 10V input channel 3 | mV |
| 0-10V_IN_4 | 30004 | 0 - 10V input channel 4 | mV |
| 0-10V_IN_5 | 30005 | 0 - 10V input channel 5 | mV |
| 0-10V_IN_6 | 30006 | 0 - 10V input channel 6 | mV |
| 0-10V_IN_7 | 30007 | 0 - 10V input channel 7 | mV |
| 0-10V_IN_8 | 30008 | 0 - 10V input channel 8 | mV |
| 0-10V_IN_1 | 30009 | 0 - 10V input channel 9 | mV |
| 0-10V_IN_2 | 30010 | 0 - 10V input channel 10 | mV |
| 0-10V_IN_3 | 30011 | 0 - 10V input channel 11 | mV |
| 0-10V_IN_4 | 30012 | 0 - 10V input channel 12 | mV |
| 0-10V_IN_5 | 30013 | 0 - 10V input channel 13 | mV |
| 0-10V_IN_6 | 30014 | 0 - 10V input channel 14 | mV |
| 0-10V_IN_7 | 30015 | 0 - 10V input channel 15 | mV |
| 0-10V_IN_8 | 30016 | 0 - 10V input channel 16 | mV |
| 1K_R_IN_1 | 30017 | 1K thernistor resistance channel 1 | ohm |
| 1K_R_IN_2 | 30018 | 1K thernistor resistance channel 2 | ohm |
| 1K_R_IN_3 | 30019 | 1K thernistor resistance channel 3 | ohm |
| 1K_R_IN_4 | 30020 | 1K thernistor resistance channel 4 | ohm |
| 1K_R_IN_5 | 30021 | 1K thernistor resistance channel 5 | ohm |
| 1K_R_IN_6 | 30022 | 1K thernistor resistance channel 6 | ohm |
| 1K_R_IN_7 | 30023 | 1K thernistor resistance channel 7 | ohm |
| 1K_R_IN_8 | 30024 | 1K thernistor resistance channel 8 | ohm |
| 1K_R_IN_1 | 30025 | 1K thernistor resistance channel 9 | ohm |
| 1K_R_IN_2 | 30026 | 1K thernistor resistance channel 10 | ohm |
| 1K_R_IN_3 | 30027 | 1K thernistor resistance channel 11 | ohm |
| 1K_R_IN_4 | 30028 | 1K thernistor resistance channel 12 | ohm |
| 1K_R_IN_5 | 30029 | 1K thernistor resistance channel 13 | ohm |
| 1K_R_IN_6 | 30030 | 1K thernistor resistance channel 14 | ohm |
| 1K_R_IN_7 | 30031 | 1K thernistor resistance channel 15 | ohm |
| 1K_R_IN_8 | 30032 | 1K thernistor resistance channel 16 | ohm |
| 10K_R_IN_1 | 30033 | 10K thernistor resistance channel 1 | ohm |
| 10K_R_IN_2 | 30034 | 10K thernistor resistance channel 2 | ohm |
| 10K_R_IN_3 | 30035 | 10K thernistor resistance channel 3 | ohm |
| 10K_R_IN_4 | 30036 | 10K thernistor resistance channel 4 | ohm |
| 10K_R_IN_5 | 30037 | 10K thernistor resistance channel 5 | ohm |
| 10K_R_IN_6 | 30038 | 10K thernistor resistance channel 6 | ohm |
| 10K_R_IN_7 | 30039 | 10K thernistor resistance channel 7 | ohm |
| 10K_R_IN_8 | 30040 | 10K thernistor resistance channel 8 | ohm |
| 10K_R_IN_1 | 30041 | 10K thernistor resistance channel 9 | ohm |
| 10K_R_IN_2 | 30042 | 10K thernistor resistance channel 10 | ohm |
| 10K_R_IN_3 | 30043 | 10K thernistor resistance channel 11 | ohm |
| 10K_R_IN_4 | 30044 | 10K thernistor resistance channel 12 | ohm |
| 10K_R_IN_5 | 30045 | 10K thernistor resistance channel 13 | ohm |
| 10K_R_IN_6 | 30046 | 10K thernistor resistance channel 14 | ohm |
| 10K_R_IN_7 | 30047 | 10K thernistor resistance channel 15 | ohm |
| 10K_R_IN_8 | 30048 | 10K thernistor resistance channel 16 | ohm |

### Holding registers

Access level Read/Write, Size 16 bits

| Device function | Register Address | Modbus Address | Measurement Unit |
| --- | --- | --- | --- |



## Function codes implemented

* Read Coils (0x01)
* Read Discrete Inputs (0x02)
* Read Holding Registers (0x03)
* Read Input Registers (0x04)
* Write Single Coil (0x05)
* Write Single Register (0x06)
* Write Multiple Coils (0x0f)
* Write Multiple registers (0x10)


