
/******************************************************************************
Function Name	:	main
Engineer		:	D Brook / F Winters
Date			:	2/25/98

Parameters		:	none
Returns			:	none
Notes			:	Main entry point of the application. This routine starts
					the OS code.
******************************************************************************/
void StartApplication(void);

void
main(void)
{
	StartApplication();		 /* jump to OSEK v.2.0 startup */
}