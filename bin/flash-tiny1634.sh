#/bin/sh
FIRMWARE=$1
while ! avrdude -c usbasp -p t1634; do sleep 1; done
avrdude -c usbasp -p t1634 -u -Uflash:w:$FIRMWARE
