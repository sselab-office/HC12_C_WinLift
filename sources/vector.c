#define VECTOR_C
/******************************************************************************
*
*       Copyright (C) 2000 Motorola, Inc.
*       All Rights Reserved
*
*       The code is the property of Motorola St.Petersburg Software Development
*       and is Motorola Confidential Proprietary Information.
*
*       The copyright notice above does not evidence any
*       actual or intended publication of such source code.
*
* Filename:     $Source: /u/hiware/install/image_files/HC12/(CodeWarrior_Examples)/HC12/HC12\040SIMULATOR/HC12\040C_WinLift/sources/vector.c,v $
* Author:       $Author: estyger $
* Locker:       $Locker:  $
* State:        $State: Exp $
* Revision:     $Revision: 1.1.1.1 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*               03Dec96 Created from Cosmic sample. (cmp)
*
* Description:  Vector table for HC12
*
* Notes:        1.  The only one of the following variables may be defined, while
*                   all others are undefined. This is controlled by the compiler
*                   option, which in turn is to be adjusted in 'makefile' or batch
*                   file:
*                       OSHC12D60       M68EVB912D60 is used
*                       OSHC12BC32      M68HC12BC32EVB is used
*                       OSHC12D128      M68EVB912D60 with DA128 chip is used
*
******************************************************************************/

#if !defined(OSPROPH)   
#include    <osprop.h>                          /* OS Properties */
#else   /* !defined(OSPROPH) */
#include    OSPROPH                             /* OS Properties */
#endif  /* !defined(OSPROPH) */

#include    <osapi.h>                           /* OSEK API */

                                                /* for HC12 */
/************************* Declarations **************************************/
DeclareISR(StallInt);

/*            INTERRUPT VECTORS TABLE                    */



#if !defined(NULL)
#define NULL    0
#endif 
#if !defined(OSINITRM)
#define OSINITRM        0x10                    /* RAM mapping register */
#endif
#if !defined(OSINITRG)
#define OSINITRG        0x11                    /* Register Block mapping register */
#endif

#if defined(OSHICROSS12)
#define OSVECTF ( void ( *const __osdecl )( ) ) /* Vector table function specifier */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
#define OSVECTF ( void *const )                 /* Vector table function specifier */
#endif  /* defined(OSCOSMIC12) */

#define OSFUNC void __osdecl                    /* Function declare specifier */

                                                /* Vector table declare specifier */
#define OSVECTAB OSFUNC ( * const __osdecl _vectab[] )( )


#if defined(OSHICROSS12)
extern OSFUNC _Startup( void );                 /* startup routine for Hiware compiler */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
extern OSFUNC _stext( );                        /* startup routine for Cosmic compiler */
#endif  /* defined(OSCOSMIC12)  */

/***************************************************************************
 * Function : _dummyISR( )
 *
 * Description: dummy interrupt handler
 *
 * Returns: no returns value
 *
 * Notes:
 *
 **************************************************************************/

OSINTERRUPT _dummyISR( void )
{
    while( 1 );                                 /* endless cycle */
}
                                                /* Start-up module to initialize RAM/REGISTERS area */
#if defined(OSHICROSS12)

#if defined(_BASE) || defined(_BASERAM)

#pragma NO_FRAME
#pragma NO_ENTRY
#pragma NO_EXIT

/***************************************************************************
 * Function : _StartupInitRAMREG( )
 *
 * Description: HI-CROSS+ pre-startup function
 *              to initialize RAM/REGISTERS area
 *
 * Returns: no returns value
 *
 * Notes:
 *
 **************************************************************************/

OSFUNC _StartupInitRAMREG( void )
{
#if defined(_BASERAM)
                                                /* fisrt step: Initialize INITRM register (RAM allocation) */
    ( *( (OSNEAR volatile OSBYTEPTR)OSINITRM ) ) = ( _BASERAM>>8 )&0xF8;
#endif  /*  defined(_BASERAM)   */
#if defined(_BASE)
                                                /* last step: initialize INITRG registers (I/O registers allocation) */
    ( *( (OSNEAR volatile OSBYTEPTR)OSINITRG ) ) = ( _BASE>>8 )&0xF8;
#endif  /* defined(_BASE) */
                                                /* Jump to normal startup */
    asm{
        jmp _Startup
    }
}

#endif  /* defined(_BASE) || defined(_BASERAM) */

#endif  /* defined(OSHICROSS12) */

#if defined(OSCOSMIC12)

#if defined(_BASE) || defined(_BASERAM)

