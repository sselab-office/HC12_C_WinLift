#define OSCFG_C
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
*       : 1.17 $ : takrte : 2001/06/22 09:13:26 : 2001/06/22 09:13:26 $
*
* Note: The implementation was used: OSEKturbo_OS12_2_1_1_27
*		OSEK System generator Target Specific DLL - Version: 2.1.27
*
******************************************************************************/
#if	!defined(OSPROPH)
#include	"osprop.h"								/* OS Properties */
#else	/*	!defined(OSPROPH)	*/
#include	OSPROPH								/* OS Properties */
#endif	/*	!defined(OSPROPH)	*/

#include	<osapi.h>

#if defined(APPTYPESH)
#include APPTYPESH								/* user's header file */
#endif	/* defined(APPTYPESH) */

#if	!defined(OSCFGH)
#include	"cfg.h"								/* definitions for system objects */
#else	/*	!defined(OSCFGH)		*/
#include	OSCFGH								/* definitions for system objects */
#endif	/*	!defined(OSCFGH)		*/

/*  Tasks' entry points */

const   OSTASKENTRY         OsTaskEntry[OSNTSKS] = 
{
    0,                                          /* free to use  */      
    FuncMotorDriveTask,                                  /* MotorDriveTask    */
    FuncControlTask,                                  /* ControlTask    */
    FuncInitTask,                                  /* InitTask    */
    FuncInputTask,                                  /* InputTask    */
    FuncLockTask,                                  /* LockTask    */
};

/*  Tasks' base priorities  */

const   OSTASKPRIO          OsTaskBasePrio[OSNTSKS] =
{
    0,                                          /* must be lowest priority (zero)   */      
    3,                                          /* MotorDriveTask    */
    4,                                          /* ControlTask    */
    6,                                          /* InitTask    */
    1,                                          /* InputTask    */
    2,                                          /* LockTask    */
};

/*  Tasks' properties   */

const   OSBYTE              OsTaskProperty[OSNTSKS] =
{
    0,                                              /* MUST BE ZERO */
	OSTSKEXTENDED,			/* MotorDriveTask    */
	OSTSKEXTENDED,			/* ControlTask    */
	0|OSTSKACTIVATE|OSTSKNONPREEMPT,			/* InitTask    */
	0,			/* InputTask    */
	0,			/* LockTask    */
};

/*  Tasks' active priorities    */

        OSTASKPRIO          OsTaskPrio[OSNTSKS];

/*  Tasks' links    */

        TaskType            OsTaskLink[OSNTSKS];

/* Tasks' current stack pointer.    */

OSBYTE*             OsTaskSP[OSNTSKS];          

/* Tasks' status. */

OSBYTE              OsTaskStatus[OSNTSKS];  

/* Tasks' top of stacks.    */

const   OSBYTE* const       OsTaskTOS[OSNXTSKS+1] = 
{
    0,                                              /* Free to use  */      
    OSGETTOPOFCTX(OsMotorDriveTaskStack,OSMotorDriveTaskSTKSIZE),     /* MotorDriveTask    */
    OSGETTOPOFCTX(OsControlTaskStack,OSControlTaskSTKSIZE),     /* ControlTask    */
};          

const   OSBYTE* const       OsTaskBOS[OSNXTSKS+1] =
{
    0,                                              /* Free to use  */      
    OsMotorDriveTaskStack,                                 /* MotorDriveTask    */
    OsControlTaskStack,                                 /* ControlTask    */
};
/* Ext. Tasks' mask of waiting events.  */

EventMaskType       OsTaskWaitEvent[OSNXTSKS];  

/* Ext. Tasks' mask of set events.      */

EventMaskType       OsTaskSetEvent[OSNXTSKS];   

 /* OSNXTSKS > 0 */
/* Task's stacks    */

OSBYTE              OsMotorDriveTaskStack[OSMotorDriveTaskSTKSIZE];
OSBYTE              OsControlTaskStack[OSControlTaskSTKSIZE];

/*  Resources' priorities   */

