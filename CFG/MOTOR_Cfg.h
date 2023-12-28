#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

#define M1_IN1	PINB0
#define M1_IN2	PINB1

#define M2_IN1	PINB2
#define M2_IN2	PINB3

#define M3_IN1	PINB4
#define M3_IN2	PINB5

#define M4_IN1	PINB6
#define M4_IN2	PINB7


/********************************* IN1	  IN2 */
DIO_Pin_type MotorPinsArr[4][2]={{M1_IN1,M1_IN2},	/* M1*/
								 {M2_IN1,M2_IN2},	/* M2*/
								 {M3_IN1,M3_IN2},	/* M3*/
								 {M4_IN1,M4_IN2} 	/* M4*/
								};


#define MOTOR_INIT_STATE	STOP		/********STOP for stop******CW for CLOCK WISE direction******CCW COUNTER CLOCK WISE direction***************/


#endif /* MOTOR_CFG_H_ */