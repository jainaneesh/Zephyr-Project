// #include "gpio.h"
#include <zephyr/kernel.h>

#include "gpio_get.h"

// Defining enums to identify the boards
typedef enum {
    ROLE_UNKNOWN = 0,
    ROLE_BOARD_1 = 1,
    ROLE_BOARD_2 = 2,
} BoardRole;

BoardRole role = ROLE_BOARD_1;

int main(void){

    // Checking if both GPIOs were initialized
    if ( gpio_init() != 0 ){
        printk("GPIO init failed\r\n");
        return 1;
    }

    // Checking if both GPIOs were configured
    if ( configure_pins() != 0 ){
        printk("GPIO configuration failed\r\n");
        return 1;
    }

    // Setting the driver pin HIGH
    set_pin_state();

    int role = identify_board();

    if (role == ROLE_BOARD_1) {
        printk("You are board 1\r\n");
    } else {
        printk("You are not the right board\r\n");
    }
}