/***************************************************************************
 * Function : _StartupInitRAMREG( )
 *
 * Description: Cosmic pre-startup function
 *              to initialize RAM/REGISTERS area
 *
 * Returns: no returns value
 *
 * Notes:
 *
 **************************************************************************/

OSFUNC _StartupInitRAMREG( void )
{
#if defined(_BASERAM)
                                                /* fisrt step: Initialize INITRM register (RAM allocation) */
    ( *( (OSNEAR volatile OSBYTEPTR)OSINITRM ) ) = ( _BASERAM >> 8 ) & 0xF8;
#endif  /*  defined(_BASERAM)   */
#if defined(_BASE)
                                                /* last step: initialize INITRG registers (I/O registers allocation) */
    ( *( (OSNEAR volatile OSBYTEPTR)OSINITRG ) ) = ( _BASE >> 8 ) & 0xF8;
#endif  /* defined(_BASE) */
                                                /* Jump to normal startup */
    _asm("xref  __stext\n");
    _asm("jmp   __stext\n");
}

#endif  /* defined(_BASE) || defined(_BASERAM) */

#endif  /* defined(OSCOSMIC12) */


/***************************************************************************/
/* OSHC12A4 */
/***************************************************************************/


/***************************************************************************/
/* OSHC12D60 */
/***************************************************************************/

#if defined(OSHC12D60)

#if defined(OSHICROSS12)
#pragma CONST_SEG .vectors
#endif  /* defined(OSHICROSS12) */

OSVECTAB = {

    OSVECTF _dummyISR,                          /* 0xFFC2:  CGM lock and limp home */
    OSVECTF _dummyISR,                          /* 0xFFC4:  MSCAN transmit  */
    OSVECTF _dummyISR,                          /* 0xFFC6:  MSCAN receive   */
    OSVECTF _dummyISR,                          /* 0xFFC8:  MSCAN errors    */
    OSVECTF _dummyISR,                          /* 0xFFCA:  Pulse Accumulator B Overflow */
#if defined(OSSYSTIMER) && defined(OSTIMMDC)
    OSVECTF OSISRSystemTimer,                   /* 0xFFCC:  Modulus Down-Counter underflow */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2MDC)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFCC:  Modulus Down-Counter underflow */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMMDC) */  
    OSVECTF _dummyISR,                          /* 0xFFCE:  Key wake-up G or H */
    OSVECTF _dummyISR,                          /* 0xFFD0:  MSCAN wake-up    */
    OSVECTF _dummyISR,                          /* 0xFFD2:  ATD0 or ATD1     */
    OSVECTF _dummyISR,                          /* 0xFFD4:  SCI 1            */
    OSVECTF _dummyISR,                          /* 0xFFD6:  SCI 0            */
    OSVECTF _dummyISR,                          /* 0xFFD8:  SPI              */
    OSVECTF _dummyISR,                          /* 0xFFDA:  Pulse acc input  */
    OSVECTF _dummyISR,                          /* 0xFFDC:  Pulse acc overf  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMTOI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFDE:  Timer Overflow  */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMTOI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFDE:  Timer Overflow  */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */  
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC7)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE0:  Timer Channel 7 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC7)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
    OSVECTF _dummyISR,                          /* 0xFFE0:  Timer Channel 7 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC6)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE2:  Timer Channel 6 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC6)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
    OSVECTF _dummyISR,                          /* 0xFFE2:  Timer Channel 6 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC5)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE4:  Timer Channel 5 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC5)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
    OSVECTF _dummyISR,                          /* 0xFFE4:  Timer Channel 5 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC4)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE6:  Timer Channel 4 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC4)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
    OSVECTF _dummyISR,                          /* 0xFFE6:  Timer Channel 4 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC3)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE8:  Timer Channel 3 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC3)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
    OSVECTF _dummyISR,                          /* 0xFFE8:  Timer Channel 3 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC2)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEA:  Timer Channel 2 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC2)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
    OSVECTF _dummyISR,                          /* 0xFFEA:  Timer Channel 2 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC1)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEC:  Timer Channel 1 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC1)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
    OSVECTF _dummyISR,                          /* 0xFFEC:  Timer Channel 1 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC0)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEE:  Timer Channel 0 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC0)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
    OSVECTF _dummyISR,                          /* 0xFFEE:  Timer Channel 0 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
#if defined(OSSYSTIMER) && defined(OSTIMRTI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFF0:  Real Time Interrupt */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2RTI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF0:  Real Time Interrupt */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF2:  IRQ             */
    OSVECTF _dummyISR,                          /* 0xFFF4:  XIRQ            */
