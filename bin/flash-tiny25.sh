#/bin/sh
FIRMWARE=$1
while ! avrdude -c usbasp -p t25; do sleep 1; done
avrdude -c usbasp -p t25 -u -Uflash:w:$FIRMWARE
