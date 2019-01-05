# ESP8266-based "real" multi camera remote control

![](https://i.imgur.com/ILdYBRm.jpg)

---

**Status:** Work in progress

ESP8266 based real Remote Control (RC mode, not APP mode) for GoPro HERO4+ cameras. Cameras tested are HERO4, HERO5, HERO7.

### Protocol:

GoPro cameras with WiFi functionality offer various connectivity modes: App or Access Point mode, Remote Control / Smart Remote / Station mode, Bluetooth Mode and REMO mode.

On App mode, the camera starts a Cherokee server internally that points to the SD card, starts the gpControl API on `10.5.5.9` and starts a password protected WiFi Access Point.

On devices with 1 NIC (Network Interface Card) connecting multiple cameras in App mode is impossible. 

The [GoPro Smart Remote](https://shop.gopro.com/accessories-3/smart-remote/ARMTE-002.html) broadcasts an Access Point, the camera(s) act as a client and connect to the Remote Access Point. This is what this project aims to replicate. 

ESP8266 based boards are inexpensive Arduino boards with an embedded WiFi Network Interface. The ESP8266 can be configured to broadcast a WiFi signal identical to a GoPro smart remote.

GoPro Smart Remote has an MAC Address of `D8:96:85:XX:XX:XX`, the WiFi AP must be an open network with the SSID: `HERO-RC-XXXXXX` (Last 6 characters of the MAC address).

The IP address of the Smart Remote WiFi AP is `10.71.79.1`.

### ESP8266 based Remote

[GoProRC.ino](GoProRC.ino) is a Proof of Concept of how to emulate a Smart Remote connection.

Tested on Wemos D1 mini and Lolin NodeMCU V3.

Load the code onto your ESP8266 board, on your camera go to Connections > New > Remote and wait for it to connect to the ESP8266.

The IP address will appear in the Serial Monitor.

### Todo list:

- [ ] Bind DCHP server so IP addresses can be reached
- [ ] Determine command structure and API^1 ^2 ^3
- [ ] Open port on :80 and host custom webapp and API for multi camera control

Sources:

- 1: https://github.com/KonradIT/gopro-py-api/pull/27
- 2: https://github.com/KonradIT/goprowifihack/issues/78
- 3: https://github.com/vmayoral/GoProController/blob/master/Infrastructure%20Wifi%20Research.md
