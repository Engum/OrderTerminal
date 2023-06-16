
#ifndef LORA_P2P_MODEM_H
#define LORA_P2P_MODEM_H

/*********************************************************************
* Function: void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
*
* Overview: Process a Received Message
*
* PreCondition: MiApp_ProtocolInit
*
* Input:  None
*
* Output: None
*
********************************************************************/
void ReceivedDataIndication (RECEIVED_MESSAGE *ind);

/*********************************************************************
* Function: void TxToutCallback(void)
*
* Overview: Transmission timeout callback to bring the node back to continious transaction cycle
*
* PreCondition: MiApp_ProtocolInit
*
* Input:  None
*
* Output: None
*
********************************************************************/
void TxToutCallback(void);

/*********************************************************************
* Function: void dataConfcb(uint8_t handle, miwi_status_t status, uint8_t* msgPointer)
*
* Overview: Callback routine which will be called upon the initiated data procedure is performed
*
* PreCondition: MiApp_ProtocolInit
*
* Input:  None
*
* Output: None
*
********************************************************************/
void dataConfcb(uint8_t handle, miwi_status_t status, uint8_t* msgPointer);

/*********************************************************************
* Function: void M_BroadcastMessageToFeryy(uint8_t signal)

* Overview: Allocates memory space and broadcasts signal
*
* Input:  Signal to send
*
* Output: None
*
********************************************************************/
void M_BroadcastMessageToTerminal(uint8_t signal);

/*********************************************************************
* Function: void M_SendReceivedUARTMessage(uint8_t message);
*
* Overview: Send received UART message to terminal
*
* PreCondition: 
*
* Input:  Message to send
*
* Output: None
*
********************************************************************/
void M_SendReceivedUARTMessage(uint8_t message);

/*********************************************************************
* Function: void M_SendReceivedLoRaMessage(uint8_t message);
*
* Overview: Send received RF message to gate or other source with UART
*
* PreCondition: 

* Input:  Received RF message
*
* Output: None
*
********************************************************************/
void M_SendReceivedLoRaMessage(uint8_t message);


/*********************************************************************
* Function: bool M_CheckIdentifier(uint8_t LoRa_message);
*
* Overview: Check if received RF signal is meant for ferry
*
* PreCondition: MiApp_ProtocolInit
*
* Input:  Received LoRa message
*
* Output: True if received LoRa message is for ferry
*
********************************************************************/
bool M_CheckIdentifier(uint8_t LoRa_message);


/*********************************************************************
* Function: void processOrder(uint8_t receivedOrder, uint8_t terminalIdentifier);
*
* Overview: Opens gate or updates queue based on ferry state
*
* PreCondition: 
*
* Input:
	receivedOrder: Which terminal has ordered the ferry
	terminalIdentifier: Which terminal did the order come from
*
* Output: None
*
********************************************************************/
void processOrder(uint8_t receivedOrder, uint8_t terminalIdentifier);






#endif	/* P2P_DEMO_H */
