#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include <iostream>


#define RED 15
#define YELLOW 14
#define GREEN 13
#define PIN 28
#define ADC 2

void led(int matrix[]){
                gpio_put(RED,0);
                gpio_put(YELLOW,0);
                gpio_put(GREEN,0);
    for (int i = 0; i < 3; i++){
        int led = matrix[i];
        switch (led)
        {    
            case RED:
                gpio_put(RED,1);
                std::clog << "LED is red   \n";
                break;
            case YELLOW:
                gpio_put(YELLOW,1);
                std::clog << "LED is yellow\n";
                break;
            case GREEN:
                gpio_put(GREEN,1);
                std::clog << "LED is green \n";
                break;
            default:
                break;
        }
    }
}

int main()
{
    stdio_init_all();



    //initialize adc
    adc_init();

    //intialize adc gpio
    adc_gpio_init(PIN);
    gpio_init(RED);
    gpio_init(YELLOW);
    gpio_init(GREEN);

    //initializ funciton
    adc_select_input(ADC);
    gpio_set_dir(RED, GPIO_OUT);
    gpio_set_dir(YELLOW, GPIO_OUT);
    gpio_set_dir(GREEN, GPIO_OUT);

    int matrix[3];

    while (true) {
        const float conversion_factor = 3.3f / (1 << 12);
        auto val = adc_read();
        auto volt = val * conversion_factor;
        //std::clog << "Raw value: " << val << ", Voltage: " << "\r" << std::flush;

        //"\033[<num>F" goes back num lines up in console
        //std::clog << "\033[F";

        //"\033[H" Moves cursor to the top-left corner (0,0)
        std::clog << "\033[H";

        std::clog << "Raw value: " << val << ", Voltage: " << volt << std::endl << std::flush;
        
        matrix[0] = 0;
        matrix[1] = 0;
        matrix[2] = 0;

        if(volt <=1.3){
           matrix[0] = RED;
        } 
        if(volt >0.9 && volt <= 2.4){
            matrix[1] = YELLOW;
        } 
        if(volt > 2.0){
            matrix[2] = GREEN;
        }

        led(matrix);

        std::clog << "                                  ";

        sleep_ms(500);
    }
}