const   OSTASKPRIO          OsResPrio[OSNRESS] =
{
    254,                                        /* Scheduler priority   */
	5,                                          /* Msg_Res */
};

/*  Resources' saved priorities of tasks    */

OSTASKPRIO          OsResSave[OSNRESS];

/*  Counters' and Timers' links */

AlarmType          OsCtrLink[OSNCTRS];

/*  Counters' and Timers' maxallowedvalue   */

const   TickType            OsCtrMax[OSNCTRS] =
{
    0xFFFF,                                        /* SYSTEMTIMER */
};

/* Counters' and Timers' ticksperbase.  */

const   TickType            OsCtrBase[OSNCTRS] =
{
    10,                                          /* SYSTEMTIMER */
};                      


#if OSNCTRS > OSNHWCTRS
TickType    OsCtrValue[OSNCTRS-OSNHWCTRS];    /* SW Counter's value */
#endif


/*  Alarms' links (for list of alarms)  */

        AlarmType           OsAlmLink[OSNALMS];

/*  Alarms' counters attached to    */

const   CtrType             OsAlmCtr[OSNALMS] = 
{
    SYSTEMTIMER,                                       /* STATE_AL */
    SYSTEMTIMER,                                       /* POLLINPUTS_AL */
    SYSTEMTIMER,                                       /* INT_END_AL */
    SYSTEMTIMER,                                       /* REVERSE_AL */
};

/*  Alarms' attached tasks  */

const   TaskType            OsAlmTask[OSNALMS] = 
{
    ControlTask,                                      /* STATE_AL */
    InputTask,                                      /* POLLINPUTS_AL */
    ControlTask,                                      /* INT_END_AL */
    ControlTask,                                      /* REVERSE_AL */
};

/* Alarms' event mask to be set.        */

const   EventMaskType       OsAlmSetEvent[OSNALMS] =
{
    STATE_EVENT,                                          /* STATE_AL */
    0,                                          /* POLLINPUTS_AL */
    INT_END_EVENT,                                          /* INT_END_AL */
    REVERSE_EVENT,                                          /* REVERSE_AL */
};      

/*  Alarms' delta values    */

        TickType            OsAlmValue[OSNALMS];

/*  Alarms' cycle values    */

        TickType            OsAlmCycle[OSNALMS];

   

/* Messages objects definition  */

MSG_PState	OSMsg_InputObject;

char	OSMsg_LockObject;

/* Message objects copies definition  */

char	OSLOCK_SMsg_LockObject;


const void*    const         OsMsgPtr[OSNMSGS] =          /* pointers to messages bodies */
{
    &OSMsg_InputObject,
    &OSMsg_LockObject,
};

const    int                 OsMsgSize[OSNMSGS] =         /* size of messages in bytes */
{
	sizeof(MSG_PState),
	sizeof(char),
};

#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT)
const    TaskType            OsSigTask[OSNMSGS] =         /* Tasks to be signaled */
{
	ControlTask,
	LockTask,
};
#endif

#if defined(OSSIGEVENT)
const    EventMaskType       OsSigEvent[OSNMSGS] =        /* Events to be set */
{
	KEY_EVENT,
	0 ,
};
#endif

#if defined(OSSIGCALLBACK)
const    OSCALLBACK          OsSigCallBack[OSNMSGS] =     /* to be called in SendMessage */
{
	0 ,
	0 ,
};
#endif




/* Stack Labels   */

#if	defined(OSCOSMIC) || defined(OSCOSMIC12)
void  os_stack_labels()
{
_asm("xdef _MotorDriveTask_BOS\n_MotorDriveTask_BOS:      equ _OsMotorDriveTaskStack\n");
_asm("xdef _MotorDriveTask_TOS\n_MotorDriveTask_TOS:      equ _OsMotorDriveTaskStack+101\n");

_asm("xdef _ControlTask_BOS\n_ControlTask_BOS:      equ _OsControlTaskStack\n");
_asm("xdef _ControlTask_TOS\n_ControlTask_TOS:      equ _OsControlTaskStack+101\n");

}
#endif
