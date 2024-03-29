// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on TM4C123
// Program written by: Noah Najvar, Adrian Gallegos
// Date Created: 3/6/17 
// Last Modified: 3/22/21 
// Lab number: 6
// Hardware connections
/*

Port B [2, 3, 4, 5] - DAC input
Port E [0, 1, 2] - piano input

*/

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "DAC.h"
#include "../inc/tm4c123gh6pm.h"


// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();
  
	SYSCTL_RCGCGPIO_R |= 0x20;
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTF_DEN_R |= 0x02;
	
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
}

// **************Sound_Start*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Start called again, or Sound_Off is called
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Start(uint32_t period){
  if (period == 0)
	{
		GPIO_PORTF_DATA_R &= 0xFD;
		NVIC_ST_CTRL_R = 0;
		return;
	}
	GPIO_PORTF_DATA_R |= 0x02;
	NVIC_ST_RELOAD_R = period - 1;
	NVIC_ST_CTRL_R = 0x07;
}

// **************Sound_Voice*********************
// Change voice
// EE319K optional
// Input: voice specifies which waveform to play
//           Pointer to wave table
// Output: none
void Sound_Voice(const uint8_t *voice){
  // optional
}
// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
  // write this

}
// **************Sound_GetVoice*********************
// Read the current voice
// EE319K optional
// Input: 
// Output: voice specifies which waveform to play
//           Pointer to current wavetable
const uint8_t *Sound_GetVoice(void){
 // write this
 // optional
  return 0;
}

// Interrupt service routine
// Executed every 12.5ns*(period)
const uint8_t sinWave[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};
uint8_t i = 0; 
void SysTick_Handler(void){
		
	i++;
	i &= 0x1F;
	DAC_Out(sinWave[i]);

}


