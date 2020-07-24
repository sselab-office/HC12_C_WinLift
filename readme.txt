

# HC12 OSEKturbo WindowLift demo and True-Time Simulator
###################################################################

Overview
========

This project is a HC12 OSEKturbo ANSI-C Simulator project.
This example is running the WindowLift application on the
True-Time Simulator.


The WindowLift application controls a car window lift, which is 
simulated in the True-Time Simulator.


The project
===========
The "True-Time Simulator" CodeWarrior target is available within this project.

When starting the debugger, the project application is automatically programmed 
to the Simulator.

NOTE: At the beginning the simulator automatically opens the windowlift panel
and the Inspect window.

This project example contains the following Groups of files:
- Sources: This Group contains your source files:
  -'main_demo.c' file, main function.
  -'winlift_demo.c' file, WindowLift core program
  -'winlift.h' file, header file for Windowlift demo
  -'Io.h' file, declaration of the I/O ports
  -'vector.c' file, describe the interrupt vector table
  -'usertypes.h' file, header file for Windowlift demo
  This files are physically stored in the 'sources' sub-directory.
  -'cfg.c'
  -'cfg.h'  
  -'osprop.h'
  This files are generated from OSEK SysGen and are physically stored in the 
  'gen'sub-directory.
  -'option.h'
  This files are generated from OSEK SysGen and are physically stored in the 
  {Project} directory.

- Prm: This Group contains the linker parameter file:
  The linker parameter file is used to build the application (memory location 
  specification...). This file is/must be set up in the Linker for HC12 
  Panel (Target Settings Panels -<ALT-F7>-). The .prm file physically is stored 
  in the 'prms' sub-directory.

- Debugger Project File: This Group contains the debugger initialization file:
  The .ini file contains the configuration information for the debugger:
  Target interface settings, path information, etc. 
  Paths and environment information can be set within the debugger when choosing 
  the menu entry File | Configuration.
  The .ini file is physically stored in the project directory.

- Startup Code: This Group contains the application startup code:
  The application startup code performs several program initializations.
  You may adapt it to your own needs, but in such a case, make sure that 
  you are using a local copy.
  The current start*.c file is physically stored in the 
  'CodeWarrior_xxx_Vx.x\lib\HC12c\SRC'sub-directory. This file is a copy of the one 
  located in the HC12 compiler library directory.

- Libs: This Group contains the ANSI library (binary) to be linked with 
  your application. The ansis.lib file is physically stored in the HC12 compiler 
  library directory. The winlift.lib file is physically stored in the 'lib' 
  sub-directory.

The start instruction
=====================

1. Run the Code Warrior IDE with the shortcut created in the program group.
2. Open the project HC12 C_WinLift (Simulator).mcp. Choose the menu 
   File -> Open -> ...\Metrowerks\CodeWarrior\Examples\HC12\HC12 SIMULATOR\
   HC12 C_WinLift, select HC12 C_WinLift (Simulator).mcp -> press Open.
3. Now you have the WindowLift project with all files set up. 
4. Start the Debugger using the menu Project -> Debug or press the Debug 
   button in the tool bar or press F5. The project will compile and link and 
   then will load automatically the application into the True-Time Simulator.
5. Run the WindowLift demo. Choose menu Run->Start/Continue or 
   choose the Start/Continue button in the tool bar or press F5.
6. Now press the up/down and other buttons in the WindowLift panel and
   watch the window going up/down

Metrowerks
