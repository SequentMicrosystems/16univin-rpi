# update

This is the [Sequent Microsystems](https://www.sequentmicrosystems.com) Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi firmware update tool.

## Usage

```bash
~$ git clone https://github.com/SequentMicrosystems/16univin-rpi.git
~$ cd 16univin-rpi/update/
~/16univin-rpi/update$ ./update 0
```

If you clone the repository already, skip the first step. 
The command will download the newest firmware version from our server and burn it  to the board.
The stack level of the board must be provided as a parameter. 
Make sure no one (python scripts or sell scripts or node-red flow) tries to access the card during the update process.
During firmware update we strongly recommend to disconnect all outputs from the board since they can change state unpredictably.
