/******************************************************************************
*
*       Copyright (C) 2000-2001 Metrowerks, Inc.
*       All Rights Reserved
*
*       You can use this example for any purpose on any computer system with
*       the following restrictions:
*
*       1. This example is provided "as is", without warranty.
*
*       2. You don't remove this copyright notice from this example or any
*          direct derivation thereof.
*
* Description:  OSEK OS sample application
*
* Notes:  Header file for Window lift training exercise.      
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/************************* #Defines ******************************************/
#define	PIN_INPUT		0x00

#define K_UP			0x01                   /*  Bit masks for key inputs			*/
#define K_DOWN			0x02
#define K_LOCK			0x10    
#define K_UNLOCK		0x20
#define K_TOP			0x40
#define K_BOTTOM		0x80

#define M_UP			0x40					/* Bit masks for motor operation	*/
#define M_DOWN			0x80
#define M_STOP			0xC0

#define	O_LOCK			0x02
#define	O_UNLOCK		0x01

#define STALL_LED		0x02					/* Bit masks for LED	*/
#define O_RUN_LED		0x04

#define STATE_STOP		0x00					/* Values for state table			*/
#define STATE_UP		0x01
#define STATE_DOWN		0x02
#define STATE_CLOSE		0x03
#define STATE_OPEN		0x04
#define STATE_LOCK		0x05
#define	STATE_UNLOCK	0x06
#define STATE_LOCKED	0x07
#define STATE_STALL		0x08
#define STATE_REVERSE	0x09



#ifdef __cplusplus
}
#endif



/************************* Prototypes ****************************************/
//void		StartUserThread(void);					/* main thread of the OS				*/
