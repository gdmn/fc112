#! /usr/bin/env bash

set -e
export SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
echo $SCRIPT_DIR
rm -rf "${SCRIPT_DIR}/hex" || true
mkdir -p "${SCRIPT_DIR}/hex"
UI=fc112

for TARGET in cfg-*.h ; do
  NAME=$(echo "$TARGET" | perl -ne '/cfg-(.*).h/ && print "$1\n";')
  echo "===== $NAME ====="
  ATTINY=$(grep 'ATTINY:' $TARGET | awk '{ print $3 }')
  if [ -z "$ATTINY" ]; then ATTINY=85 ; fi
  echo ../../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"
  ../../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"
  mv -f "$UI".hex "${SCRIPT_DIR}/hex/$UI".$NAME.hex
done

rm -f fc112.elf fc112.o
