# home-temp-sensor
IoT device that reads temperature and humidity and sends their values to a HomeManager server.

## How does it works
The device connects to the network and registers itself to a HomeManager server.
Its main task is to sense temperature and humidity and store those values in the HomeManager server.

If it can't register, it starts sensing data anyway without publishing them to the server and periodically tries to register again.

Registration to a HomeManager server produces an ID for the device. This ID is used for further interaction with the server.

## Device

The device is an ESP8266ex board connected to a DHT11.

## TODO
- Add wiring scheme
- Integrate MQTT
