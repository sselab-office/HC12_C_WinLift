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
* Notes:        
*
******************************************************************************/
#if !defined(APPTYPESH)	
#include	"usertypes.h"							/* header file for sample typedefs, defines etc. */
#else	/* !defined(APPTYPESH)	*/
#include	APPTYPESH								/* header file for sample typedefs, defines etc. */
#endif	/* !defined(APPTYPESH)	*/

/************************* System Include Files ******************************/
#if !defined(OSPROPH)	
#include	"osprop.h"							/* OS Properties */
#else	/* !defined(OSPROPH)	*/
#include	OSPROPH								/* OS Properties */
#endif	/* !defined(OSPROPH)	*/

#include <osapi.h>          /* API calls                                     */

#if !defined(OSCFGH)	
#include	"cfg.h"								/* Application configuration header file */
#else	/* !defined(OSCFGH)	*/
#include	OSCFGH								/* Application configuration header file */
#endif	/* !defined(OSCFGH)	*/

/************************* Project Include Files *****************************/
#include "winlift.h"  
#include "io.h"             /* register definitions from io.h                */

/************************* Declarations **************************************/
DeclareTask(ControlTask);		
DeclareTask(InputTask);
DeclareTask(MotorDriveTask);
DeclareTask(InitTask);
DeclareTask(LockTask);

DeclareCounter(SYSTEMTIMER);
			
DeclareAlarm(POLLINPUTS_AL);
DeclareAlarm(STATE_AL);
DeclareAlarm(INT_END_AL);
DeclareAlarm(REVERSE_AL);

DeclareEvent(KEY_EVENT);		//ControlTask
DeclareEvent(STATE_EVENT);
DeclareEvent(IRQ_EVENT);
DeclareEvent(INT_END_EVENT);
DeclareEvent(REVERSE_EVENT);

DeclareEvent(UP_EVENT);			//MotorDriveTask
DeclareEvent(DOWN_EVENT);
DeclareEvent(STOP_EVENT);

DeclareResource(Msg_Res);

/************************* typedefs ******************************************/


/************************* Global Variables **********************************/


/************************* #Defines ******************************************/


/******************************************************************************
Function Name	:	StartApplication
Engineer		:	D Brook / F Winters
Date			:	2/25/98

Parameters		:	none
Returns			:	none
Notes			:	Main entry point of the application. This routine starts
					the OS code.
******************************************************************************/
void
StartApplication(void)
{
	StartOS( appmode );		 /* jump to OSEKturbo OS 2.1 startup */
}

/******************************************************************************
Hook Name		:	StartupHook
Engineer		:	D Brook / F Winters
Date			:	2/25/98

Parameters		:	none
Returns			:	none
Notes			:	Start up hook. Called on initial operating system startup.
******************************************************************************/
void
StartupHook()   /* Start up hook */
{
	/* Set the direction port pins as input */
	DDRT   = PIN_INPUT;
	
	/* Set the direction port pins as output and stop the motor	*/
	PORTB |= M_STOP;
	DDRB  |= M_STOP;
	
	/* Set the direction port pins as output and unlock the door*/
	DDRA   = (O_UNLOCK | O_LOCK);
	PORTA  = O_UNLOCK;
	
	/* Set the direction port pin as output and ensure it is switched OFF*/
	LED_PORT |= STALL_LED;
}

/******************************************************************************
Task Name		:	InitTask
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	This task initiate the tasks, the counter and cyclic alarms
******************************************************************************/
TASK (InitTask)
{
	ActivateTask(ControlTask);		/*task aktivation*/
	ActivateTask(MotorDriveTask);	/*task aktivation*/

	InitCounter(SYSTEMTIMER,0);		/* init system timer    */
	SetRelAlarm(POLLINPUTS_AL,3,1);	/* set alarm for reading input keys */

	TerminateTask();				/*task terminate itself*/
}

/******************************************************************************
Task Name		:	InputTask
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	This task is set off by an Alarm and detects a key press
******************************************************************************/
TASK (InputTask)
{
static	char		OldStatus=0,toggel=0;
char				NewStatus;

	NewStatus = PORTT;
	
	if(toggel == 0)
		{
		PORTA &= ~O_RUN_LED;
		toggel = 1;
		}
	else
		{
		PORTA |= O_RUN_LED;
		toggel = 0;
		}
	
	
	if (OldStatus != NewStatus)	/*Have changed the state of the PORTT?*/
		{
		OldStatus 	= NewStatus;
		
		GetResource(Msg_Res);	
		input.port = OldStatus;
		SendMessage(Msg_Input,&input);
		ReleaseResource(Msg_Res);
		
		}
	TerminateTask();	/*task terminate itself*/
}


