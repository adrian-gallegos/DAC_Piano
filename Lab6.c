// Lab6.c
// Runs on TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Noah Najvar, Adrian Gallegos
// Date Created: 3/6/17 
// Last Modified: 3/22/21  
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/LaunchPad.h"
#include "../inc/CortexM.h"
#include "Sound.h"
#include "Key.h"
#include "Music.h"
#include "TExaS.h"

#define D 8513   //293.7 Hz
#define G 12755  //196 Hz
#define A 5682   //440 Hz


void DAC_Init(void);         // your lab 6 solution
void DAC_Out(uint8_t data);  // your lab 6 solution
uint8_t Testdata;

// lab video Lab6_voltmeter
int voltmetermain(void){ //voltmetermain(void){     
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  DAC_Init(); // your lab 6 solution
  Testdata = 15;
  EnableInterrupts();
  while(1){                
    Testdata = (Testdata+1)&0x0F;
    DAC_Out(Testdata);  // your lab 6 solution
  }
}

// lab video Lab6_static
int staticmain(void){   uint32_t last,now;  
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  Testdata = 15;
  EnableInterrupts();
  last = LaunchPad_Input();
  while(1){                
    now = LaunchPad_Input();
    if((last != now)&&now){
       Testdata = (Testdata+1)&0x0F;
       DAC_Out(Testdata); // your lab 6 solution
    }
    last = now;
    Clock_Delay1ms(25);   // debounces switch
  }
}



//**************Lab 6 solution below*******************


int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Key_Init();
  LaunchPad_Init();
  Sound_Init();
  EnableInterrupts();
  while(1){ 
		uint8_t input = Key_In();
		if (input == 0) {
			Sound_Start(0);
		}
		else if (input == 1) {
			Sound_Start(A);
		}
		else if (input < 4) {
			Sound_Start(D);
		}
		else if (input < 8) {
			Sound_Start(G);
		}
  }           
}


/*
int main(void){
	DAC_Init();
	for(int i = 0; i < 16; i++){
		DAC_Out(i);
		for(int j = 0; j < 10000000; j++);
	}
}
*/



