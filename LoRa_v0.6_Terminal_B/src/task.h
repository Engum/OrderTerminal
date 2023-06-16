/**
* \file  task.h
*
* \brief Interface of Tasks for Demo Application on MiWi P2P 
*
* Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries. 
*
* \asf_license_start
*
* \page License
*
* Subject to your compliance with these terms, you may use Microchip
* software and any derivatives exclusively with Microchip products. 
* It is your responsibility to comply with third party license terms applicable 
* to your use of third party software (including open source software) that 
* may accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, 
* WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, 
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, 
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE 
* LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL 
* LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE 
* SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY 
* RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
* \asf_license_stop
*
*/

#ifndef TASK_H
#define	TASK_H

#include "system.h"

#include "miwi_api.h"
#include "demo_output.h"


/*********************************************************************
* Function: void Initialize_Demo(void)
*
* Overview: MAC Layer Protocol Initialization , Ch selection and Network Roles 
 *                  Pan Co or End Device In case of Star
 *              
*
* PreCondition: Hardware_Init()
*
* Input:  None
*
* Output:None 
*           
********************************************************************/
bool Initialize_LoRa(bool freezer_enable);

/*********************************************************************
* Function: void Run_Communication(void)
*
* Overview: Start P2p or Star Demo depending on the protocol chosen in
*                 miwi_config.h
*
* PreCondition: Hardware_Init && Demo_Init
*
* Input:  None
*
* Output:None
*
********************************************************************/
void Run_Communication(void);

extern uint8_t TxTimerId;

#endif	/* TASK_H */

