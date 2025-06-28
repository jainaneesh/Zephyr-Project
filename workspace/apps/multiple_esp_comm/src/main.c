#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/pwm.h>
#include <stdio.h>
#include <string.h>
#include "uart_comm.h"
#include "gpio_get.h"
// #include "poten_get.h"

// Configs
#define ADC_THRESHOLD 2000
#define STACK_SIZE 1024
#define PRIORITY 5
#define MSGQ_MAX_MSGS 10
#define MSG_SIZE sizeof(uint16_t)
#define ADC_SLEEP_MS 500

extern struct k_thread adc_thread_data;
extern struct k_thread uart_thread_data;
extern k_thread_stack_t adc_stack[];
extern k_thread_stack_t uart_stack[];

// Defining enums to identify the boards
typedef enum {
    ROLE_UNKNOWN = 0,
    ROLE_BOARD_1 = 1,
    ROLE_BOARD_2 = 2,
} BoardRole;

BoardRole role = ROLE_BOARD_1;


// #include <zephyr/kernel.h>


// #include "poten_get.h"


// static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(DT_ALIAS(my_adc_channel));





// Thread stack and metadata
K_THREAD_STACK_DEFINE(adc_stack, STACK_SIZE);
struct k_thread adc_thread_data;


// Message Queue
K_MSGQ_DEFINE(adc_msgq, MSG_SIZE, MSGQ_MAX_MSGS, 4);




// ADC + PWM Thread
void adc_pwm_thread(void *arg1, void *arg2, void *arg3)
{
    // ADC Setup
    // #define MY_ADC_CH DT_ALIAS(my_adc_channel)
    const struct device *adc = DEVICE_DT_GET(DT_ALIAS(my_adc));
    const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(DT_ALIAS(my_adc_channel));
    printk("ADC node label: %s\n", STRINGIFY(DT_ALIAS(my_adc)));
    printk("ADC channel alias: %s\n", STRINGIFY(DT_ALIAS(my_adc_channel)));
    uint16_t buf;
    int32_t vref_mv = DT_PROP(DT_ALIAS(my_adc_channel), zephyr_vref_mv);
    struct adc_sequence seq = {
        .channels = BIT(adc_ch.channel_id),
        .buffer = &buf,
        .buffer_size = sizeof(buf),
        .resolution = DT_PROP(DT_ALIAS(my_adc_channel), zephyr_resolution),
    };

    if (!device_is_ready(adc)) {
        printk("ADC not ready\n");
        return;
    }

    // if (!device_is_ready(pwm_led_0.dev)) {
    //     printk("PWM not ready\n");
    //     return;
    // }

    if (adc_channel_setup(adc, &adc_ch) < 0) {
        printk("Failed to setup ADC channel\n");
        return;
    }

    while (1) {
        if (adc_read(adc, &seq) < 0) {
            printk("ADC read failed\n");
            continue;
        }

        // PWM Duty Cycle
        // uint32_t pulse = pwm_led_0.period / ((1 << seq.resolution) / (float)buf);
        // int ret = pwm_set_dt(&pwm_led_0, pwm_led_0.period, pulse);
        // if (ret) {
        //     printk("PWM set failed: %d\n", ret);
        // }

        // printk("ADC: %4d | Pulse: %4d ns\n", buf, pulse);
        printk("ADC: %4d\n", buf);

        // Send to UART thread if above threshold
        if (buf > ADC_THRESHOLD) {
            k_msgq_put(&adc_msgq, &buf, K_NO_WAIT);
        }

        k_msleep(ADC_SLEEP_MS);
    }
}

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
        // Launch ADC Sampling Thread
        k_thread_create(&adc_thread_data, adc_stack, STACK_SIZE,
                        adc_pwm_thread, NULL, NULL, NULL,
                        PRIORITY, 0, K_NO_WAIT);

        // Launch UART TX Thread
        k_thread_create(&uart_thread_data, uart_stack, STACK_SIZE,
                        uart_tx_thread, NULL, NULL, NULL,
                        PRIORITY, 0, K_NO_WAIT);

    } else if (role == ROLE_BOARD_2) {
        printk("You are board 2\r\n");
        // uint8_t counter = 0;
        // while (1) {
        //     uart_send_ping(counter++);
        //     k_sleep(K_SECONDS(1));
        // }
        // uart_rx_poll_test();

        //uart_receive_loop();  // Blocking loop

    } else {
        printk("Cannot recognize the board\r\n");
    }
}