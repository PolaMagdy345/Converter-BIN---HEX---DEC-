#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"



void MOTOR_Stop(MOTOR_type m)
{
	DIO_WritePin(MotorPinsArr[m][IN1],LOW);
	DIO_WritePin(MotorPinsArr[m][IN2],LOW); 
	/*switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		break;

		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,LOW);
		break;

	}*/

}

void MOTOR_CW(MOTOR_type m)
{
		DIO_WritePin(MotorPinsArr[m][IN1],HIGH);
		DIO_WritePin(MotorPinsArr[m][IN2],LOW);
	/*switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,HIGH);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,HIGH);
		DIO_WritePin(M2_IN2,LOW);
		break;

		case M3:
		DIO_WritePin(M3_IN1,HIGH);
		DIO_WritePin(M3_IN2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_IN1,HIGH);
		DIO_WritePin(M4_IN2,LOW);
		break;

	}*/
}

void MOTOR_CCW(MOTOR_type m)
{
			DIO_WritePin(MotorPinsArr[m][IN1],LOW);
			DIO_WritePin(MotorPinsArr[m][IN2],HIGH);
	/*switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;

		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,HIGH);
		break;
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,HIGH);
		break;

	}*/
}

void MOTOR_Init(void)
{
	MOTOR_State status= MOTOR_INIT_STATE;
	switch(status)
	{
		case STOP:
		MOTOR_Stop(M1);
		MOTOR_Stop(M2);
		MOTOR_Stop(M3);
		MOTOR_Stop(M4);
		break;
		
		case CW:
		MOTOR_CW(M1);
		MOTOR_CW(M2);
		MOTOR_CW(M3);
		MOTOR_CW(M4);
		break;
		case CCW:
		MOTOR_CCW(M1);
		MOTOR_CCW(M2);
		MOTOR_CCW(M3);
		MOTOR_CCW(M4);
	}
}