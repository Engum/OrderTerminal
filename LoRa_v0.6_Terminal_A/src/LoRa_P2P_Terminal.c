
#include "miwi_api.h"
#include "miwi_p2p.h"
#include "task.h"
#include "LoRa_P2P_Terminal.h"
#include "mimem.h"
#include "asf.h"
#include "customCommandsTerminalFerry.h"
#include "UART_LoRa_AUTOPAX.h"
#include "UpdateQueue.h"


#if defined(ENABLE_SLEEP_FEATURE)
#include "sleep_mgr.h"
#endif

#if defined (ENABLE_CONSOLE)
#include "sio2host.h"
#endif

#include "phy.h"
#include "sw_timer.h"

#if defined(PROTOCOL_P2P)

uint8_t i;
uint8_t TxNum = 0;
uint8_t RxNum = 0;
uint8_t msghandledemo = 0;

bool orderStatus = false;

uint8_t* previousMessage = NULL;

uint8_t ferryState = 0;

#define PAYLOAD_TERMINAL 1

void TxToutCallback(void)
{
	/* That bring the node back to continuous transaction cycle */
	PHY_DataConf(TRANSACTION_EXPIRED);
	SwTimerStop(TxTimerId);
}


// Transmission callback
void dataConfcb(uint8_t handle, miwi_status_t status, uint8_t* msgPointer)
{
#if defined (ENABLE_CONSOLE)
	printf("\nData Confirm: Handle: %d status:%d \r\n", handle, status);
#endif // #if defined (ENABLE_CONSOLE)
	/* Stop transmission timeout timer */
	SwTimerStop(TxTimerId);
	/* Free payload buffer allocated */
	MiMem_Free(msgPointer);
	
}




void T_A_OnDemandOrder(void)
{	
	uint8_t pressedButton = ButtonPressed();
	// Checks if button has been pressed
	
	if (pressedButton)
	{
		if(!orderStatus)
		{
			uint8_t teaid_reqf_request = TEAID_REQF_REQUEST;
			UART_SAM_To_RPi(&teaid_reqf_request);
			LED_Toggle(LED1);

			T_BroadcastMessageToFerry(TEAID_REQF_REQUEST);
			
			port_pin_set_output_level(LED_BUTTON, true);
			orderStatus = true;
			
			
		}
	}
}

void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	/*******************************************************************/
	// If a packet has been received, handle the information available
	// in rxMessage.
	/*******************************************************************/
	if ((myPANID.v[1] == ind->SourcePANID.v[1]) && (myPANID.v[0] == ind->SourcePANID.v[0]))
	{	
		T_SendReceivedLoRaMessage(rxMessage.Payload[0]);	
		
		#if defined(ENABLE_CONSOLE)
		DemoOutput_HandleMessage();
		#endif
		DemoOutput_UpdateTxRx(TxNum, ++RxNum);
		// Toggle LED2 to indicate receiving a packet.
		LED_Toggle(LED0);
		DemoOutput_Instruction();	
	}
	else
	{
		printf("Packet received from other Source PAN ID : 0x%x%x\r\n",ind->SourcePANID.v[1],ind->SourcePANID.v[0]);
	}
	
}

struct queStruct s = {
	.front = -1,
	.rear = -1
};

void T_BroadcastMessageToFerry(uint8_t signal)
{
	uint8_t* dataPtr = NULL;
	uint8_t dataLen = 0;
	uint16_t broadcastAddress = 0xFFFF;
	
	MiMem_Free(previousMessage);
	previousMessage = MiMem_Alloc(CALC_SEC_PAYLOAD_SIZE(PAYLOAD_TERMINAL));
	
	dataPtr = MiMem_Alloc(CALC_SEC_PAYLOAD_SIZE(PAYLOAD_TERMINAL));
	
	if (NULL == dataPtr) return;
	
	for (i = 0; i < PAYLOAD_TERMINAL; i++)
	{
		previousMessage[i] = signal;
		dataPtr[dataLen++] = signal;
	}
			
	// Broadcast the message
	if (MiApp_SendData(SHORT_ADDR_LEN, (uint8_t *)&broadcastAddress, dataLen, dataPtr, msghandledemo++, true, dataConfcb) == false)
	{
		DemoOutput_BroadcastFail();
	}
	else
	{
		SwTimerStart(TxTimerId, MS_TO_US(5000), 0, (void *)TxToutCallback, NULL);
	}
	
}


