/******************************************************************************
*
*       Copyright (C) 2000-2001 Metrowerks, Inc.
*       All Rights Reserved
*
*       You can use this example for any purpose on any computer system with the
*       following restrictions:
*
*       1. This example is provided "as is", without warranty.
*
*       2. You don't remove this copyright notice from this example or any direct
*          derivation thereof.
*
* Description:  This file defines data structures that areapplication specific 
                but refered to by the OSEK (e.g. Message types) 
*
* Notes:        
*
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/************************* typedefs ******************************************/
/* structure and typedef for OS message	*/
typedef struct	MSG_Port_State	MSG_PState;
struct MSG_Port_State
{
	char	port;
};

#ifdef __cplusplus
}
#endif
