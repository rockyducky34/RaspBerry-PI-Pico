#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


#define LED_PIN 15

int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip

    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed\n");
    //     return -1;
    // }
        

    // Example to turn on the Pico W LED
    //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN,1);
        sleep_ms(1000);
        gpio_put(LED_PIN,0);
        sleep_ms(1000);

        printf("Hello\n");
    }
}
