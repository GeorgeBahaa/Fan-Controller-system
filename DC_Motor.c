/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: source file for the DC Motor driver
 *
 * Author: George Bahaa
 *
 *******************************************************************************/
#include "DC_Motor.h"
#include "gpio.h"
#include "PWM.h"

/*
 * Description:
 * 1) setup the direction for the two motor pins through the GPIO driver.
 * 2) Stop the motor at the beginning
 */
void DcMotor_Init(void){

	/*Setup the two motor pins as output pins*/
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PIN2_ID,PIN_OUTPUT);

	/*Motor is stopped at the beginning*/
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);
}

/*
 * Description:
 * 1) setup the state (ON or OFF) of the motor
 * 2) Control the speed of the motor 0->100% from its max speed by sending to PWM driver
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if (state==DC_MOTOR_ACW){
		//ROTATE CW
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN2_ID,LOGIC_HIGH);

		PWM_Timer0_Start(speed);
	}
	else if (state==DC_MOTOR_CW){
		//ROTATE CW
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN1_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);

		PWM_Timer0_Start(speed);
	}
	else if (state==DC_MOTOR_OFF){
		//ROTATE CW
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);

		PWM_Timer0_Start(speed);
	}
	else{
		/* Do nothing*/
	}
}
