#include <zephyr/kernel.h>
#include "uart_comm.h"
#include "gpio_get.h"

// Defining enums to identify the boards
typedef enum {
    ROLE_UNKNOWN = 0,
    ROLE_BOARD_1 = 1,
    ROLE_BOARD_2 = 2,
} BoardRole;

BoardRole role = ROLE_BOARD_1;

void main(void)
{
    // GPIO initialization
    if (gpio_init() != 0) {
        printk("GPIO init failed\r\n");
        return;
    }

    if (configure_pins() != 0) {
        printk("GPIO configuration failed\r\n");
        return;
    }

    set_pin_state();

    role = identify_board();
    uart_protocol_init();  // Now self-contained
    

    if (role == ROLE_BOARD_1) {
        printk("You are board 1\r\n");

        uint8_t counter = 0;
        while (1) {
            uart_send_ping(counter++);
            k_sleep(K_SECONDS(1));
        }

    } else if (role == ROLE_BOARD_2) {
        printk("You are board 2\r\n");
        uint8_t counter = 0;
        while (1) {
            uart_send_ping(counter++);
            k_sleep(K_SECONDS(1));
        }
        // uart_rx_poll_test();

        //uart_receive_loop();  // Blocking loop

    } else {
        printk("Cannot recognize the board\r\n");
    }
}