# Data Acquisition Dashboard 

This is a data acquisition dashboard example created in Node-RED with Sequent Microsystems [Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi?variant=44857261523196)

## I) Initial setup
### 1) Node-RED
* Install NodeRed with the following command:
```bash
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

* If you want Node-RED to run when the Pi is turned on, or re-booted, you can enable the service to autostart by running the command:
```bash
sudo systemctl enable nodered.service
```

* To disable the service, run the command:
```bash
sudo systemctl disable nodered.service
```

* Connect up to 8 [Sixteen Analog/Digital Inputs Cards](https://sequentmicrosystems.com/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi?variant=44857261523196) to your raspberry, each with different stack level jumper settings.  

* Install the necessary nodes by opening the Node-RED interface in a browser: Go to Menu > Manage pallete > Install and search for the following nodes:
```bash
node-red-contrib-fs
node-red-dashboard
node-red-node-ui-table
node-red-contrib-influxdb

```


### 2) InfluxDB
* Install InfluxDB using the following commands:
```bash
sudo apt update
sudo apt upgrade
curl https://repos.influxdata.com/influxdata-archive.key | gpg --dearmor | sudo tee /usr/share/keyrings/influxdb-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/influxdb-archive-keyring.gpg] https://repos.influxdata.com/debian stable main" | sudo tee /etc/apt/sources.list.d/influxdb.list
sudo apt update
sudo apt install influxdb
sudo systemctl unmask influxdb
sudo systemctl enable influxdb
sudo systemctl start influxdb
```

* Enter inside the InfluxDB server using the following command:
```bash
influx
```

* Create the database inside the InfluxDB server using the following command:
```bash
> create database database_influx
```

### 3) Grafana

* Install docker on your Raspberry Pi using the following commands:
```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo usermod -aG docker pi
sudo apt install -y libffi-dev libssl-dev python3 python3-pip
```

* You can verify that Docker was installed correctly:
```bash
docker --version
```

* Create a Grafana docker container using the following command:
```bash
docker run -d --name=grafana -p 3000:3000 grafana/grafana-enterprise:10.4.0-ubuntu
```

* You can check if the container was successfully created:
```docker ps``` or ```docker container ls```

## II) Importing and configuring the Node-RED flow

* Import the Data Acquisition Dashboard flow: Go to Menu > Import > select a file to import. Load the provided [flows.json](https://github.com/SequentMicrosystems/16univin-rpi/blob/main/node-red/DataAquisitionDashboard/flows.json) file and click the Import button.
![import](Pic/Import1.jpg)

* Click on the top right ```Deploy``` button.

* Configure all InfluxDB nodes inside Node-RED with the IP address of your Raspberry Pi and port ```8086``` then click again the ```Deploy``` button.

## III) Dashboard functionality
* TODO

## IV) Integration with Grafana
* TODO
