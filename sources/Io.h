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

#ifndef IO_H
#define IO_H


/************************* System Include Files ******************************/
#include <6812A4.h>

/************************* Project Include Files *****************************/


/************************* typedefs ******************************************/


/************************* Global Variables **********************************/


/************************* #Defines ******************************************/

#define LED_PORT (*(volatile char *)0x0029 )


#endif /* IO_H */
