
#include "miwi_api.h"
#include "miwi_p2p.h"
#include "task.h"
#include "LoRa_P2P_Modem.h"
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


void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	/*******************************************************************/
	// If a packet has been received, handle the information available
	// in rxMessage.
	/*******************************************************************/
	if ((myPANID.v[1] == ind->SourcePANID.v[1]) && (myPANID.v[0] == ind->SourcePANID.v[0]))
	{	
		M_SendReceivedLoRaMessage(rxMessage.Payload[0]);
		
		
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


void M_BroadcastMessageToTerminal(uint8_t signal)
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
		sio2host_putchar(dataPtr[i]);
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
void M_SendReceivedUARTMessage(uint8_t message)
{
	printf("\n\r Send UART message %x \n", message);
	switch(message)
	{
		case TEAID_GCMD_RESET:
			break;
			
		case TEAID_GCMD_OPEN:
			ferryState = TEAID; 
			printf("\n Open gate at terminal A from IO \n\r");
			break;
			
		case TEAID_GCMD_CLOSE:
			printf("\n Close gate at terminal A from IO \n\r");
			break;
			
		case TEAID_GCMD_PAUSE:
			break;
			
		case TEBID_GCMD_RESET:
			break;
			
		case TEBID_GCMD_OPEN:
			ferryState = TEBID;
			printf("\n Open gate at terminal B from IO \n\r");
			break;
			
		case TEBID_GCMD_CLOSE:
			printf("\n Close gate at terminal B from IO \n\r");
			break;
			
		case TEBID_GCMD_PAUSE:
			break;
			
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
			
		case TEBID_FREQS_REQCNT:
			break;
		
		case TEBID_FREQS_REQDRDY:
			break;
		
		case TEBID_FREQS_REQGCLR:
			break;
		
		case TEBID_FREQS_GSREQ:
			break;
			
		case TEBID_FREQS_MSREQ:
			break;
			
		case TEAID_FPROC_DCOMP:
			if (s.front == TEAID_REQF_REQUEST)
			{
				pop_front(&s);
			}
			break;
			
		case TEAID_FPROC_BCOMP:
			ferryState = IN_TRANSIT;
			break;
			
		case TEBID_FPROC_DCOMP:
			if (s.front == TEBID_REQF_REQUEST)
			{
				pop_front(&s);
			}
			break;
			
		case TEBID_FPROC_BCOMP:
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
			
		case TEBID_FGS_TIMEOUT:
			break;
		
		case TEBID_FGS_OPEN:
			break;
			
		case TEBID_FGS_CLOSE:
			break;
		
		case TEBID_FGS_PAUSE:
			break;
			
		default: ;
			uint8_t send_message_again = SEND_MESSAGE_AGAIN;
			UART_SAM_To_IO(&send_message_again);
			return;
	}
	M_BroadcastMessageToTerminal(message);
}

// Send received LoRa message with UART
void M_SendReceivedLoRaMessage(uint8_t message)
{
	printf("\n\r Received message %x \n", message);
	// Checks if received message is meant for terminal A
	if (M_CheckIdentifier(message))
	{
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
				
			case TEBID_GSTATE_TIMEOUT:
				break;
			
			case TEBID_GSTATE_OPEN:
				break;
			
			case TEBID_GSTATE_CLOSE:
				break;
			
			case TEBID_GSTATE_PAUSE:
				break;
				
			case TEAID_DRDY_READY:
				break;
				
			case TEAID_DRDY_NREADY:
				break;
				
			case TEBID_DRDY_READY:
				break;
			
			case TEBID_DRDY_NREADY:
				break;
				
			case TEAID_GPCLEAR_READY:
				break;
			
			case TEAID_GPCLEAR_NREADY:
				break;
				
			case TEBID_GPCLEAR_READY:
				break;
			
			case TEBID_GPCLEAR_NREADY:
				break;
			
			case TEAID_MSTP_PUSHED:
				break;
				
			case TEBID_MSTP_PUSHED:
				break;
			
			case TEAID_MCMD_MOG:
				break;
			
			case TEAID_MCMD_MCG:
				break;
			
			case TEAID_MCMD_MOH:
				break;
			
			case TEAID_MCMD_MCH:
				break;
			
			case TEBID_MCMD_MOG:
				break;
			
			case TEBID_MCMD_MCG:
				break;
			
			case TEBID_MCMD_MOH:
				break;
			
			case TEBID_MCMD_MCH:
				break;
			
			case TEAID_REQF_REQUEST:
				processOrder(message, TEAID);
				printf("\n Received order from terminal A \n\r");
				break;
				
			case TEBID_REQF_REQUEST:
				processOrder(message, TEBID);
				printf("\n Received order from terminal B \n\r");
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
				break;
				
			case PASSENGERS_FIVE:
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
				
			default:
				M_BroadcastMessageToTerminal(SEND_MESSAGE_AGAIN);
				return;
		}
		UART_SAM_To_IO(&message);
	}
	else if (message == SEND_MESSAGE_AGAIN)
	{
		if (previousMessage)	// Send previous message if its not NULL
		{
			M_BroadcastMessageToTerminal(previousMessage[0]);
			printf("\n Send message again \n\r");
		}
	}
	else
	{
		//M_BroadcastMessageToTerminal(SEND_MESSAGE_AGAIN);
		return;
	}
}

bool M_CheckIdentifier(uint8_t LoRa_message)
{
	int MSB_LoRA_message = (LoRa_message & 0xC0);	// 2 MSB of received message
	
	return MSB_LoRA_message == FEID;				// Return true if identifier matches
}



void processOrder(uint8_t receivedOrder, uint8_t terminalIdentifier)
{
	
	switch (terminalIdentifier)
	{
		case TEAID:
			if (ferryState == TEAID)
			{
				uint8_t teaid_gcmd_open = TEAID_GCMD_OPEN;
				M_BroadcastMessageToTerminal(teaid_gcmd_open);
			}
			else
			{
				push_back(&s, receivedOrder);

				uint8_t terminal_A_conf = TEAID_CQUD_QCONF;
				
				// Send queue confirmed
				M_BroadcastMessageToTerminal(terminal_A_conf);
				
				UART_SAM_To_IO(&terminal_A_conf);
			}
			break;
		
		case TEBID:
			if (ferryState == TEBID)
			{
				uint8_t tebid_gcmd_open = TEBID_GCMD_OPEN;
				M_BroadcastMessageToTerminal(tebid_gcmd_open);
			}
			else
			{
				push_back(&s, receivedOrder);
				
				uint8_t terminal_B_conf = TEBID_CQUD_QCONF; 
				
				// send queue confirmed
				M_BroadcastMessageToTerminal(terminal_B_conf);

				UART_SAM_To_IO(&terminal_B_conf);
			}
			break;
		
		default:
			break;
	}
}
#endif // #if defined(PROTOCOL_P2P)
