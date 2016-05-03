#! /bin/sh
#Pin 60
echo 60 > /sys/class/gpio/export
echo low > /sys/class/gpio/gpio60/direction
echo 0 > /sys/class/gpio/gpio60/value
chmod 666 /sys/class/gpio/gpio60/value
