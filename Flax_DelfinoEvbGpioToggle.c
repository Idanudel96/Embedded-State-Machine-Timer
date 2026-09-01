//###########################################################################
//
// FILE:    Flax_DelfinoEvbGpioToggle.c
//
// TITLE:   DSP2833x Device GPIO toggle test program. 
// This template was written by Eli Flaxer for DelfinoEvb Evaluation Board
//
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################



// IDAN NUDEL
// TONY TANNAS




#include "DSP28x_Project.h"     // Device Header file and Examples Include File
#include "LCD2x16Display.h"
#include "count.h"
#include "StateMachine.h"
#include "keyboardmat.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void DelfinoEvbGpioSelect(void);
void MyMainProg(void);
interrupt void cpu_timer0_isr(void);
interrupt void Xint3456_isr(void);
void StateMachine(int flag);
void Check_Code(char* keyArr);
void read_Keyboard();



int countdown_enable=0;
int T=0;
char tmr[75];


#define CODE_SIZE 4
const char my_code[] = { '1', '0', '0', '7' };
char keyArr[CODE_SIZE] = { 0 };
int keyIndex = 0;
int code_enable=0;



int32 MyDelayLoop = 200000L;

/*****************************************************************************/
void GpioCSetClear(int k,int x)
{
	if (x)
		GpioDataRegs.GPCSET.all = (1L<<k);
	else
		GpioDataRegs.GPCCLEAR.all = (1L<<k);
}
/*****************************************************************************/



void main(void)
{

	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
		InitSysCtrl();

	// Step 2. Initalize GPIO:
	// This example function is found in the DSP2833x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	// InitGpio();  // Skipped for this example

	// For this example use the following configuration:
		DelfinoEvbGpioSelect();

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
		DINT;

	// Initialize PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the DSP2833x_PieCtrl.c file.
		InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
		IER = 0x0000;
		IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
	// This function is found in DSP2833x_PieVect.c.
		InitPieVectTable();

		// Interrupts that are used in this example are re-mapped to
		// ISR functions found within this file.
		EALLOW;
		// This is needed to write to EALLOW protected registers
			PieVectTable.TINT0 = &cpu_timer0_isr;
			EDIS;
		// This is needed to disable write to EALLOW protected registers
		// Step 4. Initialize the Device Peripheral. This function can be
		// found in DSP2833x_CpuTimers.c
		InitCpuTimers(); // For this example, only initialize the Cpu Timers
	//#if (CPU_FRQ_150MHZ)
		// Configure CPU-Timer 0 to interrupt every 500 milliseconds:
		// 150MHz CPU Freq, 50 millisecond Period (in uSeconds)
			ConfigCpuTimer(&CpuTimer0, 150, 1000000);
			CpuTimer0Regs.TCR.bit.TIE =1;
				CpuTimer0Regs.TCR.bit.TSS=0;
	//#endif
		// To ensure precise timing, use write-only instructions to write to the entire register.Therefore, if any
		// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
		// below settings must also be updated.
					//CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
		// Step 5. User specific code, enable interrupts:
		// Configure GPIO32 as a GPIO output pin

				IER |= M_INT1;
		//EALLOW;
					PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
					EINT;
					ERTM;
//		GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
//		GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
//		EDIS;
//		// Enable CPU INT1 which is connected to CPU-Timer 0:
//		//IER |= M_INT1;
//		// Enable TINT0 in the PIE: Group 1 interrupt 7
//
//		// Enable global Interrupts and higher priority real-time debug events:
//		EINT;
//		// Enable Global interrupt INTM
//		ERTM;
   MyMainProg();
}
/*****************************************************************************/

/*****************************************************************************/


void MyMainProg(void)
{ 
   //GpioDataRegs.GPASET.bit.GPIO27 = 1;		// Turn on the buzzer
   //DELAY_US(200000);
  // GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;	// Turn off the buzzer
   //	StateMachine(0);

   BackLightLCD(1);
   InItLCD();
 //  DELAY_US(10000);
   ClearLCD();


   while(1)
   	   {
	   StateMachine(0);
   	   }
}

