#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <stdio.h>


static const struct gpio_dt_spec driver_pin_info = GPIO_DT_SPEC_GET(DT_ALIAS(flash_gpio), gpios);
static const struct gpio_dt_spec detecting_pin_info = GPIO_DT_SPEC_GET(DT_ALIAS(detect_gpio), gpios);

int gpio_init(void){

    // Variable to check the init status of the two pins
    uint8_t status = 0;

    // Checking if GPIO was successfully initialized or not
    if ( !gpio_is_ready_dt(&driver_pin_info) ){
        // Printing message to check if driver pin was initialized
        printk("Driver Pin was not initialized\r\n");
        status |= 1;
    } else {
        printk("Driver Pin was initialized\r\n");
    }

    if ( !gpio_is_ready_dt(&detecting_pin_info) ){
        // Printing message to check if detecter pin was initialized
        printk("Detector Pin was NOT initialized\r\n");
        status |= 2;
    } else {
        printk("Detector Pin was initialized\r\n");
    }

    return status;
}

int configure_pins(void){
    // Variables to store the return status of pin configuration APIs
    int ret_driver_pin, ret_detect_pin;

    ret_driver_pin = gpio_pin_configure_dt(&driver_pin_info, GPIO_OUTPUT);
    // Checking if the Driver pin was configured
    if ( ret_driver_pin < 0 ){
        printk("Driver pin configuration failed\r\n");
        return ret_driver_pin;
    }

    ret_detect_pin = gpio_pin_configure_dt(&detecting_pin_info, GPIO_INPUT);
    // Checking if the Detect pin was configured
    if ( ret_detect_pin < 0 ){
        printk("Detect pin configuration failed\r\n");
        return ret_detect_pin;
    }

    // Safe return if nothing fails
    return 0;
}

int set_pin_state(void){
    int ret_driver_pin_state = gpio_pin_set_dt(&driver_pin_info, 1);
    // Checking if state was set
    if ( ret_driver_pin_state < 0 ){
        printk("Driver pin is set to HIGH - 1\r\n");
        return 0;
    } else {
        return 1;
    }
}

int identify_board(void){
    int ret_detect_pin_state = gpio_pin_get_dt(&detecting_pin_info);

    if ( ret_detect_pin_state < 0 ){
        printk("Error reading pin\r\n");
        return -1;
    }

    if ( ret_detect_pin_state ){
        printk("This board is ROLE 1\r\n");
        return ret_detect_pin_state;
    } else {
        return 0;
    }
}