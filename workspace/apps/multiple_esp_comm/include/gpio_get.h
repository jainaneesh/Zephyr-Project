#ifndef GPIO_GET_H
#define GPIO_GET_H_

int gpio_init(void);
int configure_pins(void);
int set_pin_state(void);
int identify_board(void);
#endif