# AltWallet

Bitcoin cryptocurrency cold wallet with Arduino

Roni Bandini, Buenos Aires, Argentina. May 2022

CC Attribution Int. License 

# Demo 

https://www.youtube.com/watch?v=slu2VULd6mk

# 3d parts 

https://www.thingiverse.com/thing:5387126

# Instructions 

https://wikimakes.com/

# Spanish info 

# Python Alt Loader script

This script requires a Raspberry Pi with Python 2.7

Then you have to install dependencies

sudo apt-get install python-pip
sudo apt-get install python-picamera
sudo pip install qrtools
sudo apt-get install python-zbar
sudo apt-get install python-pillow

# Arduino CLI for Raspberry

Only required if you are going to use the Alt Loader with a Raspberry PI in command line mode. You can also use the Desktop IDE version (easier)

Go to home, then run

$ curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

Create config file

$ arduino-cli config init

Connect the Altoids Wallet 

$ arduino-cli core update-index

Search the board

$ arduino-cli board list

Install Arduino Micro Board

$ arduino-cli core install arduino:avr

Adding library 

$ arduino-cli lib install "ButtonFever"
$ arduino-cli lib install "Nokia 5110 LCD library"

Compile 

$ arduino-cli compile --fbqn arduino:avr:micro wallet6 

Flash 

$ arduino-cli upload -p /dev/ttyACM0 --fbqn arduino:avr:micro wallet6 -v

# Spanish info

https://bandini.medium.com/alt-oids-wallet-billetera-de-bitcoin-curiosamente-fuerte-f20d56cc21e4

Like the project? You are welcome to use the QR code for BTC donations. Latest version will be sent to all donors. 

Contact 
Instagram https://www.instagram.com/ronibandini/
Twitter https://twitter.com/RoniBandini


