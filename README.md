ESP8266-automation
==

Code and circuitry to support simple event driven signaling from remote sensors (ESP8266) to a server (BeagleBone)

The remote sensors use an ESP8266-01 plus the PCB defined under the eagle directory. You can order the PCB from [oshpark directly](https://www.oshpark.com/shared_projects/7gWfLivJ) Use 3xAA batteries as the power supply and any convenient switch as the switch. A simple mercury switch is good. To extend battery life you can desolder the red LED on the ESP8266 board. It is better to use [4pin Female Single Row Straight Headers](http://www.aliexpress.com/item/50-pcs-4P-4pin-Female-Single-Row-Straight-Header-Strip-Socket-Connector-Pitch-2-54mm/32442780670.html) rather than solder the ESP8266 board to the PCB directly so you can detach it and reflash.

There are two images to flash to the ESP8266. They both do the following:

 * Detect when GPIO0 grounded and send a message to the server with an event.
 * Detect when the voltage falls below 3v and send a battery status message.
 * Send a battery status message on startup.
 
The server is a Beaglebone running Nginx with some PHP scripts. The difference between the two images is that the GPIO0 ground message is slightly different and invokes a different script. One tells the server to just log, the other (Mailbox) tells the server to sound a chime as well.

To compile the two flash images you need to have the Arduino environment installed. Then you need to edit the file local_network.h to include your own settings and copy it to:

`~/.arduino15/packages/esp8266/hardware/esp8266/2.0.0/tools/sdk/include`

For details on flashing the ESP8266 from an Arduino environment see [this link](http://iot-playground.com/blog/2-uncategorised/38-esp8266-and-arduino-ide-blink-example).

To set up the BeagleBone just install [Nginx](https://www.nginx.com/resources/wiki/start/topics/tutorials/install/#) and copy the php scripts into `/usr/share/nginx/www`

If you want to use the chime then you need to wire up the BeagleBone like this:

![BeagleBone chime](BeagleBone/SirenFritz.png)

And arrange for the `BeagleBone/startup/gpio60.sh` script to run at startup.

Also create a file `/home/receiver/log.csv` and use chmod to make it writeable from anyone. This is the log file and it can be viewed by browsing to `<your BeagleBone>/printlog.php`. You should see something like this:

![Sample log](log-image.png)

This shows mostly battery levels logged at startup, but the send entry shows the value in red, indicating it has dropped below 3000. The last entry is an actual event on the mailbox and was used to test the chime.

To get the log showing the right names for the devices you need to edit the printlog.php file. Specifically this line:

`$sources = array("test" => "123","pond" => "16058556","backdoor" => "8442031", "mailbox" => "8425573");`

The values it is mapping against are the unique id of each ESP8266 obtained from the `ESP.getChipId()` call. If there is no mapping value the unmapped value appears in the log.

To log the time properly you must ensure the BeagleBone's clock is set correctly. there is help on how to do this [here](http://derekmolloy.ie/automatically-setting-the-beaglebone-black-time-using-ntp/) however I had to use usr/sbin/ntp rather than usr/bin/ntp on my system.