#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <iostream>



#define PIN 28
#define ADC 2

int main()
{
    stdio_init_all();

    

    //initialize adc
    adc_init();

    //intialize adc gpio
    adc_gpio_init(PIN);

    adc_select_input(ADC);



    while (true) {
        const float conversion_factor = 3.3f / (1 << 12);
        auto val = adc_read();
        //std::clog << "Raw value: " << val << ", Voltage: " << "\r" << std::flush;
        std::clog << "Raw value: " << val << ", Voltage: " << val * conversion_factor << "\r" << std::flush;
        
        sleep_ms(500);
    }
}
