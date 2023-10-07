/*
 * Mini_Project_3.c
 *
 *  Created on: Oct 6, 2022
 *      Author: georg
 */

#include "ADC.h"
#include "DC_Motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "avr/io.h" /* To use the SREG Register */

typedef enum{
	FAN_OFF,FAN_ON
}Fan_State;

int main(void){
	uint8 temp;

	ADC_ConfigType ADC_Configurations = {INTERNAL_VOLT,F_CPU_8};

	Fan_State Fan = FAN_OFF;

	/*Enable interrupts by setting I-bit*/
	SREG |= (1<<7);

	/*Initialize Motor Driver*/
	DcMotor_Init();

	/*Initialize LCD Driver*/
	LCD_init();

	/*Initialize ADC Driver	 */
	ADC_init(&ADC_Configurations);



	/*Display the string "Temp =   °C" only once at the second row*/
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =   C ");

	while(1){
		temp= LM35_getTemperature();     // read the temperature from the sensor

		// if temperature more than 120 °C
		if (temp>=120){

			Fan= FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,100);

		}
		// if temperature more than 90 °C
		else if (temp>=90){

			Fan= FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,75);

		}
		// if temperature more than 60 °C
		else if (temp>=60){

			Fan= FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,50);

		}
		// if temperature more than 30 °C
		else if (temp>=30){

			Fan= FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,25);

		}
		// if temperature less than 30 °C
		else{

			Fan= FAN_OFF;
			DcMotor_Rotate(DC_MOTOR_OFF,0);

		}

		// Display the state of the fan on the LCD
		if (Fan == FAN_OFF){
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is OFF");
		}
		else{
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is ON ");
		}

		// Display the temperature value every time at same position on the LCD
		LCD_moveCursor(1,10);
		if(temp>=100){
			LCD_intgerToString(temp);
		}
		else{
			LCD_intgerToString(temp);
			// In case the digital value is two or one digits print space in the next digit place
			LCD_displayCharacter(' ');
		}

	}
}
