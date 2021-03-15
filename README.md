FC112 FSM UI
============

FC112 UI manual: [/gdmn/fc112/tree/fc112/ToyKeeper/spaghetti-monster/fc112/fc112-manual.md](https://github.com/gdmn/fc112/tree/fc112/ToyKeeper/spaghetti-monster/fc112/fc112-manual.md)

HEX files to download: [/gdmn/fc112/tree/fc112/ToyKeeper/spaghetti-monster/fc112/hex](https://github.com/gdmn/fc112/tree/fc112/ToyKeeper/spaghetti-monster/fc112/hex)

UI dev thread: [budgetlightforum.com/node/75951](https://budgetlightforum.com/node/75951)

Source: [flashlight-firmware/anduril2/revision/583](https://bazaar.launchpad.net/~toykeeper/flashlight-firmware/anduril2/revision/583)

The rest of original README file is below.

ToyKeeper's flashlight firmware repository
==========================================

This is a collection of firmware for flashlights or torches, mostly
collected from BLF (http://budgetlightforum.com/).  It's collected
here mostly for convenience, and to provide bug tracking and revision
control services for the code.

See the INDEX file to find out which projects might be relevant to
your needs.


Getting Started
===============

The central firmware thread on BLF is here:

  http://budgetlightforum.com/node/38364

A general overview of what you need to get going is here:

  http://flashlightwiki.com/AVR_Drivers

Some useful hardware for flashing firmware:

  What TK uses:

    http://www.fasttech.com/product/1002900-atmega-attiny-51-avr-isp-usbasp-usb-programmer
    http://www.fasttech.com/product/1011800-40-pin-splittable-ribbon-cable-20cm
    http://www.digikey.com/product-detail/en/5250/501-1311-ND/745102
    HQ ProgKey: http://budgetlightforum.com/node/63230

  Ratus' guide:  https://redd.it/8g5l5w  (prices checked 2018-05-01)

    Store A: About $4.20 shipped
      https://www.aliexpress.com/item/USB-ISP-Programmer-for-ATMEL-AVR-ATMega-ATTiny-51-AVR-Board-ISP-Downloader/32699341177.html
      https://www.aliexpress.com/item/WAVGAT-Programmer-Testing-Clip-SOP8-SOP-SOIC-8-SOIC8-DIP8-DIP-8-Pin-IC-Test-Clamp/32827794024.html
      https://www.aliexpress.com/item/40Pin-20CM-2-54MM-Row-Female-to-Female-F-F-Dupont-Cable-Breadboard-Jumper-Wire-for/32822958653.html

    Store B: About $4.18 shipped:
      https://www.aliexpress.com/store/product/1pcs-New-USBASP-USBISP-AVR-Programmer-USB-ISP-USB-ASP-ATMEGA8-ATMEGA128-Support-Win7-64K/1171090_32809542958.html
      https://www.aliexpress.com/store/product/Free-shipping-Programmer-Testing-Clip-SOP8-SOP-SOIC-8-SOIC8-DIP8-DIP-8-Pin-IC-Test/1171090_32402561848.html
      https://www.aliexpress.com/store/product/20pcs-20cm-2-54mm-1p-1p-Pin-Female-to-Female-Color-Breadboard-Cable-Jump-Wire-Jumper/1171090_32628811461.html

For Windows / MacOS users, these links may be useful:

  Oweban's guides:  (Windows 10, MacOS X) (not generic, focuses on Anduril)

    http://budgetlightforum.com/node/73487

  Hoop's guide:

    http://budgetlightforum.com/node/36216

  Comfychair's guide:

    http://budgetlightforum.com/node/29081

  WarHawk-AVG's guide:

    http://budgetlightforum.com/node/29684

  Getting a USBasp to work in Windows:

    http://rayshobby.net/dead-simple-driver-installation-for-usbasp-and-usbtiny-on-windows/
    http://www.protostack.com/accessories/usbasp-avr-programmer

To set up an attiny dev environment on Ubuntu (13.10):

  sudo apt-get install flex byacc bison gcc libusb-dev libc6-dev
  sudo apt-get install gcc-avr avr-libc binutils-avr
  sudo apt-get install avrdude avrdude-doc

  Optional:  (make avrdude usable by non-root users, is a security risk)
  sudo chmod u+s $(which avrdude)

To set up an attiny dev environment on Fedora (30):

  sudo dnf install flex byacc bison gcc libusb libusb-devel glibc-devel
  sudo dnf install avr-gcc avr-libc avr-binutils
  sudo dnf install avrdude

Building/installing attiny dev tools on other UNIX systems (in general):

  http://www.ladyada.net/learn/avr/setup-unix.html

After wiring everything up, this tests the connection to the ATTINY13A chip:

  avrdude -p t13 -c usbasp -n
  (you may need to put 'sudo' in front, on UNIX systems...
  or set the suid bit on the avrdude binary, which is convenient but a
  potential security risk)

To test if you can flash firmware correctly, or to restore a light to something
like a default state, try flashing the NLITE driver from DrJones.  It's similar
to the default nanjg / qlite firmware, but better.

  ./bin/flash-tiny13.sh DrJones/NLITE/nlite.hex

For a quick test to make sure your tool chain works and your flashing tools
are working, try the 'hello world' program:

  cd hello_world
  make
  make flash

If that works, you should be ready to start making changes to the code, or
flashing any of the pre-built firmwares.

Most projects can be compiled with the bin/build.sh script.  For example, to
build Crescendo for an attiny25-based driver and then flash it:

  cd ToyKeeper/crescendo
  ../../bin/build.sh 25 crescendo
  ../../bin/flash-tiny25.sh crescendo.hex

Other useful tools are in bin/ too, so they might be worth a look.
