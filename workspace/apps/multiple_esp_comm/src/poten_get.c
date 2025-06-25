#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/pwm.h>
#include "poten_get.h"

// Configs
#define ADC_THRESHOLD 2000
#define STACK_SIZE 1024
#define PRIORITY 5
#define MSGQ_MAX_MSGS 10
#define MSG_SIZE sizeof(uint16_t)
#define ADC_SLEEP_MS 500

// ADC Setup
#define MY_ADC_CH DT_ALIAS(my_adc_channel)
static const struct device *adc = DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(MY_ADC_CH);

// Message Queue
K_MSGQ_DEFINE(adc_msgq, MSG_SIZE, MSGQ_MAX_MSGS, 4);

// Thread stack and metadata
K_THREAD_STACK_DEFINE(adc_stack, STACK_SIZE);
struct k_thread adc_thread_data;


// ADC + PWM Thread
void adc_pwm_thread(void *arg1, void *arg2, void *arg3)
{
    uint16_t buf;
    int32_t vref_mv = DT_PROP(MY_ADC_CH, zephyr_vref_mv);
    struct adc_sequence seq = {
        .channels = BIT(adc_ch.channel_id),
        .buffer = &buf,
        .buffer_size = sizeof(buf),
        .resolution = DT_PROP(MY_ADC_CH, zephyr_resolution),
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