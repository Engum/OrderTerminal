
#ifndef LORA_P2P_TERMINAL_H
#define LORA_P2P_TERMINAL_H

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
* Function: T_BroadcastMessageToFerry(uint8_t signal)

* Overview: Allocates memory space and broadcasts signal
*
* Input:  Signal to send
*
* Output: None
*
********************************************************************/
void T_BroadcastMessageToFerry(uint8_t signal);

/*********************************************************************
* Function: void T_SendReceivedUARTMessage(uint8_t message)
*
* Overview: Send received UART message to ferry
*
* PreCondition:
*
* Input:  Message to send
*
* Output: None
*
********************************************************************/
void T_SendReceivedUARTMessage(uint8_t message);

/*********************************************************************
* Function: void T_SendReceivedLoRaMessage(uint8_t message)
*
* Overview: Send received RF message to gate or other source with UART
*
* PreCondition: 

* Input:  Received RF message
*
* Output: None
*
********************************************************************/
void T_SendReceivedLoRaMessage(uint8_t message);

/*********************************************************************
* Function: bool T_A_CheckIdentifier(uint8_t message)
*
* Overview: Check if received RF signal is meant for terminal A
*
* PreCondition:
*
* Input:  Received LoRa message
*
* Output: True if received LoRa message is for terminal A
*
********************************************************************/
bool T_A_CheckIdentifier(uint8_t LoRa_message);

/*********************************************************************
* Function: bool T_B_CheckIdentifier(uint8_t message)
*
* Overview: Check if received RF signal is meant for terminal A
*
* PreCondition:
*
* Input:  Received LoRa message
*
* Output: True if received LoRa message is for terminal A
*
********************************************************************/
bool T_B_CheckIdentifier(uint8_t LoRa_message);

/*********************************************************************
* Function: bool M_CheckIdentifier(uint8_t LoRa_message);
*
* Overview: Check if received RF signal is meant for ferry
*
* PreCondition:
*
* Input:  Received LoRa message
*
* Output: True if received LoRa message is for ferry
*
********************************************************************/
bool M_CheckIdentifier(uint8_t LoRa_message);

/*********************************************************************
* Function: void T_B_OnDemandOrder(void);
*
* Overview: Order ferry if button has been pressed
*
* PreCondition:
*
* Input:
*
* Output:
*
********************************************************************/
void T_B_OnDemandOrder(void);

/*********************************************************************
* Function: void init_order_button(void);
*
* Overview: Initialize pin PA07 as input to register for button press
*
* PreCondition:
*
* Input:
*
* Output:
*
********************************************************************/
void init_order_button(void);

/*********************************************************************
* Function: void init_LED_order_button(void);
*
* Overview: Initialize pin PA06 as output to ignite LED on button
*
* PreCondition:
*
* Input:
*
* Output:
*
********************************************************************/
void init_LED_order_button(void);

#endif	/* P2P_DEMO_H */
