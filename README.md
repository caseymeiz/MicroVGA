# MicroVGA

Color VGA Video From a MC9S12DJ256 Microcontroller

[MC9S12DJ256FS.pdf](http://www.nxp.com/assets/documents/data/en/fact-sheets/MC9S12DJ256FS.pdf)


## Desription
Using the MC9S12DJ256 Microcontroller to display 

## Set-up
### Hardware
We used PORTB bits for the syncs; bit 0 is used for the vsync and bit 1 for the hsync. For the color we didn't care for the full 24 bits color so we just did it digitaly, which give us 3 bits of color. The three least significant bit on PORTP were used the color. There was no correct placement of the color because we could only draw boxes and we couldn't any better to be display. We used the analog ports 7 and 6 for the joystick. We used PORTA for the button to change the color of the background and box. 

### Software
We had two main interrupt

## Reflection
