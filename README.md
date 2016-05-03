# ESP8266-automation

Code and circuitry to support simple event driven signaling from remote sensors (ESP8266) to a server (BeagleBone)

The remote sensors use an ESP8266-01 plus the PCB defined under the eagle directory. You can ord the PCB from oshpark directly: ... Use 3xAA batteries as the power supply and any convenient switch as the switch. A simple mercury switch is good.

Flash the ESP8266 with either the PossumTrap or MailBox code. Mailbox sounds the siren. But you will have to edit the code to add your own network info and for each remote you want to assign a unique id.

The server end is a BeagleBone with Nginx running. I've provided the scripts the remotes call.

The remotes report when their battery level is getting low. Otherwise they just log the event and optionally sound the siren.
