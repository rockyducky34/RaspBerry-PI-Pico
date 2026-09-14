#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <iostream>
#include <limits>


#define PIN 16
#define WRAP 65530

void set_pwm_pin(uint pin, uint freq, uint duty_c) { 
		gpio_set_function(pin, GPIO_FUNC_PWM);
		uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_config config = pwm_get_default_config();
		float div = (float)clock_get_hz(clk_sys) / (freq * WRAP);
		pwm_config_set_clkdiv(&config, div);
		pwm_config_set_wrap(&config, WRAP); 
		pwm_init(slice_num, &config, true); // start the pwm running according to the config
		pwm_set_gpio_level(pin, duty_c); //connect the pin to the pwm engine and set the on/off level. 
};

int main()
{
    stdio_init_all();

     // Tell GPIO 0 and 1 they are allocated to the PWM

    
    
    

    float voltage = 0;

    while (true)
    {
        std::cout << "What output voltage do you want?\n" << std::endl ;
        std::cin >> voltage;
        while (true)
        {
            if (std::cin.fail()) { // Check if the input type didn't match
                std::cout << "Invalid input! Please enter a valid number.\n";
                
                std::cin.clear();  // 1. Reset the error flags so cin works again
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\r'); // 2. Discard the bad data

                std::cout << "What output voltage do you want?\n" << std::endl ;
                std::cin >> voltage;
                
            } else {
                std::cout << "your voltage is " << voltage << std::endl;
                break; // Input was valid, break out of the loop
            }
        }
        
        if(voltage < 0) voltage = 0;
        if(voltage > 3.3) voltage = 3.3;
        float pwmVal=(WRAP/3.3)*voltage;
        std::cout << "pwmval = " << pwmVal << std::endl;

        set_pwm_pin(PIN,10,pwmVal);
    }
    
}