#if defined(OSBCC1)
    OSVECTF _dummyISR,                          /* SWI               */
#elif defined(OSECC1)
    OSTaskForceDispatchHandler,                 /* SWI               */
#endif  /* defined(OSECC1)  */
    OSVECTF _dummyISR,                          /* 0xFFF8:  instr trap      */
    OSVECTF _dummyISR,                          /* 0xFFFA:  cop fail        */
    OSVECTF _dummyISR,                          /* 0xFFFC:  cop clock fail  */
#if defined(OSHICROSS12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _Startup,                           /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _stext,                             /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSCOSMIC12)  */
};

#if defined(OSHICROSS12)
#pragma CONST_SEG DEFAULT
#endif  /* defined(OSHICROSS12) */

#endif  /*  defined(OSHC12D60)  */

/***************************************************************************/
/* OSHC12B32 */
/***************************************************************************/


/***************************************************************************/
/* OSHC12BC32 */
/***************************************************************************/

#if defined(OSHC12BC32)

#if defined(OSHICROSS12)
#pragma CONST_SEG .vectors
#endif  /* defined(OSHICROSS12) */

OSVECTAB = {

    OSVECTF _dummyISR,                          /* 0xFFC2:  Reserved        */
    OSVECTF _dummyISR,                          /* 0xFFC4:  MSCAN transmit  */
    OSVECTF _dummyISR,                          /* 0xFFC6:  MSCAN receive   */
    OSVECTF _dummyISR,                          /* 0xFFC8:  MSCAN errors    */
    OSVECTF _dummyISR,                          /* 0xFFCA:  Reserved        */
    OSVECTF _dummyISR,                          /* 0xFFCC:  Reserved        */
    OSVECTF _dummyISR,                          /* 0xFFCE:  Reserved        */
    OSVECTF _dummyISR,                          /* 0xFFD0:  MSCAN wake-up   */
    OSVECTF _dummyISR,                          /* 0xFFD2:  ATD             */
    OSVECTF _dummyISR,                          /* 0xFFD4:  Reserved        */
    OSVECTF _dummyISR,                          /* 0xFFD6:  SCI 0           */
    OSVECTF _dummyISR,                          /* 0xFFD8:  SPI             */
    OSVECTF _dummyISR,                          /* 0xFFDA:  Pulse acc input */
    OSVECTF _dummyISR,                          /* 0xFFDC:  Pulse acc overf */
#if defined(OSSYSTIMER) && defined(OSTIMTIMTOI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFDE:  Timer Overflow  */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMTOI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFDE:  Timer Overflow  */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC7)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE0:  Timer Channel 7 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC7)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
    OSVECTF _dummyISR,                          /* 0xFFE0:  Timer Channel 7 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC6)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE2:  Timer Channel 6 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC6)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
    OSVECTF _dummyISR,                          /* 0xFFE2:  Timer Channel 6 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC5)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE4:  Timer Channel 5 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC5)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
    OSVECTF _dummyISR,                          /* 0xFFE4:  Timer Channel 5 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC4)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE6:  Timer Channel 4 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC4)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
    OSVECTF _dummyISR,                          /* 0xFFE6:  Timer Channel 4 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC3)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE8:  Timer Channel 3 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC3)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
    OSVECTF _dummyISR,                          /* 0xFFE8:  Timer Channel 3 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC2)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEA:  Timer Channel 2 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC2)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
    OSVECTF _dummyISR,                          /* 0xFFEA:  Timer Channel 2 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC1)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEC:  Timer Channel 1 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC1)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
    OSVECTF _dummyISR,                          /* 0xFFEC:  Timer Channel 1 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC0)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEE:  Timer Channel 0 */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC0)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
    OSVECTF _dummyISR,                          /* 0xFFEE:  Timer Channel 0 */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
#if defined(OSSYSTIMER) && defined(OSTIMRTI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFF0:  Real Time Interrupt */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2RTI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF0:  Real Time Interrupt */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF StallInt,                           /* 0xFFF2:  IRQ             */
    OSVECTF _dummyISR,                          /* 0xFFF4:  XIRQ            */
#if defined(OSBCC1)
    OSVECTF _dummyISR,                          /* SWI               */
#elif defined(OSECC1)
    OSTaskForceDispatchHandler,                 /* SWI               */
