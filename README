Installation
=

**Download required libraries:**

 - [ESP8266wifi](https://github.com/ekstrand/ESP8266wifi) for server.
 - *(Optionally, )* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) for JSON responses.
 - [IRremoteESP8266](https://github.com/markszabo/IRremoteESP8266) for IR transmission.

---

Configuration
=

**Create `WiFi.h` with login information.**

```
$ cp WiFi.h.bak WiFi.h
$ vi WiFi.h
```

**Modify IR functionality.**

 - Change `IRsend irsend(4);` to the corresponding port of your IR transmitter.
 - Use an IR receiver to get HEX values (and their corresponding number of bits) for `void transmitIR()`.

---

Use
=

 - Flash to your board.
 - Use the serial monitor to detect board's IP address.
 - `POST` commands to `http://[ipaddress]/tv`.
