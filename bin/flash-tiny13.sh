#/bin/sh
FIRMWARE=$1
while ! avrdude -c usbasp -p t13; do sleep 1; done
avrdude -c usbasp -p t13 -u -Uflash:w:$FIRMWARE