#endif  /* defined(OSECC1)  */
    OSVECTF _dummyISR,                          /* 0xFFF8:  instr trap      */
    OSVECTF _dummyISR,                          /* 0xFFFA:  cop fail        */
    OSVECTF _dummyISR,                          /* 0xFFFC:  cop clock fail  */
#if defined(OSHICROSS12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _Startup,                           /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _stext,                             /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSCOSMIC12)  */
};

#if defined(OSHICROSS12)
#pragma CONST_SEG DEFAULT
#endif  /* defined(OSHICROSS12) */

#endif  /*  defined(OSHC12BC32) */

/***************************************************************************/
/* OSHC12D128 */
/***************************************************************************/

#if defined(OSHC12D128)

#if defined(OSHICROSS12)
#pragma CONST_SEG .vectors
#endif  /* defined(OSHICROSS12) */
OSVECTAB = {

    OSVECTF _dummyISR,                          /* 0xFFB6:  Reserved                */
    OSVECTF _dummyISR,                          /* 0xFFB8:  MSCAN 1 transmit        */
    OSVECTF _dummyISR,                          /* 0xFFBA:  MSCAN 1 receive         */
    OSVECTF _dummyISR,                          /* 0xFFBC:  MSCAN 1 errors          */
    OSVECTF _dummyISR,                          /* 0xFFBE:  MSCAN 1 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFC0:  IIC Bus                 */
    OSVECTF _dummyISR,                          /* 0xFFC2:  CGM lock and limp home  */
    OSVECTF _dummyISR,                          /* 0xFFC4:  MSCAN 0 transmit        */
    OSVECTF _dummyISR,                          /* 0xFFC6:  MSCAN 0 receive         */
    OSVECTF _dummyISR,                          /* 0xFFC8:  MSCAN 0 errors          */
    OSVECTF _dummyISR,                          /* 0xFFCA:  Pulse Accumulator B Overflow */
#if defined(OSSYSTIMER) && defined(OSTIMMDC)
    OSVECTF OSISRSystemTimer,                   /* 0xFFCC:  Modulus Down-Counter underflow */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2MDC)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFCC:  Modulus Down-Counter underflow */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMMDC) */  
    OSVECTF _dummyISR,                          /* 0xFFCE:  Key wake-up J or H      */
    OSVECTF _dummyISR,                          /* 0xFFD0:  MSCAN 0 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFD2:  ATD0 or ATD1            */
    OSVECTF _dummyISR,                          /* 0xFFD4:  SCI 1                   */
    OSVECTF _dummyISR,                          /* 0xFFD6:  SCI 0                   */
    OSVECTF _dummyISR,                          /* 0xFFD8:  SPI serial transfer complete */
    OSVECTF _dummyISR,                          /* 0xFFDA:  Pulse accumulator input edge */
    OSVECTF _dummyISR,                          /* 0xFFDC:  Pulse accumulator overflow */
#if defined(OSSYSTIMER) && defined(OSTIMTIMTOI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFDE:  Timer Overflow          */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMTOI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFDE:  Timer Overflow          */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */  
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC7)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE0:  Timer Channel 7         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC7)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
    OSVECTF _dummyISR,                          /* 0xFFE0:  Timer Channel 7         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC6)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE2:  Timer Channel 6         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC6)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
    OSVECTF _dummyISR,                          /* 0xFFE2:  Timer Channel 6         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC5)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE4:  Timer Channel 5         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC5)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
    OSVECTF _dummyISR,                          /* 0xFFE4:  Timer Channel 5         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC4)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE6:  Timer Channel 4         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC4)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
    OSVECTF _dummyISR,                          /* 0xFFE6:  Timer Channel 4         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC3)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE8:  Timer Channel 3         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC3)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
    OSVECTF _dummyISR,                          /* 0xFFE8:  Timer Channel 3         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC2)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEA:  Timer Channel 2         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC2)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
    OSVECTF _dummyISR,                          /* 0xFFEA:  Timer Channel 2         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC1)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEC:  Timer Channel 1         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC1)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
    OSVECTF _dummyISR,                          /* 0xFFEC:  Timer Channel 1         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
#if defined(OSSYSTIMER) && defined(OSTIMTIMOC0)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEE:  Timer Channel 0         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC0)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
    OSVECTF _dummyISR,                          /* 0xFFEE:  Timer Channel 0         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
#if defined(OSSYSTIMER) && defined(OSTIMRTI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFF0:  Real Time Interrupt     */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2RTI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF0:  Real Time Interrupt     */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF2:  IRQ                     */
    OSVECTF _dummyISR,                          /* 0xFFF4:  XIRQ                    */
