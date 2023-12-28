#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define RS PINA1
#define EN PINA2
#define _8_BIT		1
#define _4_BIT		0

/*********8 bit or 4 bit ******************/

#define LCD_MODE	_4_BIT

#define LCD_PORT	PA

/************ 4 BIT MODE ONLY**********/

#define D4		PINA3
#define D5		PINA4
#define D6		PINA5
#define D7		PINA6

/************ 8 BIT MODE ONLY**********/

#endif /* LCD_CFG_H_ */