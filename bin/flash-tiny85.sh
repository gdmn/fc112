#/bin/sh
FIRMWARE=$1
while ! avrdude -c usbasp -p t85; do sleep 1; done
avrdude -c usbasp -p t85 -u -Uflash:w:$FIRMWARE
