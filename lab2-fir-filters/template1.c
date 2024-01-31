/*
(C) Copyright Utah State University 2013.  All rights reserved.
No part of this program may be photocopied, reproduced, or translated
to another program language without the prior written consent of
Utah State University.

Time-stamp: " "

(program) template1.c
(status) Under development
(description) Template file for output of samples using the OMAP-L138 Experimenter kit.
(keywords) ECE 5640, Real-Time DSP

(long_d)
This is a template file for use in the lab for ECE 5640.  It is used to provide the
initialization for the OMAP-L138 Experimenter kit that will send samples to the left
and right channels.
(long_d)

(see_also) template1.h template2.c template2.h aic3106.c mcasp.c

(bugs)
There are no known bugs at this time
(bugs)

(author) Andrew Pound

(modifications)
Written 04/01/13 by name
Modified: See subversion logs.
(modifications)


  Info: $Id: template1.c 738 2014-01-15 19:12:30Z scott $   USU
  Revision: $Rev: 738 $
 $LastChangedDate: 2014-01-15 12:12:30 -0700 (Wed, 15 Jan 2014) $
 $LastChangedBy: scott $

*/

#include "template1.h"


// The following define is for a test output generated using a call to the sin()
// function.  THIS IS NOT HOW LAB 1 IS TO BE DONE!
// Size of the array buffer.
#define BUFF_SIZE  	(256)

// Function Prototypes
void SetGpio(void);
//-----------------------------------------------------------------------------
// Function:	Initialize the general-purpose I/O
//
// Parameters:  none
//
// Returns:     none
//
//-----------------------------------------------------------------------------
int main(void)
{
	int16_t sample = 0;				// Sample index into the buffer array
	int16_t dataInput;       		// Sine Sample
	int16_t oldDataInput;       	// Sine Sample delayed
	float theta = 0;				// Argument of the sine wave
	int16_t buffer[BUFF_SIZE] = {0};// Buffer to hold the sine samples
	float amplitude = AMPLITUDE;	// Amplitude of the generated sin wave

   EVMOMAPL138_init();				// Initialize the board
   EVMOMAPL138_initRAM();			// Set up the RAM
   EVMOMAPL138_enableDsp();			// Wake up the DSP


	// init the i2c for all to use.
	USTIMER_init();					// General use timers
	I2C_init(I2C0, I2C_CLK_400K);	// I2C initialization

	// set gpio output
	SetGpio();						// Configure the General Purpose I/O
	
	McASP_Init();					// Initialize McASP

	AIC3106_Init();					// Initialize AIC3106

	McASP_Start();					// Start McASP

	// Infinite loop:  	Each loop reads/writes one sample to the left and right channels.
	while (1){

/* The following code is here to allow a test signal to be generated. THIS IS
NOT HOW LAB 1 IS TO BE DONE!  Remove the code up to the indicated spot and insert
your own code.
*/

		// Store the last sample because of the one sample delay between channels.
		oldDataInput = dataInput;

		// Calculate the next sine wave sample...
        dataInput = ((int16_t) amplitude*sin(theta));
			
		// Increment the argument...
		theta += THETA_INC;
        if (theta > 2*PI) theta -= 2*PI;  	// Wrap around 2pi
			
		// Store the new sample in the buffer, for viewing...
        buffer[sample] = dataInput;
        sample = (sample+1)%BUFF_SIZE;      // Update the sample indx
			
/* Before writing the 16-bit samples, you must insert your own processing here. */

        // wait for xmit ready and send a sample to the left channel.
        while (!CHKBIT(MCASP->SRCTL11, XRDY)) {}
        MCASP->XBUF11 = oldDataInput;
//        oldDataInput = MCASP->XBUF12;	// Read the left channel input samples.

        // wait for xmit ready and send a sample to the right channel.
        while (!CHKBIT(MCASP->SRCTL11, XRDY)) {}
        MCASP->XBUF11 = dataInput;
//        dataInput = MCASP->XBUF12;	// Read the right channel input samples.
            	
     }   
}

//-----------------------------------------------------------------------------
// SetGpio
// config pinmux for gpio
//-----------------------------------------------------------------------------

void SetGpio(void)
{
	uint32_t	errchk;

	EVMOMAPL138_pinmuxConfig(PINMUX_MCASP_REG_17,PINMUX_MCASP_MASK_17,PINMUX_MCASP_VAL_17);
	errchk=GPIO_setDir(GPIO_BANK7,GPIO_PIN7,GPIO_OUTPUT);

}

