#include <stdio.h>
#include "pico/stdlib.h"
#include <iostream>
#include <hardware/pwm.h>
#include <hardware/adc.h>
#include <cmath>


#define PIN 15
#define WRAP 65530
#define POT 2
#define POT_PIN 28
#define POT_LIMIT 4095

void set_pwm_pin(uint pin){
    gpio_set_function(pin,GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, WRAP);
    pwm_init(slice_num, &config, true);
}

int main()
{
    stdio_init_all();

    adc_init();

    set_pwm_pin(PIN);

    adc_gpio_init(POT_PIN);
    adc_select_input(POT);

    auto adc = adc_read();

    float pwmVal = 16.f/WRAP * adc*(WRAP/POT_LIMIT);
    auto brightness = std::pow(2,pwmVal);
    while (true)
    {
        adc = adc_read();
        pwmVal = 16.f/WRAP * adc*(WRAP/POT_LIMIT);
        brightness = std::pow(2,pwmVal);
        std::cout << "adc: " << adc << ", pmwVal: " << pwmVal << '\r' ;

        pwm_set_gpio_level(PIN,brightness);
        
    }
    
}
