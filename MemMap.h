#ifndef MEMMAP_H_
#define MEMMAP_H_


/**************************DIO REGISTERS**************************/

#define DDRA	(*(volatile unsigned char*)0x3A)
#define PORTA	(*(volatile unsigned char*)0x3B)
#define PINA	(*(volatile unsigned char*)0x39)

#define DDRB	(*(volatile unsigned char*)0x37)
#define PORTB	(*(volatile unsigned char*)0x38)
#define PINB	(*(volatile unsigned char*)0x36)

#define DDRC	(*(volatile unsigned char*)0x34)
#define PORTC	(*(volatile unsigned char*)0x35)
#define PINC	(*(volatile unsigned char*)0x33)

#define DDRD	(*(volatile unsigned char*)0x31)
#define PORTD	(*(volatile unsigned char*)0x32)
#define PIND	(*(volatile unsigned char*)0x30)



/* ADC_Registers */
#define ADMUX (*(volatile unsigned char*)0x27)

#define ADLAR 5
#define REFS0 6
#define REFS1 7


#define ADCSRA (*(volatile unsigned char*)0x26)
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7

#define ADCL (*(volatile unsigned char*)0x24)
#define ADCH (*(volatile unsigned char*)0x25)



#endif /* MEMMAP_H_ */