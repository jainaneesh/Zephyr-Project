#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#define UART_FRAME_SIZE 4
#define UART_START_BYTE 0xAA
#define CMD_PING 0x01

void uart_protocol_init(void);       // no args now
void uart_send_ping(uint8_t value);
void uart_receive_loop(void);
void uart_rx_poll_test(void);
// void uart_cb(const struct device *dev, void *user_data);

#endif // UART_PROTOCOL_H
