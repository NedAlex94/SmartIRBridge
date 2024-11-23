# SmartIRBridge

### Problem
I have an old Denon (1908) receiver that still havs great sound for my ears, but it does not play well with my modern LG OLED TV. For instance, I want to control the volume of the Denon AVR with an LG Magic Remote, but that only works for me when connected through optical cable (and, even then, with a delay). However, my TV is connected to the Denon through an HDMI eARC Audio Extractor & Splitter and, through this setup, the Magic Remote refuses to control the volume on the Denon even though the LG's Universal Control Feature say it does.

Additionally, I would like to use the unused Magic Remote buttons, which are many, to control other things in the living room (e.g., Govee lights), but the Magic Remote cannot be mapped directly unless you root the TV.

### Concept
This repo contains ESP32 firmware that continuously listens to IR commands from the Magic Remote and sends them as MQTT messages over WiFi. This can be then configured so that any home automation ecosystem (Home Assistant in my case) can listen for these MQTT messages, allowing to build various automations regardless of remote.


### Solution
SmartIRBridge uses an ESP32 to:
1. Intercept IR signals from the LG Magic Remote.
2. Convert these signals into MQTT commands over WiFi.
   
Example use case:
- Pressing **Volume Up** on the Magic Remote sends a command to MQTT.
- HA listens to the MQTT topic, interprets the command, and uses a separate IR transmitter (I use a Broadlink RM4 on the other side of the room to send commands only) to increase the Denon AVR’s volume.
- Controlling other devices like Govee lights for turning them on or off using the Magic Remote.

### License
MIT License
