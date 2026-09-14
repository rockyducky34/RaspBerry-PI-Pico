#include <stdio.h>
#include <iostream>
#include <limits>
#include "pico/stdlib.h"
#include <hardware/pwm.h>

#define RED 13
#define GREEN 14
#define BLUE 15
#define RGB_LIMIT 256
#define WRAP 65530


void set_pwm_pin(uint pin){
    gpio_set_function(pin,GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, WRAP);
    pwm_init(slice_num, &config, true);
}

void boundRBG(int* rgb){
    if(*rgb < 0) *rgb = 0;
    if(*rgb > RGB_LIMIT) *rgb = RGB_LIMIT;
}

int main()
{
    stdio_init_all();

    set_pwm_pin(RED);
    set_pwm_pin(GREEN);
    set_pwm_pin(BLUE);

    int red = 0;
    int blue = 0;
    int green = 0;
    float pwmVal = (WRAP/RGB_LIMIT);
    
    

    while (true) {

        std::cout << "Enter a rgb value R G B" << std::endl;
        std::cin >> red >> green >> blue;


        while (true)
        {
            if (std::cin.fail()) { // Check if the input type didn't match
                std::cout << "Invalid input! Please enter a valid value.\n";
                
                std::cin.clear();  // 1. Reset the error flags so cin works again
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\r'); // 2. Discard the bad data

                std::cout << "Enter a rgb value R G B\n" << std::endl ;
                std::cin >> red >> green >> blue;
                
            } else {
                
                break; // Input was valid, break out of the loop
            }
        }


        boundRBG(&red);
        boundRBG(&green);
        boundRBG(&blue);

        pwm_set_gpio_level(RED,pwmVal * red);
        pwm_set_gpio_level(GREEN,pwmVal * green);
        pwm_set_gpio_level(BLUE,pwmVal * blue);

        std::cout << "your color is " << red << " " << green  << " " << blue << std::endl;
    }
}