// Send received UART message with LoRa
void T_SendReceivedUARTMessage(uint8_t message)
{
	printf("\n\r Message received: %x", message);
	switch(message)
	{		
		case TEAID_GSTATE_TIMEOUT:
			break;
			
		case TEAID_GSTATE_OPEN:
			break;
			
		case TEAID_GSTATE_CLOSE:
			break;
			
		case TEAID_GSTATE_PAUSE:
			break;
			
		case TEAID_DRDY_READY:
			break;
			
		case TEAID_DRDY_NREADY:
			break;
			
		case TEAID_GPCLEAR_READY:
			break;
			
		case TEAID_GPCLEAR_NREADY:
			break;
			
		case TEAID_MSTP_PUSHED:
			break;
			
		case TEAID_MCMD_MOG:
			break;
			
		case TEAID_MCMD_MCG:
			break;
		
		case TEAID_MCMD_MOH:
			break;
		
		case TEAID_MCMD_MCH:
			break;	
			
		case PASSENGERS_ZERO:
			break;
			
		case PASSENGERS_ONE:
			break;
		
		case PASSENGERS_TWO:
			break;
		
		case PASSENGERS_THREE:
			break;
		
		case PASSENGERS_FOUR:
			printf("\n Recevied UART message from IO-machine \n\r");
			break;
		
		case PASSENGERS_SIX:
			break;
		
		case PASSENGERS_SEVEN:
			break;
		
		case PASSENGERS_EIGHT:
			break;
		
		case PASSENGERS_NINE:
			break;
		
		case PASSENGERS_TEN:
			break;
		
		case PASSENGERS_ELEVEN:
			break;
		
		case PASSENGERS_TWELVE:
			break;
		
		case PASSENGERS_THRITEEN:
			break;
		
		case PASSENGERS_FOURTEEN:
			break;
		
		case PASSENGERS_FIFTEEN:
			break;
			
		
		default: ;
			uint8_t send_message_again = SEND_MESSAGE_AGAIN;
			UART_SAM_To_IO(&send_message_again);
			return;
			
	}
	T_BroadcastMessageToFerry(message);
}

// Send received LoRa message with UART
void T_SendReceivedLoRaMessage(uint8_t message)
{
	printf("\n\r Received LoRa message: %x", message);
	// Checks if received message is meant for terminal A
	if (T_A_CheckIdentifier(message))
	{		

		switch(message)
		{
			case TEAID_GCMD_RESET:
				break;
				
			case TEAID_GCMD_OPEN:
				ferryState = TEAID;
				UART_SAM_To_RPi(&message);
				printf("\n Open gate at terminal A \n\r");
				break;
				
			case TEAID_GCMD_CLOSE:
				orderStatus = false;
				port_pin_set_output_level(LED_BUTTON, false);
				UART_SAM_To_RPi(&message);
				printf("\n Close gate at terminal A");
				break;
				
			case TEAID_GCMD_PAUSE:
				break;
				
			case TEAID_CQUD_QCONF:
				printf("\n Order confirmed, wait for ferry to arrive");
				break;;
				
			case TEAID_FREQS_REQCNT:
				break;
				
			case TEAID_FREQS_REQDRDY:
				break;
				
			case TEAID_FREQS_REQGCLR:
				break;
				
			case TEAID_FREQS_GSREQ:
				break;
				
			case TEAID_FREQS_MSREQ:
				break;
				
			case TEAID_FPROC_DCOMP:
				break;
				
			case TEAID_FPROC_BCOMP:
				UART_SAM_To_RPi(&message);
				ferryState = IN_TRANSIT;
				break;
				
			case TEAID_FGS_TIMEOUT:
				break;
			
			case TEAID_FGS_OPEN:
				break;
			
			case TEAID_FGS_CLOSE:
				break;
			
			case TEAID_FGS_PAUSE:
				break;
				
			/* Ask for new message if received message was not in register */	
			default:
				T_BroadcastMessageToFerry(SEND_MESSAGE_AGAIN);		
				return;
		}
		UART_SAM_To_IO(&message);
	}
	else if (message == SEND_MESSAGE_AGAIN)
	{
		if (previousMessage)	// Send previous message if its not NULL
		{
			T_BroadcastMessageToFerry(previousMessage[0]);
			printf("\n Send message again \n\r");
		}
	}
	else if (T_B_CheckIdentifier(message))
	{
		switch(message)
		{
			case TEBID_GCMD_OPEN:			// Update screen
				ferryState = TEBID;
				UART_SAM_To_RPi(&message);
				printf("\n Ferry is at terminal B \n\r");
				break;
				
			case TEBID_GCMD_CLOSE:
				UART_SAM_To_RPi(&message);
				break;
			
			case TEBID_FPROC_BCOMP:			// Update screen
				ferryState = IN_TRANSIT;
				UART_SAM_To_RPi(&message);
				printf("\n Ferry is leaving terminal B");
				break;
			
			default:						// Do nothing
				break;
		}
	}
	else
	{
		//T_BroadcastMessageToFerry(SEND_MESSAGE_AGAIN);
		return;
	}
}



bool T_A_CheckIdentifier(uint8_t LoRa_message)
{
	int MSB_LoRA_message = (LoRa_message & 0xC0);	// 2 MSB of received message
	
	return MSB_LoRA_message == TEAID;			// Return true if identifier matches
}


bool T_B_CheckIdentifier(uint8_t LoRa_message)
{
	int MSB_LoRA_message = (LoRa_message & 0xC0);	// 2 MSB of received message
	
	return MSB_LoRA_message == TEBID;			// Return true if identifier matches
}

bool M_CheckIdentifier(uint8_t LoRa_message)
{
	int MSB_LoRA_message = (LoRa_message & 0xC0);	// 2 MSB of received message
	
	return MSB_LoRA_message == FEID;				// Return true if identifier matches
}

void init_order_button(void)
{
	struct port_config order_button_conf;
	port_get_config_defaults(&order_button_conf);
	order_button_conf.direction  = PORT_PIN_DIR_INPUT;
	port_pin_set_config(ORDER_BUTTON_PIN, &order_button_conf);
}

void init_LED_order_button(void)
{
	struct port_config order_button_led_conf;
	port_get_config_defaults(&order_button_led_conf);
	order_button_led_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_BUTTON, &order_button_led_conf);
}




#endif // #if defined(PROTOCOL_P2P)
