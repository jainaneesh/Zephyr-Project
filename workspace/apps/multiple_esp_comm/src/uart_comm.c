#include <stdint.h>
#include "uart_comm.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>

// Bring in the UART node from overlay alias
#define UART_NODE DT_ALIAS(uart_tx)
static const struct device *uart_dev = DEVICE_DT_GET(UART_NODE);

// Thread stack and metadata
K_THREAD_STACK_DEFINE(uart_stack, STACK_SIZE);
struct k_thread uart_thread_data;

static uint8_t rx_buf[UART_FRAME_SIZE];
static size_t rx_index = 0;

#define CMD_IDLE   0x10


static uint8_t calculate_crc8(uint8_t cmd, uint8_t data)
{
    return cmd ^ data;
}

// uint8_t frame[UART_FRAME_SIZE] = {
//         UART_START_BYTE,
//         CMD_PING,
//         value,
//         calculate_crc8(CMD_PING, value)
//     };
// void uart_rx_poll_test(void)
// {
//     uint8_t test;
//     int ret = uart_poll_in(uart_dev, &test);
//     printk("poll ret: %d\n", ret);
//     if (ret == 0) {
//         printk("Poll test saw byte: 0x%02X\n", test);
//     } else {
//         printk("Poll test failed\n");
//     }
// }

static void process_frame(const uint8_t *frame)
{
    if (frame[0] != UART_START_BYTE) return;

    uint8_t cmd = frame[1];
    uint8_t data = frame[2];
    uint8_t crc = frame[3];

    if (crc != calculate_crc8(cmd, data)) {
        printk("CRC ERROR\n");
        return;
    }

    if (cmd == CMD_PING) {
        printk("PING received: %u\n", data);
    } else {
        printk("Unknown CMD: 0x%02X\n", cmd);
    }
}

static void uart_cb(const struct device *dev, void *user_data)
{
    printk("Inside of uart_cb\r\n");
    uint8_t byte;

    while (uart_irq_update(dev) && uart_irq_rx_ready(dev)) {
        while (uart_fifo_read(dev, &byte, 1)) {
            rx_buf[rx_index++] = byte;
            if (rx_index == UART_FRAME_SIZE) {
                process_frame(rx_buf);
                rx_index = 0;
            }
        }
        printk("Received byte: 0x%02X\n", byte);
    }
}


void uart_protocol_init(void)
{
    if (!device_is_ready(uart_dev)) {
        printk("UART device not ready\n");
        return;
    }
    uart_irq_callback_user_data_set(uart_dev, uart_cb, NULL);
    uart_irq_rx_enable(uart_dev);
}

// void uart_send_ping(uint8_t value)
// {
//     // printk("Inside uart_send_ping\r\n");
//     uint8_t frame[UART_FRAME_SIZE] = {
//         UART_START_BYTE,
//         CMD_PING,
//         value,
//         calculate_crc8(CMD_PING, value)
//     };
    
//     // printk("About to send uart\r\n");
//     // for (int i = 0; i < UART_FRAME_SIZE; i++) {
//     //     printk("0x%02X ", frame[i]);
//     // }
//     // printk("\r\n");
//     for (int i = 0; i < UART_FRAME_SIZE; i++) {
//         uart_poll_out(uart_dev, frame[i]);
//         printk("Sent: 0x%02X\n", frame[i]);
//     }
//     // int ret = uart_tx(uart_dev, frame, UART_FRAME_SIZE, SYS_FOREVER_US);
//     // if (ret < 0) {
//         // printk("UART TX failed: %d\n", ret);
//     // }
// }



// void uart_receive_loop(void)
// {
//    while (1) {
//        uint8_t byte;
//        if (uart_fifo_read(uart_dev, &byte, 1)) {
//            rx_buf[rx_index++] = byte;
//            if (rx_index == UART_FRAME_SIZE) {
//                process_frame(rx_buf);
//                rx_index = 0;
//            }
//        }
//        k_sleep(K_MSEC(1));
//    }
//}

// UART TX Thread
void uart_tx_thread(void *arg1, void *arg2, void *arg3)
{
    uint16_t val;

    if (!device_is_ready(uart_dev)) {
        printk("UART not ready\n");
        return;
    }

    while (1) {
        if (k_msgq_get(&adc_msgq, &val, K_FOREVER) == 0) {
            uint8_t cmd;
            if (val < 1000)
                cmd = CMD_IDLE;
            else if (val < 2000)
                cmd = CMD_WARN;
            else
                cmd = CMD_ALERT;

            // 🧱 Build UART Frame
            uint8_t data = (uint8_t)(val & 0xFF);
            uint8_t crc = calculate_crc8(cmd, data);
            uint8_t frame[UART_FRAME_SIZE] = {
                UART_START_BYTE,
                cmd,
                data,
                crc
            };

            for (int i = 0; i < UART_FRAME_SIZE; i++) {
                uart_poll_out(uart_dev, frame[i]);
                printk("Sent: 0x%02X\n", frame[i]);
            }
        }
    }
}


