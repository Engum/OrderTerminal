

#ifndef CUSTOMCOMMANDSTERMINALFERRY_H
#define	CUSTOMCOMMANDSTERMINALFERRY_H

/* ---------------------------------------*/
/*	COMMANDS				PAYLOAD		  */
/* ---------------------------------------*/

// Ferry identifier
#define FEID						0xC0

// Terminal A identifier
#define TEAID						0x40

//Terminal B identifier
#define TEBID						0x80

// Ferry in transmit between terminals
#define IN_TRANSIT					0xA0

//* Gate states *//
/* Terminal A Timeout */
#define TEAID_GSTATE_TIMEOUT		0xD1

/* Terminal A Open */
#define TEAID_GSTATE_OPEN			0xD2

/* Terminal A Close */
#define TEAID_GSTATE_CLOSE			0xD3

/* Terminal A Pause */
#define TEAID_GSTATE_PAUSE			0xD4

/* Terminal B Timeout */
#define TEBID_GSTATE_TIMEOUT		0xE1

/* Terminal B Open */
#define TEBID_GSTATE_OPEN			0xE2

/* Terminal B Close */
#define TEBID_GSTATE_CLOSE			0xE3

/* Terminal B Pause */
#define TEBID_GSTATE_PAUSE			0xE4

//* Docking ready*//
/* Docking ready at terminal A */
#define TEAID_DRDY_READY			0xD5

/* Docking not ready at terminal A */
#define TEAID_DRDY_NREADY			0xD6

/* Docking ready at terminal B */
#define TEBID_DRDY_READY			0xE5

/* Docking not ready at terminal B */
#define TEBID_DRDY_NREADY			0xE6

//* Gap clear *//
/* Cap clear at terminal A */
#define TEAID_GPCLEAR_READY			0xD7

/* Cap not clear at terminal A */
#define TEAID_GPCLEAR_NREADY		0xD8

/* Cap clear at terminal B */
#define TEBID_GPCLEAR_READY			0xE7

/* Cap not clear at terminal B */
#define TEBID_GPCLEAR_NREADY		0xE8

//* Manual Stop*//
/* Manual stop pushed at terminal A */
#define TEAID_MSTP_PUSHED			0xD9

/* Manual stop pushed at terminal B */
#define TEBID_MSTP_PUSHED			0xE9


//* Manual Commands *//
/* Manual open gate at terminal A */
#define TEAID_MCMD_MOG				0xDA

/* Manual close gate at terminal A */
#define TEAID_MCMD_MCG				0xDB

/* Manual open hatch at terminal A */
#define TEAID_MCMD_MOH				0xDC

/* Manual close hatch at terminal A */
#define TEAID_MCMD_MCH				0xDD

/* Manual open gate at terminal B */
#define TEBID_MCMD_MOG				0xEA

/* Manual close gate at terminal B */
#define TEBID_MCMD_MCG				0xEB

/* Manual open hatch at terminal B */
#define TEBID_MCMD_MOH				0xEC

/* Manual close hatch at terminal B */
#define TEBID_MCMD_MCH				0xED


//* Gate commands for terminal A*//
/* Reset gate at terminal A */
#define TEAID_GCMD_RESET		0x71

/* Open gate at terminal A */
#define TEAID_GCMD_OPEN			0x72

/* Close gate at terminal A */
#define TEAID_GCMD_CLOSE		0x73

/* Pause gate at terminal A*/
#define TEAID_GCMD_PAUSE		0x74


//* Gate commands for terminal B*//
/* Reset gate at terminal B */
#define TEBID_GCMD_RESET		0xB1

/* Open gate at terminal B */
#define TEBID_GCMD_OPEN			0xB2

/* Close gate at terminal B */
#define TEBID_GCMD_CLOSE		0xB3

/* Pause gate at terminal B*/
#define TEBID_GCMD_PAUSE		0xB4


/* "On-demand" request from Terminal A */
#define TEAID_REQF_REQUEST		0xDE

/* "On-demand" request from Terminal B */
#define TEBID_REQF_REQUEST		0xEE

/* Queue update confirmed at Terminal A */
#define TEAID_CQUD_QCONF		0x75

/* Queue update confirmed at Terminal B */
#define TEBID_CQUD_QCONF		0xB5


//* Ferry Request States *//
/* Request people counter at terminal A */
#define TEAID_FREQS_REQCNT		0x76

/* Request docking ready at terminal A */
#define TEAID_FREQS_REQDRDY		0x77

/* Request gap clear at terminal A */
#define TEAID_FREQS_REQGCLR		0x78

/* Request gate state at terminal A */
#define TEAID_FREQS_GSREQ		0x79

/* Request manual stop button state at terminal A */
#define TEAID_FREQS_MSREQ		0x7A

/* Request people counter at terminal B */
#define TEBID_FREQS_REQCNT		0xB6

/* Request docking ready at terminal B */
#define TEBID_FREQS_REQDRDY		0xB7

/* Request gap clear at terminal B */
#define TEBID_FREQS_REQGCLR		0xB8

/* Request gate state at terminal B */
#define TEBID_FREQS_GSREQ		0xB9

/* Request manual stop button state at terminal B */
#define TEBID_FREQS_MSREQ		0xBA



//* Ferry Process *//
/* Docking complete at terminal A */
#define TEAID_FPROC_DCOMP		0x7B

/* Boarding complete at terminal A */
#define TEAID_FPROC_BCOMP		0x7C

/* Docking complete at terminal B */
#define TEBID_FPROC_DCOMP		0xBB

/* Boarding complete at terminal B */
#define TEBID_FPROC_BCOMP		0xBC


//* Ferry gate states *//
/* Ferry gate timeout to terminal A */
#define TEAID_FGS_TIMEOUT		0x7D

/* Ferry gate open to terminal A */
#define TEAID_FGS_OPEN			0x7E

/* Ferry gate close to terminal A */
#define TEAID_FGS_CLOSE			0x7F

/* Ferry gate pause to terminal B */
#define TEAID_FGS_PAUSE			0x70

/* Ferry gate timeout to terminal B */
#define TEBID_FGS_TIMEOUT		0xBD

/* Ferry gate open to terminal B */
#define TEBID_FGS_OPEN			0xBE

/* Ferry gate close to terminal B */
#define TEBID_FGS_CLOSE			0xBF

/* Ferry gate pause to terminal B */
#define TEBID_FGS_PAUSE			0xB0

/* People count */
#define PASSENGERS_ZERO			0x00
#define PASSENGERS_ONE			0x01
#define PASSENGERS_TWO			0x02
#define PASSENGERS_THREE		0x03
#define PASSENGERS_FOUR			0x04
#define PASSENGERS_FIVE			0x05
#define PASSENGERS_SIX			0x06
#define PASSENGERS_SEVEN		0x07
#define PASSENGERS_EIGHT		0x08
#define PASSENGERS_NINE			0x09
#define PASSENGERS_TEN			0x0A
#define PASSENGERS_ELEVEN		0x0B
#define PASSENGERS_TWELVE		0x0C
#define PASSENGERS_THRITEEN		0x0D
#define PASSENGERS_FOURTEEN		0x0E
#define PASSENGERS_FIFTEEN		0x0F

/* Send previous message again*/
#define SEND_MESSAGE_AGAIN			0xAA




#endif