#if defined(OSBCC1)
    OSVECTF _dummyISR,                          /* SWI               */
#elif defined(OSECC1)
    OSTaskForceDispatchHandler,                 /* SWI               */
#endif  /* defined(OSECC1)  */
    OSVECTF _dummyISR,                          /* 0xFFF8:  Unimplemented instruction trap  */
    OSVECTF _dummyISR,                          /* 0xFFFA:  COP failure reset               */
    OSVECTF _dummyISR,                          /* 0xFFFC:  COP clock monitor fail reset    */
#if defined(OSHICROSS12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _Startup,                           /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _stext,                             /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSCOSMIC12)  */
};

#if defined(OSHICROSS12)
#pragma CONST_SEG DEFAULT
#endif  /* defined(OSHICROSS12) */

#endif  /*  defined(OSHC12D128) */

/***************************************************************************/
/* OSS12DP256 */
/***************************************************************************/

#if defined(OSS12DP256)

#if defined(OSHICROSS12)
#pragma CONST_SEG .vectors
#endif  /* defined(OSHICROSS12) */
OSVECTAB = {

    OSVECTF _dummyISR,                          /* 0xFF8C:  PWM Emergency Shutdown  */
    OSVECTF _dummyISR,                          /* 0xFF8E:  Port P Interrupt        */
    OSVECTF _dummyISR,                          /* 0xFF90:  MSCAN 4 transmit        */
    OSVECTF _dummyISR,                          /* 0xFF92:  MSCAN 4 receive         */
    OSVECTF _dummyISR,                          /* 0xFF94:  MSCAN 4 errors          */
    OSVECTF _dummyISR,                          /* 0xFF96:  MSCAN 4 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFF98:  MSCAN 3 transmit        */
    OSVECTF _dummyISR,                          /* 0xFF9A:  MSCAN 3 receive         */
    OSVECTF _dummyISR,                          /* 0xFF9C:  MSCAN 3 errors          */
    OSVECTF _dummyISR,                          /* 0xFF9E:  MSCAN 3 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFA0:  MSCAN 2 transmit        */
    OSVECTF _dummyISR,                          /* 0xFFA2:  MSCAN 2 receive         */
    OSVECTF _dummyISR,                          /* 0xFFA4:  MSCAN 2 errors          */
    OSVECTF _dummyISR,                          /* 0xFFA6:  MSCAN 2 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFA8:  MSCAN 1 transmit        */
    OSVECTF _dummyISR,                          /* 0xFFAA:  MSCAN 1 receive         */
    OSVECTF _dummyISR,                          /* 0xFFAC:  MSCAN 1 errors          */
    OSVECTF _dummyISR,                          /* 0xFFAE:  MSCAN 1 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFB0:  MSCAN 0 transmit        */
    OSVECTF _dummyISR,                          /* 0xFFB2:  MSCAN 0 receive         */
    OSVECTF _dummyISR,                          /* 0xFFB4:  MSCAN 0 errors          */
    OSVECTF _dummyISR,                          /* 0xFFB6:  MSCAN 0 wake-up         */
    OSVECTF _dummyISR,                          /* 0xFFB8:  FLASH                   */
    OSVECTF _dummyISR,                          /* 0xFFBA:  EEPROM                  */
    OSVECTF _dummyISR,                          /* 0xFFBC:  SPI2                    */
    OSVECTF _dummyISR,                          /* 0xFFBE:  SPI1                    */
    OSVECTF _dummyISR,                          /* 0xFFC0:  IIC Bus                 */
    OSVECTF _dummyISR,                          /* 0xFFC2:  DLC                     */
    OSVECTF _dummyISR,                          /* 0xFFC4:  SCME                    */
    OSVECTF _dummyISR,                          /* 0xFFC6:  CRG lock                */
    OSVECTF _dummyISR,                          /* 0xFFC8:  Pulse Accumulator B Overflow */

#if defined(OSSYSTIMER) && defined(OSTIMMDC)
    OSVECTF OSISRSystemTimer,                   /* 0xFFCA:  Modulus Down-Counter underflow */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2MDC)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFCA:  Modulus Down-Counter underflow */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMMDC) */  

    OSVECTF _dummyISR,                          /* 0xFFCC:  Port H                  */
    OSVECTF _dummyISR,                          /* 0xFFCE:  Port J                  */
    OSVECTF _dummyISR,                          /* 0xFFD0:  ATD1                    */
    OSVECTF _dummyISR,                          /* 0xFFD2:  ATD0                    */
    OSVECTF _dummyISR,                          /* 0xFFD4:  SCI 1                   */
    OSVECTF _dummyISR,                          /* 0xFFD6:  SCI 0                   */
    OSVECTF _dummyISR,                          /* 0xFFD8:  SPI serial transfer complete */
    OSVECTF _dummyISR,                          /* 0xFFDA:  Pulse accumulator input edge */
    OSVECTF _dummyISR,                          /* 0xFFDC:  Pulse accumulator A overflow */

