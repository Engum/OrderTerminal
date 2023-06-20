#include "UART_LoRa_AUTOPAX.h"
#include "miwi_api.h"
#include "miwi_p2p.h"
#include "LoRa_P2P_Modem.h"
#include "mimem.h"



void UART_init(void)
{
	UART_IO_init();
}

void UART_IO_init(void)
{
	struct usart_config config_uart_IO;
	usart_get_config_defaults(&config_uart_IO);

	config_uart_IO.baudrate    = UART_BAUD;
	config_uart_IO.mux_setting = USART_RX_3_TX_0_XCK_1; //SERCOM1
	config_uart_IO.pinmux_pad0 = PINMUX_PB02D_SERCOM5_PAD0; //TX
	config_uart_IO.pinmux_pad1 = PINMUX_UNUSED; //UNUSED
	config_uart_IO.pinmux_pad2 = PINMUX_UNUSED;
	config_uart_IO.pinmux_pad3 = PINMUX_PB23D_SERCOM5_PAD3; //RX
		
	while (usart_init(&UART_IO,SERCOM5, &config_uart_IO) != STATUS_OK) {
	}
	
	
	usart_enable(&UART_IO);
}

void UART_cb_init(void)
{
	UART_IO_cb_init();
}

void UART_IO_cb_init(void)
{
	usart_register_callback(&UART_IO,UART_IO_rx_cb, USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&UART_IO, USART_CALLBACK_BUFFER_RECEIVED);
}


void UART_IO_rx_cb(struct usart_module *const usart_module)
{
	printf("\n\r UART message received %x", rx_buffer_IO[0]);
	M_SendReceivedUARTMessage(rx_buffer_IO[0]);
}

void UART_SAM_To_IO(uint8_t* data)
{
	usart_write_buffer_wait(&UART_IO, data, 1);
}