#include "UART_LoRa_AUTOPAX.h"
#include "miwi_api.h"
#include "miwi_p2p.h"
#include "LoRa_P2P_Terminal.h"
#include "mimem.h"



void UART_init(void)
{
	UART_LoRa_init();
	UART_IO_init();
}

void UART_LoRa_init(void)
{
	
	struct usart_config config_uart_LoRa; //Making an config struct for LoRa Module
	usart_get_config_defaults(&config_uart_LoRa); //Initializing the UART by setting default values to the module
	
	//Don't use PA18(LED_PIN1) and PA19(LED_PIN0)
	config_uart_LoRa.baudrate    = UART_BAUD;
	config_uart_LoRa.mux_setting = USART_RX_1_TX_0_XCK_1; //RX - TX position ref: https://asf.microchip.com/docs/latest/common.services.fs.fatfs.access_example.saml21_xplained_pro/html/asfdoc_sam0_sercom_usart_mux_settings.html
	config_uart_LoRa.pinmux_pad0 = PINMUX_PA22C_SERCOM3_PAD0;	// TX - PA22
	config_uart_LoRa.pinmux_pad1 = PINMUX_PA23C_SERCOM3_PAD1;	// RX - PA23
	config_uart_LoRa.pinmux_pad2 = PINMUX_UNUSED;				// UNUSED
	config_uart_LoRa.pinmux_pad3 = PINMUX_UNUSED;				// UNUSED
	
	while (usart_init(&UART_LoRa,SERCOM3, &config_uart_LoRa) != STATUS_OK) {}

	usart_enable(&UART_LoRa);
}

void UART_IO_init(void)
{
	struct usart_config config_uart_IO;
	usart_get_config_defaults(&config_uart_IO);

	config_uart_IO.baudrate    = UART_BAUD;
	config_uart_IO.mux_setting = USART_RX_3_TX_0_XCK_1;		// SERCOM5
	config_uart_IO.pinmux_pad0 = PINMUX_PB02D_SERCOM5_PAD0; // TX - PB02
	config_uart_IO.pinmux_pad1 = PINMUX_UNUSED;				// UNUSED
	config_uart_IO.pinmux_pad2 = PINMUX_UNUSED;				// UNUSED
	config_uart_IO.pinmux_pad3 = PINMUX_PB23D_SERCOM5_PAD3; // RX - PB23
	
	while (usart_init(&UART_IO,SERCOM5, &config_uart_IO) != STATUS_OK) {}
	
	usart_enable(&UART_IO);
}

void UART_cb_init(void)
{
	//UART_LoRa_cb_init();
	UART_IO_cb_init();
}

void UART_LoRa_cb_init(void)
{
	usart_register_callback(&UART_LoRa,UART_LoRa_rx_cb, USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&UART_LoRa, USART_CALLBACK_BUFFER_RECEIVED);
}

void UART_LoRa_tx_cb(struct usart_module *const usart_module)
{
	port_pin_toggle_output_level(LED_0_PIN);
}

void UART_LoRa_rx_cb(struct usart_module *const usart_module)
{

}



void UART_IO_cb_init(void)
{
	usart_register_callback(&UART_IO,UART_IO_rx_cb, USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&UART_IO, USART_CALLBACK_BUFFER_RECEIVED);
}

void UART_IO_tx_cb(struct usart_module *const usart_module)
{
	port_pin_toggle_output_level(LED_1_PIN);
}

void UART_IO_rx_cb(struct usart_module *const usart_module)
{
	T_SendReceivedUARTMessage(rx_buffer_IO[0]);
}

void UART_SAM_To_RPi(uint8_t* data)
{
	usart_write_buffer_wait(&UART_LoRa, data, 1);
}

void UART_SAM_To_IO(uint8_t* data)
{
	usart_write_buffer_wait(&UART_IO, data, 1);
}