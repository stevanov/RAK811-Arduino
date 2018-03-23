# RAK811-Arduino
Arduino library for RakWireless RAK811

http://www.rakwireless.com/en/
http://www.rakwireless.com/en/module/lora/RAK811

## As of yet, this does not work

This is my attempt to write a Library for Rak811 Arduino shields. NOT the built in SMT microcontroller that is in the Rak811 can.
The Arduino library that RakWireless provides is very simple and does not even work. Hence this attempt
If you want to contribute, please do! Or if you have a working library for the RAK811, please let me know.
The sketch that is used here is still a single file and not yet a library, but it is intended to be one at some point. I do my testing and developing with an official RAK811 shield on top of a official arduino mega. The code reflects that.


Right now there seems to be a bug concerning the sending and receiving of commands. I would like to make the Arduino sort of be aware of the state that the RAK811 is in by waiting for a reponse and it being correct before moving on to the next command, as of right now that does not seem to work. Sometimes the Arduino has to send at+version about 10 times before it gets the proper response. And even then, all subsequent commands do not go over smooth. Every command and every response is trailed by (http://support.rakwireless.com/topic/188/why-send-at-command-device-not-respones) and as far as i know the code i have right now reflects that, but no dice.
Any input would be greatly appreciated!
