
#ifndef UART_LoRa_AUTOPAX_H_INCLUDED
#define UART_LoRa_AUTOPAX_H_INCLUDED

//-------- INCLUDES ----------------------------//
#include <asf.h>
#include "sio2host.h"

//-------- DEFINES -----------------------------//
#define LoRa_UART_RX_BUFFER_LENGTH   1
#define AUTOPAX_UART_RX_BUFFER_LENGTH   1

#define UART_BAUD 115200

//-------- STRUCTS ------------------------------//
struct usart_module UART_LoRa;
struct usart_module UART_IO;

//-------- VARIABLES ----------------------------//
volatile uint8_t rx_buffer_LoRa[LoRa_UART_RX_BUFFER_LENGTH];
volatile uint8_t rx_buffer_IO[AUTOPAX_UART_RX_BUFFER_LENGTH];

//---------- PROTOTYPES -------------------------//
//------- INITIALIZING --------------------//
//---- UART ---------------------------//
void UART_init(void);
void UART_LoRa_init(void);
void UART_IO_init(void);

//---- CALLBACK ----------------------//
void UART_cb_init(void);
void UART_LoRa_cb_init(void);
void UART_IO_cb_init(void);

//------ CALLBACK FUNCTIONS LoRa ---------------//
void UART_LoRa_rx_cb(struct usart_module *const usart_module);
void UART_LoRa_tx_cb(struct usart_module *const usart_module);

//------ CALLBACK FUNCTIONS AUTOPAX -----------//
void UART_IO_rx_cb(struct usart_module *const usart_module);
void UART_IO_tx_cb(struct usart_module *const usart_module);
//------ DATA FUNCTIONS ----------------------//
void UART_SAM_To_RPi(uint8_t* data);

void UART_SAM_To_IO(uint8_t* data);

#endif /* UART_LoRa_AUTOPAX_H_INCLUDED */
