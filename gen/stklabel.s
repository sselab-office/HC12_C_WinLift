;******************************************************************************
;
;       Copyright (C) 2001 Motorola, Inc.
;       All Rights Reserved
;
;       The code is the property of Motorola St.Petersburg Software Development
;       and is Motorola Confidential Proprietary Information.
;
;       The copyright notice above does not evidence any
;       actual or intended publication of such source code.
;
;       : 1.11 $ : takrte : 2001/06/22 09:13:34 : 2001/06/22 09:13:34 $
;
; Note: The implementation was used: OSEKturbo_OS12_2_1_1_27
;		OSEK System generator Target Specific DLL - Version: 2.1.27
;
;******************************************************************************

;  Stack Labels

		XREF	OsMotorDriveTaskStack
		XDEF MotorDriveTask_BOS
MotorDriveTask_BOS:      EQU OsMotorDriveTaskStack
		XDEF MotorDriveTask_TOS
MotorDriveTask_TOS:      EQU OsMotorDriveTaskStack+101

		XREF	OsControlTaskStack
		XDEF ControlTask_BOS
ControlTask_BOS:      EQU OsControlTaskStack
		XDEF ControlTask_TOS
ControlTask_TOS:      EQU OsControlTaskStack+101

