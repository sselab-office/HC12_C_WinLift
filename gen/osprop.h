#ifndef OSPROP_H
#define OSPROP_H
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
*       : 1.17 $ : takrte : 2001/06/22 09:13:30 : 2001/06/22 09:13:30 $
*
* Note: The implementation was used: OSEKturbo_OS12_2_1_1_27
*		OSEK System generator Target Specific DLL - Version: 2.1.27
*
******************************************************************************/


/*	Target MCU	*/
#define 	OSHC12
#undef  	OSHC08

#ifndef		OSHC12BC32
#define 	OSHC12BC32
#endif

/*	OS version	*/

#define		OSVERSION21
#undef OSNOBUILDNUMBER

/* Conformance Class */

#undef  	OSBCC1
#define 	OSECC1

/* Scheduler Policy */

#undef  	OSNOPREEMPT
#define 	OSMIXPREEMPT
#undef  	OSFULLPREEMPT

/* Local Communications only  */

#define LOCALMESSAGESONLY

#define OSHCBASEPAGE                          /* The direct addressing is used for the system variables */
#undef OSHCLOWPOWER                          /* The scheduler uses low power consumption during idle loop */

#undef OSRESOURCEISR                            /* ISRs use resource mechanism */

#define OSRES_SCHEDULER                         /* RESOURCE RES_SCHEDULER access */

#undef OSEXTSTATUS                             /* Work in extended API return status */


#define OSORTIDEBUGLEVEL    2                       /* may be 0 or 1 - static ORTI only */
#undef OSSTKCHECK                            /* Run-time checking of stack overflow */

/* Hook routines */

#undef  	OSHOOKERROR 				/* User-supplied OS hook for error handling is used	*/
#undef  	OSHOOKPRETASK 				/* User-supplied OS hook for task switching monitoring is used (pre-task hook)	*/
#undef  	OSHOOKPOSTTASK 				/* User-supplied OS hook for task switching monitoring is used (post-task hook)	*/
#define 	OSHOOKSTARTUP 				/* User-supplied OS hook for startup is used	*/
#undef  	OSHOOKSHUTDOWN 				/* User-supplied OS hook for shutdown is used	*/
#undef  	OSHOOKSCHEDULER				/* User-supplied OS hook for scheduler idle loop is used */

#undef OSALMHOOK                               /* Alarm hook is supported */

/* ISRs categories support */

#define OSNOISR1                                /* ISR category 1 is absent */
#undef OSNOISR2                                /* ISR category 2 is absent */
#define OSNOISR3                                /* ISR category 3 is absent */

/* Interrupt management */

#define 	OSISRENTRYEXIT 						/* ISR entry/exit frames must be implemented */

#define OSISRSTACKSIZE 64

/* Events mechanism */

#define OSEVENT8                                /* Up to 8 events are supported */

/* Communication mechanism */

#if defined (LOCALMESSAGESONLY)
#define OSSTATEMSG                              /* State messages are supported */

#define OSSIGACTIVTASK                          /* Task activation is supported by a message */
#define OSSIGEVENT                              /* Event notification is supported by a message */
#undef OSSIGCALLBACK                           /* Callback method is supported by a message */
#endif  /* LOCALMESSAGESONLY */

/* Counters and Alarms mechanisms */

#undef OSHWCOUNTER
#define OSNHWCTRS 0
#define OSSYSTIMER
#undef OSSECONDTIMER
/* Timer hardware type */
#define OSTIMRTI

#define OSTIMPRESCALER 1

#define OSALMSETEVENT                          /* Event notification is supported by an alarm */

/* Configuration constants  */

#define OSNTSKS     6                           /* number of all tasks plus 1                       */
                                                /* (zero-task is reserved for list of ready tasks)  */

#define OSNXTSKS    2                           /* number of extended tasks                         */
                                                /* included into number of all tasks                */
                                                /* must be 0 for BCC                                */

#define OSNRESS     2                           /* number of resources     */
#define OSNISRRESS  0                           /* number of ISR resources     */

#define OSRESOURCE

#define OSNCTRS     1                           /* number of counters  */
                     
#define OSCOUNTER

#define OSNALMS     4                           /* number of alarms */

#define OSALARM

#if defined (LOCALMESSAGESONLY)
#define OSNMSGS		2                           /* number of messages */

#define OSMESSAGE
#endif  /* LOCALMESSAGESONLY */

/* Application modes */

#define appmode      OSDEFAULTAPPMODE

#undef OSTIMESCALE

#define         INITIAL_INTERRUPT_DESCRIPTOR    0

#endif /* OSPROP_H */
