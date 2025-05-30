

#ifndef ULTRASONIC_HCSR04_H_
#define ULTRASONIC_HCSR04_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* Ultrasonic sensor HW Ports and Pins Ids */

#define ULTRASONIC_ECHO_PORT_ID						PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID						PIN6_ID

#define ULTRASONIC_TRIGGER_PORT_ID               	PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID					PIN5_ID



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void Ultrasonic_init(void);


/*
 * 	Description :
	Send the Trigger pulse to the ultrasonic
 */
void Ultrasonic_Trigger(void);


/*
 * 	Description :
	-Send the trigger pulse by using the Ultrasonic_Trigger function
	-Start the measurements by the ICU
 */
uint16 Ultrasonic_readDistance(void);


/*
 * 	Description :
	-The call back function called by the ICU driver
	-Calculate the pulse time generated by the ultrasonic sensor
 */
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_HCSR04_H_ */
