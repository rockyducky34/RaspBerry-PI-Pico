#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <iostream>
#include <cuchar>

#define BIT1 15
#define BIT2 14
#define BIT3 13
#define BIT4 12


int main()
{
    stdio_init_all();

    gpio_init(BIT1);
    gpio_init(BIT2);
    gpio_init(BIT3);
    gpio_init(BIT4);
    gpio_set_dir(BIT1,GPIO_OUT);
    gpio_set_dir(BIT2,GPIO_OUT);
    gpio_set_dir(BIT3,GPIO_OUT);
    gpio_set_dir(BIT4,GPIO_OUT);

    // Initialise the Wi-Fi chip
    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed\n");
    //     return -1;
    // }

    // Example to turn on the Pico W LED
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    int num = 0;

    while (true) {
        
        if(num%2 == 1){
            gpio_put(BIT1,1);
        } else {
            gpio_put(BIT1,0);
        }

        if((num/2 + 1)%2 == 0 && num != 0){
            gpio_put(BIT2,1);
        } else {
            gpio_put(BIT2,0);
        }

        if((num%8)>=4){
            gpio_put(BIT3,1);
        } else {
            gpio_put(BIT3,0);
        }

        if(num>=8){
            gpio_put(BIT4,1);
        } else {
            gpio_put(BIT4,0);
        }

        //printf("num is %d\n",num);

        std::cout << "num is " << num << "\r" << std::flush;
        if(num >= 15)
            std::cout << "num is    " << "\r" << std::flush;
            
        sleep_ms(500);
        // std::cout << "enter num between 0-15 "<< std::endl;
        // std::cin >> std::mbrtowc num; 
        // std::cout << std::endl;
        num++;
        if(num >= 16)
            num = 0;

    }
}
