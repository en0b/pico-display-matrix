#include "pico/stdlib.h"
#include "pico_display.hpp"
#include <string>
#include "images.h"

const uint32_t FPS = 1000 / 10; // Run at 10 FPS, 100ms
const uint32_t max_frame = 126;
uint32_t buffer_size = pimoroni::PicoDisplay::WIDTH * pimoroni::PicoDisplay::HEIGHT;
uint32_t frame = 0;
uint32_t last_time = 0;
uint16_t buffer[pimoroni::PicoDisplay::WIDTH * pimoroni::PicoDisplay::HEIGHT];
pimoroni::PicoDisplay pico_display(buffer);

uint16_t pallete[16] = { // 16 colours
        pico_display.create_pen(1, 4, 0),
        pico_display.create_pen(2, 12, 0),
        pico_display.create_pen(5, 23, 0),
        pico_display.create_pen(2, 40, 4),
        pico_display.create_pen(2, 58, 2),
        pico_display.create_pen(0, 85, 0),
        pico_display.create_pen(24, 158, 22),
        pico_display.create_pen(17, 225, 20),
        pico_display.create_pen(35, 38, 34),
        pico_display.create_pen(36, 86, 37),
        pico_display.create_pen(76, 84, 76),
        pico_display.create_pen(86, 231, 87),
        pico_display.create_pen(122, 149, 120),
        pico_display.create_pen(230, 233, 229),
        pico_display.create_pen(0, 0, 0),
        pico_display.create_pen(0, 0, 0)};

void init() {
    pico_display.init();
    pico_display.set_backlight(255);
    pico_display.set_pen(0, 0, 0);
    pico_display.clear();

    // Initialises the screen
    pico_display.update();
    pico_display.set_led(24,158,24);
}

void update_and_render(uint32_t time) {
    if (time - last_time < FPS) {
        return;
    }
    last_time = time;
    for(int i = 0; i < buffer_size; i++)
    {
        if(i%2 == 0)
        {
            buffer[i] = pallete[images[(buffer_size*frame + i)/2]&0x0F];
        }
        else
        {            
            buffer[i] = pallete[images[(buffer_size*frame + i)/2]>>4];
        }
    }
    if (frame == max_frame)
    {
        frame = 0;
    }
    else
    {
        frame++;
    }    
    pico_display.update();
}

bool x_pressed = false;
bool y_pressed = false;
bool b_pressed = false;
bool a_pressed = false;
bool enabled = true;

int main() {
    init();
    uint64_t start_time = time_us_64();
    while (true) {

        if (!y_pressed && pico_display.is_pressed(pimoroni::PicoDisplay::Y)) {
            ;
        }
        y_pressed = pico_display.is_pressed(pimoroni::PicoDisplay::Y);

        if (!b_pressed && pico_display.is_pressed(pimoroni::PicoDisplay::B)) {
            ;
        }
        b_pressed = pico_display.is_pressed(pimoroni::PicoDisplay::B);

        if (!a_pressed && pico_display.is_pressed(pimoroni::PicoDisplay::A)) {
           ;
        }
        a_pressed = pico_display.is_pressed(pimoroni::PicoDisplay::A);

        if (!x_pressed && pico_display.is_pressed(pimoroni::PicoDisplay::X)) {
            ;
        }
        x_pressed = pico_display.is_pressed(pimoroni::PicoDisplay::X);
        update_and_render((time_us_64() - start_time) / 1000);
    }
}
