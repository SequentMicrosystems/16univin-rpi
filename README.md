[![16univin-rpi](res/sequent.jpg)](https://sequentmicrosystems.com)
# 16univin-rpi
Drivers for Sequent Microsystems [Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi) 

![MEGA-IND](res/16-univ.webp)

## Setup

Enable I2C communication first:
```bash
sudo raspi-config
```
A good article about I2C on Raspberry can be found [here](https://www.raspberrypi-spy.co.uk/2014/11/enabling-the-i2c-interface-on-the-raspberry-pi/).

If you use Ubuntu you need to install `raspi-config` first:
```bash
sudo apt update
sudo apt install raspi-config
```

Make sure you have all tools you need:
```bash
sudo apt update
sudo apt-get install git build-essential
```

## Usage

Install the command:
```bash
git clone https://github.com/SequentMicrosystems/16univin-rpi.git
cd 16univin-rpi/
sudo make install
```

Now you can access all the functions of the [card](https://sequentmicrosystems.com/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi) through the command "16univin". Use -h option for help:
```bash
16univin -h
```

If you clone the repository any update can be made with the following commands:
```bash
cd 16univin-rpi/  
git pull
sudo make install
```


