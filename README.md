# pico-display-matrix
Digital rain animation gif with glow squeezed into a raspberry pi pico and pimoroni pico-display
_or_
how to actually use all Flash memory on your raspberry pi pico


#Background
I wanted to have the matrix 'digital rain' effect on a small display. Instead of using a library, I wanted to use a 'nicely rendered' GIF file for animation. Due to the display resolution of 135x240 it resulted in a GIF with a large file size of 8MB. Because I was too lazy to implement an existing file compression I first just shortened and modified the animation manually (with GIMP you can modify each frame of a gif).
Unfortunately, the file was still too large with roughly 4MB and then I decided to implement a primitive compression using just 16 custom colors (mainly different green tones and black). Then I used a python file to convert the gif to a .h file of what color to use from the palette for each pixel and each frame. Like that I needed just 4bits per pixel and I could squeeze all 127 frames into the 2MB Flash the Raspberry Pi pico has on board.

#Files
convert_gif_to_h.py : use this to convert your custom gif to a .h file (Raspberry Pi Pico is able to store 127frames with 135x240)
pico_rain.cpp : source code for your pi. Set up your environment with VSCode and CMake yourself :) Look how to set it up with the pimoroni display.
images.h : converted gif to a large array
rain.gif : 127 frame animated GIF. has just 16 colors (actually only 14 are used)
pico_rain.uf2 : binary for the lazy ones

Have fun!
