

#include <util/delay.h> //to use _delay_us
#define F_CPU 8000000UL 
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
#include "ultrasonic_HCSR04.h"
#include "avr/io.h"


uint8 g_edgeCount = 0;


void Ultrasonic_init(void){

	ICU_ConfigType Ultrasonic_ICU_Config = {ICU_RISING_EDGE,F_CPU_8};

	ICU_init(&Ultrasonic_ICU_Config);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);
}


void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(200);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);
}

void Ultrasonic_edgeProcessing(void){


	if(ICU_ISR_lastEdge){				//last edge was rising edge and now we're at a falling edge
		//Calculate captured pulse period
		ICU_CapturedValue=ICU_getInputCaptureValue();

		//Next time detect rising edge:

		//1) detect rising edge
		ICU_setEdgeDetectionType(ICU_RISING_EDGE);
		//2) next time (when ISR occurs) enter the "else condition"
		ICU_ISR_lastEdge=ICU_FALLING_EDGE;

	}else{								//last edge was falling edge and now we're at a rising edge
		//Reset the current time
		ICU_clearTimer();

		//Next time detect falling edge:

		//1) detect falling edge
		ICU_setEdgeDetectionType(ICU_FALLING_EDGE);
		//2) next time (when ISR occurs) enter the "if condition"
		ICU_ISR_lastEdge=ICU_RISING_EDGE;

	}



}



uint16 Ultrasonic_readDistance(void){
	uint16 Ultrasonic_distance=0;
	Ultrasonic_Trigger();

	// distance = (time of flight / 2) * speed of sound in air in m/s * 100(to convert m to cm)
//	Ultrasonic_distance = (ICU_CapturedValue/2) * 340 * 100;

	/* Ftimer = Fcpu/prescale= 8MHz / 8 = 1MHz
	 * Ttimer = 1 / Ftimer = 1 Microsecond = 1 * 10^-6 second
	 */

//	Ultrasonic_distance = Ultrasonic_distance / 1000000;
	Ultrasonic_distance = ICU_CapturedValue / 58.5;
	return Ultrasonic_distance;
}
