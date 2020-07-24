#ifndef OSCFG_H
#define OSCFG_H
/******************************************************************************
*
*       Copyright (C) 2001 Motorola, Inc.
*       All Rights Reserved
*
*       The code is the property of Motorola St.Petersburg Software Development
*       and is Motorola Confidential Proprietary Information.
*
*       The copyright notice above does not evidence any
*       actual or intended publication of such source code.
*
*       : 1.17 $ : takrte : 2001/06/22 09:13:28 : 2001/06/22 09:13:28 $
*
* Note: The implementation was used: OSEKturbo_OS12_2_1_1_27
*		OSEK System generator Target Specific DLL - Version: 2.1.27
*
******************************************************************************/


/*  Task identifications    */
    /* Extended tasks MUST have lower numbers then Basic ! */

#define MotorDriveTask		1
void        FuncMotorDriveTask(void);			/* Task MotorDriveTask entry point */

#define ControlTask		2
void        FuncControlTask(void);			/* Task ControlTask entry point */

#define InitTask		3
void        FuncInitTask(void);			/* Task InitTask entry point */

#define InputTask		4
void        FuncInputTask(void);			/* Task InputTask entry point */

#define LockTask		5
void        FuncLockTask(void);			/* Task LockTask entry point */



/* Stacks definitions  */

#define OSMotorDriveTaskSTKSIZE  101
extern          OSBYTE              OsMotorDriveTaskStack[OSMotorDriveTaskSTKSIZE];
#define OSControlTaskSTKSIZE  101
extern          OSBYTE              OsControlTaskStack[OSControlTaskSTKSIZE];

extern const   OSBYTE* const       OsTaskBOS[OSNXTSKS+1];

extern const   OSBYTE* const       OsTaskTOS[OSNXTSKS+1];

/* Events   */

#define STATE_EVENT      0x1
#define UP_EVENT      0x1
#define STOP_EVENT      0x2
#define KEY_EVENT      0x2
#define DOWN_EVENT      0x4
#define IRQ_EVENT      0x4
#define INT_END_EVENT      0x8
#define REVERSE_EVENT      0x10


/* ISR definitions    */

#define   StallIntId     3

extern 		OSINTERRUPT         StallInt(void);
#define 	OSISRStallInt()            OSISR2(StallInt)

/*  Resource identification */

#define RES_SCHEDULER	0                   /* Resource-scheduler */
#define Msg_Res 	1

#define Msg_ResPRIO    5

/*  Counters identification */

#define SYSTEMTIMER        0

#define OSMINCYCLE        0
#define OSMAXALLOWEDVALUE 0xFFFF
#define OSTICKSPERBASE    10
#define OSTICKDURATION    2048000

/*  Alarms identification   */

#define STATE_AL        0
#define POLLINPUTS_AL        1
#define INT_END_AL        2
#define REVERSE_AL        3

/* Alarm Hooks prototypes   */

#if defined (LOCALMESSAGESONLY)

/* Messages identification  */

#define Msg_Input		0
#define Msg_Lock		1

extern MSG_PState	OSMsg_InputObject;

extern char	OSMsg_LockObject;

/*  Message copies of send accessors   */

extern char	OSLOCK_SMsg_LockObject;

/*	Send Accessors		*/

#define input	OSMsg_InputObject

#define LOCK_S	OSLOCK_SMsg_LockObject

/*  Message copies of receive accessors   */

/*	Receive Accessors		*/

#define port_input	OSMsg_InputObject

#define LOCK	OSMsg_LockObject

/* Message callback prototypes  */


#endif /* LOCALMESSAGESONLY */
#endif /* OSCFG_H */