/******************************************************************************
Task Name		:	ControlTask
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	
******************************************************************************/
TASK (ControlTask)
{
static char			state = STATE_STOP;		/* state to drive the motor			*/
EventMaskType		event;
char				INPUT,lockDoor;

	for(;;)
		{
		WaitEvent (KEY_EVENT | STATE_EVENT | IRQ_EVENT | INT_END_EVENT | REVERSE_EVENT);
		GetEvent(ControlTask,&event);
		ClearEvent(event);
	
		GetResource(Msg_Res);
		ReceiveMessage(Msg_Input,&port_input);
		INPUT=port_input.port;
		ReleaseResource(Msg_Res);
			
			
		switch (state)//state machine
			{
			case STATE_CLOSE:
				if (!(INPUT & K_DOWN) || !(INPUT & K_TOP))//change the state if push the button "Dwn" or the window is close
					{
					CancelAlarm(STATE_AL);
					SetEvent(MotorDriveTask,STOP_EVENT);
					state = STATE_STOP;			//new state -> STOP
					}
				if (event & STATE_EVENT)		//change the state if the alarm "STATE_AL" is expire
					{
					SetEvent(MotorDriveTask,UP_EVENT);
					state = STATE_UP;			//new state -> UP
					}
				if (INPUT & K_UP)				//alarm "STATE_AL" will cancel if the button "Dwn" not more pushed
					{
					CancelAlarm(STATE_AL);
					}
				if (event & IRQ_EVENT)
					{														
					SetRelAlarm(REVERSE_AL,80,0);
					SetEvent(MotorDriveTask,DOWN_EVENT);
					LED_PORT &= ~STALL_LED;
					state = STATE_REVERSE;			//new state -> STALL
					}
				break;

			case STATE_UP:
				if (!(INPUT & K_DOWN) || !(INPUT & K_TOP) || (INPUT & K_UP))//change the state if push the button "Dwn"
					{														//or the window is close or the button "Up" is not push	
					SetEvent(MotorDriveTask,STOP_EVENT);
					state = STATE_STOP;			//new state -> STOP
					}
				if (event & IRQ_EVENT)
					{														
					SetRelAlarm(REVERSE_AL,80,0);
					SetEvent(MotorDriveTask,DOWN_EVENT);
					LED_PORT &= ~STALL_LED;
					state = STATE_REVERSE;			//new state -> STALL
					}
				break;

			case STATE_OPEN://state OPEN
				if (!(INPUT & K_UP) || !(INPUT & K_BOTTOM))//change the state if push the button "Up" or the window is open
					{
					CancelAlarm(STATE_AL);
					SetEvent(MotorDriveTask,STOP_EVENT);
					state = STATE_STOP;				//new state -> STOP
					}
				if (event & STATE_EVENT)			//change the state if the alarm "STATE_AL" is expire
					{
					SetEvent(MotorDriveTask,DOWN_EVENT);
					state = STATE_DOWN;				//new state -> DOWN
					}
				if (INPUT & K_DOWN)					//alarm "STATE_AL" will cancel if the button "Dwn" not more pushed
					{
					CancelAlarm(STATE_AL);
					}
				if (event & IRQ_EVENT)
					{														
					LED_PORT &= ~STALL_LED;
					state = STATE_STALL;			//new state -> STALL
					}
	
				break;
				
			case STATE_DOWN://state DOWN
				if (!(INPUT & K_UP) || !(INPUT & K_BOTTOM) || (INPUT & K_DOWN))//change the state if push the button "Up"
					{														   //or the window is open or the button "Dwn" is not push	
					SetEvent(MotorDriveTask,STOP_EVENT);
					state = STATE_STOP;					//new state -> STOP
					}
				if (event & IRQ_EVENT)
					{														
					LED_PORT &= ~STALL_LED;
					state = STATE_STALL;			//new state -> STALL
					}
				break;
	
			case STATE_STOP://state STOP
				if (!(INPUT & K_DOWN) && !(!(INPUT & K_BOTTOM ) || !(INPUT & K_UP)))//change the state if push the button "Dwn"
					{																//and if NOT (the window is open oder puch button "Up")
					SetRelAlarm(STATE_AL,40,0);
					SetEvent(MotorDriveTask,DOWN_EVENT);
					state = STATE_OPEN;					//new state -> OPEN
					}				
				
				if (!(INPUT & K_UP)&& !(!(INPUT & K_TOP ) || !(INPUT & K_DOWN)))//change the state if push the button "Up"
					{															//and if NOT (the window is close oder puch button "Dwn")
					SetRelAlarm(STATE_AL,40,0);
					SetEvent(MotorDriveTask,UP_EVENT);
					state = STATE_CLOSE;				//new state -> CLOSE
					}
				if (!(INPUT & K_LOCK))					//change the state if push the button "Lock"
					{
					SetEvent(MotorDriveTask,UP_EVENT);
					
					GetResource(Msg_Res);
					lockDoor= O_LOCK;
					SendMessage(Msg_Lock,&lockDoor);
					ReleaseResource(Msg_Res);
					
					state   = STATE_LOCK;				//new state -> LOCK
					}
				break;
		
			case STATE_LOCK://state LOCK
				if(!(INPUT & K_TOP))					//change the state if the window is close
					{
					SetEvent(MotorDriveTask,STOP_EVENT);
					state = STATE_LOCKED;				//new state -> LOCKED
					}
				if(!(INPUT & K_UNLOCK))					//change the state if push the button "Unlock"
					{
					state   = STATE_UNLOCK;
					SetEvent(MotorDriveTask,STOP_EVENT);
					
					GetResource(Msg_Res);
					lockDoor= O_UNLOCK;
					SendMessage(Msg_Lock,&lockDoor);
					ReleaseResource(Msg_Res);
					
					state   = STATE_STOP;				//new state -> STOP
					}
				if(event & IRQ_EVENT)					//change the state if the isr "StallInt" set the "INT_EVENT" event
					{														
					SetRelAlarm(REVERSE_AL,80,0);
					SetEvent(MotorDriveTask,DOWN_EVENT);
					
					GetResource(Msg_Res);
					lockDoor= O_UNLOCK;	
					SendMessage(Msg_Lock,&lockDoor);
					ReleaseResource(Msg_Res);
					
					LED_PORT &= ~STALL_LED;
					state = STATE_REVERSE;			//new state -> STALL
					}
				break;

			case STATE_LOCKED://state LOCKED
				if(!(INPUT & K_UNLOCK))					//change the state if push the button "Unlock"
					{
					state   = STATE_UNLOCK;				//new state -> UNLOCK
					
					GetResource(Msg_Res);
					lockDoor= O_UNLOCK;					
					SendMessage(Msg_Lock,&lockDoor);
					ReleaseResource(Msg_Res);
					
					state   = STATE_STOP;				//new state -> STOP
					}
				break;
			
			case STATE_REVERSE:
			 	if (event & REVERSE_EVENT)
					{
					state = STATE_STALL;
					SetEvent(MotorDriveTask,STOP_EVENT);
					}
				break;
				
			case STATE_STALL:
				if (event & INT_END_EVENT)
					{
					state = STATE_STOP;
					LED_PORT |= STALL_LED;
					}
				break;
			} /*end of switch (state)*/
		}/*end of for*/
}//end of TASK ControlTask
/******************************************************************************
Task Name		:	MotorDriveTask
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	This function, when called, will drive the window lift
					motor in the required direction.
******************************************************************************/
TASK (MotorDriveTask)
{
EventMaskType		event;

for ( ; ; )				/*endless loop*/
	{
	ClearEvent(UP_EVENT|DOWN_EVENT|STOP_EVENT);
	WaitEvent (UP_EVENT|DOWN_EVENT|STOP_EVENT);
	GetEvent(MotorDriveTask,&event);

	if (event & UP_EVENT)						//check the event which was set
		PORTB &= ~M_UP;							// window goes up

	if (event & DOWN_EVENT)
		PORTB &= ~M_DOWN;						// window goes down

	if (event & STOP_EVENT)
		PORTB |= M_STOP;						// window stop
	
	}/*end of endless loop*/
}//end of TASK MotorDriveTask
/******************************************************************************
Task Name		:	LockTask
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	This function, when called, will control the lock mechanism
					with the data from the message
******************************************************************************/
TASK (LockTask)
{
char				Door,LOCK_DOOR;
	
	GetResource(Msg_Res);
	ReceiveMessage(Msg_Lock,&Door);
	LOCK_DOOR=Door;
	ReleaseResource(Msg_Res);
	
	if(LOCK_DOOR & O_LOCK)
		PORTA = O_LOCK;								// lock the door
		
	if(LOCK_DOOR & O_UNLOCK)
		PORTA = O_UNLOCK;							// unlock the door
		
	TerminateTask();
}//end of TASK LockTask
/******************************************************************************
ISR Name		:	StallInt
Engineer		:	M Winge
Date			:	6/26/00

Parameters		:	none
Returns			:	none
Notes			:	stop the window lift motor
******************************************************************************/
ISR (StallInt)
{
PORTB |= M_STOP;						// window stop
SetEvent(ControlTask,IRQ_EVENT);
SetRelAlarm(INT_END_AL,500,0);
}//end of ISR StallInt 
