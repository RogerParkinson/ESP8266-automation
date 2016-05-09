ESP8266-automation
==

Code and circuitry to support simple event driven signaling from remote sensors (ESP8266) to a server (BeagleBone). The remote sensors detect an n/c switch being closed and they send a message to the server which decides what to do with it. Normally it logs it and there is a web page to query the log. But for some messages it will sound a chime. The remote sensors also send a battery status every 24 hours.

The remote sensors use an ESP8266-01. Use 2xAA batteries as the power supply and any convenient switch as the switch. A simple mercury switch is good. A 3xAA battery case be slightly modified to hold just two AA batteries plus the ESP8266. 

Wiring is very simple:

![Remote Sensor Wiring](wiring.png)

This can be easily done soldering the components directly to the ESP8266 terminals. You do not need a PCB or perfboard support. There is one tricky part and that is the connection to XPD (or GPIO16) which is a tiny contact on the side of the chip, not an exposed pin unfortunately. [This page will show you where it is](http://tim.jagenberg.info/2015/01/18/low-power-esp8266/). It is probably worth prying off the red LED on the ESP8266 board too because that uses up battery unnecessarily.

Flash the RemoteSwitch image tothe ESP8266. To compile it you need to have the Arduino environment installed. Then you need to edit the file local_network.h to include your own settings and copy it to:

`~/.arduino15/packages/esp8266/hardware/esp8266/2.0.0/tools/sdk/include`

For details on flashing the ESP8266 from an Arduino environment see [this link](http://iot-playground.com/blog/2-uncategorised/38-esp8266-and-arduino-ide-blink-example).
 
The server is a Beaglebone running Nginx with some PHP scripts.

To set up the BeagleBone just install [Nginx](https://www.nginx.com/resources/wiki/start/topics/tutorials/install/#) and copy the php scripts into `/usr/share/nginx/www`

If you want to use the chime then you need to wire up the BeagleBone like this:

![BeagleBone chime](BeagleBone/SirenFritz.png)

And arrange for the `BeagleBone/startup/gpio60.sh` script to run at startup.

Also create a file `/home/receiver/log.csv` and use chmod to make it writeable from anyone. This is the log file and it can be viewed by browsing to `http://<your BeagleBone>/printlog.php`. You should see something like this:

![Sample log](log-image.png)

This shows mostly battery levels logged at startup, but the send entry shows the value in red, indicating it has dropped below 3000. The last entry is an actual event on the mailbox and was used to test the chime.

To get the log showing the right names for the devices you need to edit the printlog.php file. Specifically this line:

`$sources = array("test" => "123","pond" => "16058556","backdoor" => "8442031", "mailbox" => "8425573");`

The values it is mapping against are the unique id of each ESP8266 obtained from the `ESP.getChipId()` call. If there is no mapping value the unmapped value appears in the log.

The same thing appears in the processevent.php file where the message source name is used to decide hether to sound the chime or not. You can customise this as needed.

To log the time properly you must ensure the BeagleBone's clock is set correctly. there is help on how to do this [here](http://derekmolloy.ie/automatically-setting-the-beaglebone-black-time-using-ntp/) however I had to use usr/sbin/ntp rather than usr/bin/ntp on my system.