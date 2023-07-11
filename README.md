# beehive-sensor
A temperature and humidity sensor, embedded in a beehive using an Arduino UNO and a SIM900A module.
The sensor is powered by a 9V battery, it reads data from the DHT11 sensor every 8hours and sends it to a ThingSpeak server,
via the ThingSpeak API.

## Pros
- It sends data as expected if there is a signal connection

## Limitations
- Needs a case, and better wire connections, had trouble with loose wires
- Battery Life is short
- Doesn't recover if no signal
- If there is no signal the data is lost

## Diagram
![image](https://github.com/RockyDesigne/beehive-sensor/assets/107836920/5fa4eedb-801c-4d40-bbf9-446a5fb627e6)


