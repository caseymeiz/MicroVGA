# MicroVGA

Color VGA Video From a MC9S12DJ256 Microcontroller

[MC9S12DJ256FS.pdf](http://www.nxp.com/assets/documents/data/en/fact-sheets/MC9S12DJ256FS.pdf)

## Desription
The goal of our project was to display color on a monitor that supported VGA. 

To achive this goal we decided to create a 75 x 75 pixel square on the monitor that can have it's color changed with a button press and it's position moved with a JoyStick. The color of the square and background can be chaned to 8 different colors(3-bit color).
## Set-up
### Components
* Monitor that supports VGA connection and 680x480 resolution
* VGA cable
* MC9S12DJ256 Microcontroller (Thunder Bird)

### Hardware
We used PORTB bits for the syncs; bit 0 is used for the vsync and bit 1 for the hsync. For the color we didn't care for the full 24 bits color so we just did it digitaly, which give us 3 bits of color. The three least significant bit on PORTP were used the color. There was no correct placement of the color because we could only draw boxes and we couldn't any better to be display. We used the analog ports 7 and 6 for the joystick. We used PORTA for the button to change the color of the background and box. 

### Software
We had two main interrupt

## Reflection
