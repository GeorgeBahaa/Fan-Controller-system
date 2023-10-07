/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: header file for the DC Motor driver
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID    PORTB_ID


#define DC_MOTOR_PIN1_ID    PIN0_ID
#define DC_MOTOR_PIN2_ID    PIN1_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	DC_MOTOR_OFF,DC_MOTOR_CW,DC_MOTOR_ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * 1) setup the direction for the two motor pins through the GPIO driver.
 * 2) Stop the motor at the beginning
 */
void DcMotor_Init(void);

/*
 * Description:
 * 1) setup the state (ON or OFF) of the motor
 * 2) Control the speed of the motor 0->100% from its max speed by sending to PWM driver
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
