# atmega328p_drivers
This is a repo for learning to write drivers in C for an Atmega328p.

Reading the value from an analog sensor in to atmega328p, 
converting analog value to uart/serial-data sending to an RPI or,
any reciever that can read UART,
perhaps an atmega328p.

We can keep this a bit open in the beginning wich type of analog-sensors and what the recieving end should look like, 
but then we need to write drivers for ADC also and then 
drivers for UART-output and perhaps
UART-input depending on what we want on the recieving end,
if we go for RPI as a reciever, the RPI could read UART and send wirelessly(bluetooth serial?) to a phone
or just the terminal, or perhaps a display.

This project-description is open for interpretation and as the project progress it will become more clear 
what direction it should take.

A good start could be to start with drivers for the ADC.

We can list different type of configurations here in the git-repo and schematic overviews, pictures etc.

AN ORGANIZED LIST OF PROJECT OBJECTIVES:
1. Writing drivers for ADC    
      - Tempsensor or lightsensor. We can just hook up an voltage in the beginning. 
2. Writing drivers for UART/serial output.
      - Output to terminal and RPI. 
3. Writing drivers for UART/serial input.?!?!
      -Depends on the reciving end RPI is pretty straight forward in Python programming language. 


//
Please feel free to change anything.  










![adc_arduino_rpi](https://github.com/mh2933/atmega328p_drivers-/assets/42110442/1a36ae8c-3e37-43bf-b39a-5a21687bced8)