////INSIDE WHILE LOOP: Toggle I/Os using DATA, SET, CLEAR and TOGGEL registers
//       GpioDataRegs.GPADAT.all    = 0xA;			// DAT Register	(hazardous !!!)
//       GpioDataRegs.GPCCLEAR.all  = 0x00000F00;		// CLEAR Register
//       GpioDataRegs.GPCTOGGLE.all = 0x0000F000;		// TOGGEL Register
//       DELAY_US(MyDelayLoop);
//
//       GpioDataRegs.GPADAT.all    = 0x5;			// DAT Register	(hazardous !!!)
//       GpioDataRegs.GPCSET.all    = 0x00000F00;		// SET Register
//       GpioDataRegs.GPCTOGGLE.all = 0x0000F000;		// TOGGEL Register
//       DELAY_US(MyDelayLoop);
//
//// Reading the switches
//       GpioDataRegs.GPCDAT.bit.GPIO64 = GpioDataRegs.GPADAT.bit.GPIO8;	//(hazardous !!!)
//       GpioDataRegs.GPCDAT.bit.GPIO65 = GpioDataRegs.GPADAT.bit.GPIO9;	//(hazardous !!!)
//       GpioCSetClear(2, GpioDataRegs.GPADAT.bit.GPIO10);	// No Risk !!!
//       GpioCSetClear(3, GpioDataRegs.GPADAT.bit.GPIO11);	// No Risk !!!
//}
//}
/*****************************************************************************/

 State MyStateMachine = LOCKED;

 void StateMachine(int flag)
 {
 	if (flag==0)
 		MyStateMachine= LOCKED;
 	else
 		MyStateMachine= OPEN;


     switch (MyStateMachine)
     {
     case LOCKED:
             ClearLCD();
             GoToLCD(0, 5);
             PrintLCD("LOCKED");
             DELAY_US(1000000);
             read_Keyboard();                   //Enable writing again when in LOCKED state
      break;


     case OPEN:
         GpioDataRegs.GPASET.bit.GPIO27 = 1;
         DELAY_US(200000);
         GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
         T =5*( (GpioDataRegs.GPADAT.all>>8)&0xF);     //Mask GPIO 8-11 and multiply by 5
         ClearLCD();
         GoToLCD(0, 5);
         PrintLCD("OPEN");
         DELAY_US(1000000);
         ClearLCD();
         GoToLCD(0, 2);
         PrintLCD("Lockdown In:");
         countdown_enable=1;                  // Enable the countdown inside the interrupt
         while (countdown_enable==1)
         {
        	 if (ReadKB(0)=='#')             // If # is pressed - exit the countdown loop and return to locked state
        	 {
        		 countdown_enable=0;
        		 ClearLCD();
        		 DELAY_US(1000000);
        		 StateMachine(0);
        	 }
         }
         DELAY_US(2000000);
         StateMachine(0);                     // After the countdown has ended - return to LOCKED state
      break;
     }
 }



 /*****************************************************************************/

 void read_Keyboard() {
 	int r;
     char my_Read = ReadKB(1);  // Read keyboard input
     if (my_Read != 0)           // If a key is pressed
     {
     	if (my_Read == '*')       // If the enable button * has been pressed
     	{
     		ClearLCD();
     		GoToLCD(0, 2);
     		PrintLCD("Key Pressed: ");
             keyIndex = 0;
             code_enable = 1;         // Enable writing the input code into a keyArr[]
     	}

     	if (my_Read != '*')          // If the first button clicked is NOT '*' - inform the user
     	{
     		ClearLCD();
     		GoToLCD(0, 2);
     		PrintLCD("Click Enable");
     		DELAY_US(1000000);
             keyIndex = 0;
             code_enable = 0;            // If the enable button has not been pressed - don't enable reading into the arr
             StateMachine(0);            // Return into LOCKED state
     	}

     	if (code_enable == 1)          // If the first key clicked was * - allow writing into the arr
     	{
     		GoToLCD(1, 5);
     		for (r=0; r<4; r++)
     		{
 				keyArr[r] = ReadKB(1);     //Place the input keys into the arr
 				PutcLCD(keyArr[r]);
 				DELAY_US(100000);
     		}
 			Check_Code(keyArr);          // Send the users arr (the input code) for check
     		DELAY_US(100000);
 			code_enable = 0;
     	}
     }
 }

 /*****************************************************************************/

 void Check_Code(char* keyArr)
 {
 	int j;

 	for (j=0; j<CODE_SIZE;j++)
 	{
 		if (keyArr[j]!=my_code[j])            // If the input code is wrong go into:
 		{
     		ClearLCD();
     		GoToLCD(0, 2);
     		PrintLCD("WRONG CODE");
     		DELAY_US(1000000);
     		GpioDataRegs.GPASET.bit.GPIO27 = 1;
     		DELAY_US(100000);
     		GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
     		DELAY_US(100000);
     		memset(keyArr, 0, CODE_SIZE);         // Restart the keyArr for future attempts
     		keyIndex = 0;
     		StateMachine(0);                      // Return into LOCKED state
 		}
 	}
 	StateMachine(1);                              // If the codes match - move to OPEN state
 }

 /*****************************************************************************/



void DelfinoEvbGpioSelect(void)
{
    EALLOW;

	GpioCtrlRegs.GPAMUX1.all = 0x00000000;  	// All GPIO
	GpioCtrlRegs.GPAMUX2.all = 0x00000000;  	// All GPIO

    GpioCtrlRegs.GPADIR.all = 0x0000000F;   	// Outputs 4 Leds
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;   		// Buzzer
    GpioCtrlRegs.GPBDIR.all = 0x07FF0F00;   	// Outputs LCD 8 Bus 3 Control
    //GpioCtrlRegs.GPBDIR.all = 0x07FF??00;   	// Extended Bus Direction GPIO40-GPIO47 KB
    GpioCtrlRegs.GPCDIR.all = 0x0000FFFF;   	// Outputs 8 Leds 4 TP 4 TestLed
    //GpioCtrlRegs.GPCDIR.all = 0x000?FFFF;   	// Extended Bus Direction GPIO80-GPIO83 Button

    //GpioCtrlRegs.GPBPUD.all = 0x0000FF00;   	// Extended Bus Pull-Up Resistors

    EDIS;
}
/*****************************************************************************/



interrupt void cpu_timer0_isr(void)
{

	int p;
	CpuTimer0.InterruptCount++;
	if (countdown_enable==1)                      // If the countdown in enabled go into:
	{
		if (T>0)                                 // As long as the timer is greater then 0:
		{
			GoToLCD(1,0);
			for(p=0; p<16; p++)                    // A loop that moves the tens digit to the ones position
			PutcLCD(' ');
			sprintf(tmr, "%d", T);
			GoToLCD(1, 6);
			PrintLCD(tmr);                        // Print the timer on the LCD
			T--;
		}
		else if (T==0)                           // If T is 0 - disable the countdown_enable
		{
			countdown_enable=0;
		}
	}

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


