#if defined(OSSYSTIMER) && defined(OSTIMTIMTOI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFDE:  Timer Overflow          */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMTOI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */
    OSVECTF _dummyISR,                          /* 0xFFDE:  Timer Overflow          */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMTOI)  */  

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC7)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE0:  Timer Channel 7         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC7)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */
    OSVECTF _dummyISR,                          /* 0xFFE0:  Timer Channel 7         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC7)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC6)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE2:  Timer Channel 6         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC6)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */
    OSVECTF _dummyISR,                          /* 0xFFE2:  Timer Channel 6         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC6)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC5)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE4:  Timer Channel 5         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC5)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */
    OSVECTF _dummyISR,                          /* 0xFFE4:  Timer Channel 5         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC5)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC4)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE6:  Timer Channel 4         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC4)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */
    OSVECTF _dummyISR,                          /* 0xFFE6:  Timer Channel 4         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC4)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC3)
    OSVECTF OSISRSystemTimer,                   /* 0xFFE8:  Timer Channel 3         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC3)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */
    OSVECTF _dummyISR,                          /* 0xFFE8:  Timer Channel 3         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC3)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC2)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEA:  Timer Channel 2         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC2)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */
    OSVECTF _dummyISR,                          /* 0xFFEA:  Timer Channel 2         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC2)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC1)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEC:  Timer Channel 1         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC1)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */
    OSVECTF _dummyISR,                          /* 0xFFEC:  Timer Channel 1         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC1)  */

#if defined(OSSYSTIMER) && defined(OSTIMTIMOC0)
    OSVECTF OSISRSystemTimer,                   /* 0xFFEE:  Timer Channel 0         */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2TIMOC0)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */
    OSVECTF _dummyISR,                          /* 0xFFEE:  Timer Channel 0         */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMTIMOC0)  */

#if defined(OSSYSTIMER) && defined(OSTIMRTI)
    OSVECTF OSISRSystemTimer,                   /* 0xFFF0:  Real Time Interrupt     */
#elif   defined(OSSECONDTIMER) && defined(OSTIM2RTI)
    OSVECTF OSISRSecondTimer,
#else   /* defined(OSSYSTIMER) && defined(OSTIMRTI) */
    OSVECTF _dummyISR,                          /* 0xFFF0:  Real Time Interrupt     */
#endif  /* defined(OSSYSTIMER) && defined(OSTIMRTI) */

    OSVECTF _dummyISR,                          /* 0xFFF2:  IRQ                     */
    OSVECTF _dummyISR,                          /* 0xFFF4:  XIRQ                    */

#if defined(OSBCC1)
    OSVECTF _dummyISR,                          /* SWI               */
#elif defined(OSECC1)
    OSTaskForceDispatchHandler,                 /* SWI               */
#endif  /* defined(OSECC1)  */

    OSVECTF _dummyISR,                          /* 0xFFF8:  Unimplemented instruction trap  */
    OSVECTF _dummyISR,                          /* 0xFFFA:  COP failure reset               */
    OSVECTF _dummyISR,                          /* 0xFFFC:  COP clock monitor fail reset    */
#if defined(OSHICROSS12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _Startup,                           /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSHICROSS12) */
#if defined(OSCOSMIC12)
#if defined(_BASE) || defined(_BASERAM)
    OSVECTF _StartupInitRAMREG,                 /* 0xFFFE:  Reset   */
#else   /*  defined(_BASE) || defined(_BASERAM) */
    OSVECTF _stext,                             /* 0xFFFE:  Reset   */
#endif  /*  defined(_BASE) || defined(_BASERAM) */
#endif  /* defined(OSCOSMIC12)  */
};

#if defined(OSHICROSS12)
#pragma CONST_SEG DEFAULT
#endif  /* defined(OSHICROSS12) */

#endif  /*  defined(OSS12DP256) */

