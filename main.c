#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "Car_Interface.h"
#include "KeyPad_Interface.h"

typedef enum{
	Binary=1,
	Decimal,
	Hex
	}Mode_t;

int main(void)
{

	DIO_Init();
	MOTOR_Init();
	LCD_Init();
	KEYPAD_Init();
	LCD_Clear();
	LCD_GoTo(0,4);
	LCD_WriteString((u8*)"Hello");
	LCD_GoTo(1,0);
	LCD_WriteString((u8*)"ConverterBy Pola");
	DIO_WritePin(PINC5,HIGH);
	_delay_ms(50);
	DIO_WritePin(PINC5,LOW);
	_delay_ms(100);
	DIO_WritePin(PINC5,HIGH);
	_delay_ms(50);
	DIO_WritePin(PINC5,LOW);
	_delay_ms(1000);
	LCD_Clear();
	Mode_t Mode=0;
	u8	k=NO_KEY,BIN,HEX=0,DEC=0,flagF=0,flagT=0,c=128,New_Operation=0,count=0;
    while (1)
	{
		k=KEYPAD_Getkey();
		if(Mode==0)
		{
			LCD_GoTo(0,0);
			LCD_WriteString((u8*)"Convert From ");
			LCD_GoTo(1,0);
			LCD_WriteString((u8*)"1.B  2.D  3.H");

		}
		if(k!=NO_KEY)
		{
			if(Mode==0 && flagT==0 && flagF==0)
			{
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"1.B  2.D  3.H");
				if(k=='1' || k=='2' || k=='3')
				Mode=k-'0';
			}
			if(Mode==Binary && flagF==0 && flagT==0)			/*************BINARY MODE*************/
			{
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From B>");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"                ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"2.D 3.H");
				if(k==Decimal+'0')
				{
					flagT=1;
					flagF=1;
					LCD_Clear();
					LCD_GoTo(0,0);
					LCD_WriteString((u8*)"B:");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"D:");
					LCD_GoTo(0,2);
					c=128;
				}
				else if(k==Hex+'0')
				{
					flagT=1;
					flagF=0;
					LCD_Clear();
					LCD_GoTo(0,0);
					LCD_WriteString((u8*)"B:");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"H:");
					LCD_GoTo(0,2);
					c=128;
				}
				else if(k=='C')
				{
					flagF=0;
					flagT=0;
					Mode=0;
					LCD_Clear();
				}
			}
			if(Mode==Binary && flagT==1 && flagF==1)			/**BINARY TO DECIMAL**/
			{
				if((k=='0' || k=='1' ) && c!=0)
				{
					if(New_Operation==1)
					{
						LCD_GoTo(0,2);
						LCD_WriteString((u8*)"         ");
						LCD_GoTo(0,2);
						c=128;
						DEC=0;
						New_Operation=0;
					}
					LCD_WriteChar(k);
					BIN=k-'0';
					DEC+=(BIN*c);
					c/=2;
				}
				else if(k=='=')
				{
					LCD_GoTo(1,2);
					LCD_WriteString((u8*)"     ");
					LCD_GoTo(1,2);
					LCD_WriteNumber(DEC);
					New_Operation=1;
					LCD_GoTo(0,2);
					c=128;
				}
				else if(k=='C')
				{
					flagF=0;
					flagT=0;
					LCD_GoTo(0,0);
					LCD_WriteString((u8*)"Convert From B>");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"                ");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"2.D 3.H");
				}
			}
			if(Mode==Binary && flagT==1 && flagF==0)			/**BINARY TO HEX**/
			{
				if((k=='0' || k=='1' ) && c!=0)
				{
					if(New_Operation==1)
					{
						LCD_GoTo(0,2);
						LCD_WriteString((u8*)"         ");
						LCD_GoTo(0,2);
						c=128;
						DEC=0;
						New_Operation=0;
					}
					LCD_WriteChar(k);
					BIN=k-'0';
					DEC+=(BIN*c);
					c/=2;
				}
				else if(k=='=')
				{
					LCD_GoTo(1,2);
					LCD_WriteHex(DEC);
					New_Operation=1;
					LCD_GoTo(0,2);
					c=128;
				}
				else if(k=='C')
				{
					flagF=0;
					flagT=0;
					LCD_GoTo(0,0);
					LCD_WriteString((u8*)"Convert From B>");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"                ");
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"2.D 3.H");
				}
			}
		if(Mode==Decimal && flagF==0 && flagT==0)			/*************DECIMAL MODE*************/
		{
			LCD_GoTo(0,0);
			LCD_WriteString((u8*)"Convert From D>");
			LCD_GoTo(1,0);
			LCD_WriteString((u8*)"                ");
			LCD_GoTo(1,0);
			LCD_WriteString((u8*)"1.B 3.H");
			if(k==Binary+'0')
			{
				DEC=0;
				flagT=1;
				flagF=1;
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"D: ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"B:");
				LCD_GoTo(0,2);
				k=NO_KEY;
			}
			else if(k==Hex+'0')
			{
				DEC=0;
				flagT=1;
				flagF=0;
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"D:");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"H:");
				LCD_GoTo(0,2);
				k=NO_KEY;
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				Mode=0;
				LCD_Clear();
			}
		}
		if(Mode==Decimal && flagT==1 && flagF==1)			/**DECIMAL TO BINARY**/
		{
			if(k>='0' && k<='9')
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,2);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,2);
					DEC=0;
					New_Operation=0;
				}
				if(DEC<=25)
				{
					if(DEC==25 && (k-'0')<=5)
					{
						DEC=(DEC*10)+(k-'0');
						LCD_WriteChar(k);
					}
					else if(DEC<25)
					{
						DEC=(DEC*10)+(k-'0');
						LCD_WriteChar(k);
					}
				}
			}
			else if(k=='=')
			{
				LCD_GoTo(1,2);
				LCD_WriteBinary(DEC);
				New_Operation=1;
				LCD_GoTo(0,2);
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From D>");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"                ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"1.B 3.H");
			}
		}
		if(Mode==Decimal && flagT==1 && flagF==0)			/**DECIMAL TO HEX**/
		{
			if(k>='0' && k<='9')
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,2);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,2);
					DEC=0;
					New_Operation=0;
				}
				if(DEC<=25)
				{
					if(DEC==25 && (k-'0')<=5)
					{
						DEC=(DEC*10)+(k-'0');
						LCD_WriteChar(k);
					}
					else if(DEC<25)
					{
						DEC=(DEC*10)+(k-'0');
						LCD_WriteChar(k);
					}
				}
			}
			else if(k=='=')
			{
				LCD_GoTo(1,2);
				LCD_WriteHex(DEC);
				New_Operation=1;
				LCD_GoTo(0,2);
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				Mode=Decimal;
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From D>");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"                ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"1.B 3.H");
			}
		}
		if(Mode==Hex && flagF==0 && flagT==0)			/*************HEX MODE*************/
		{
			LCD_GoTo(0,0);
			LCD_WriteString((u8*)"Convert From H>");
			LCD_GoTo(1,0);
			LCD_WriteString((u8*)"                ");
			LCD_GoTo(1,0);
			LCD_WriteString((u8*)"1.B 2.D");
			if(k==Binary+'0')
			{
				flagT=1;
				flagF=1;
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"H:0X");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"B:");
				LCD_GoTo(0,4);
				k=NO_KEY;
			}
			else if(k==Decimal+'0')
			{
				flagT=1;
				flagF=0;
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"H:0X");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"D:");
				LCD_GoTo(0,4);
				k=NO_KEY;
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				Mode=0;
				LCD_Clear();
			}
		}
		if(Mode==Hex && flagT==1 && flagF==1)			/**HEX TO BINARY**/
		{
			if(k>='0' && k<='9' && count==0)
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,4);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,4);
					HEX=0;
					New_Operation=0;
				}
				count++;
				HEX|=(k-'0')<<4;
				LCD_WriteChar(k);
			}
			else if((k=='+'|| k=='-'|| k=='*'|| k=='/') && count==1)
			{
				switch (k)
				{
					case '+':
					LCD_WriteChar('A');
					HEX|=10;
					break;
					
					case '-':
					LCD_WriteChar('B');
					HEX|=11;
					break;
					
					case '*':
					LCD_WriteChar('C');
					HEX|=12;
					break;
					
					case '/':
					LCD_WriteChar('D');
					HEX|=13;
					break;
				}
				count++;
			}
			else if((k=='+'|| k=='-'|| k=='*'|| k=='/') && count==0)
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,4);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,4);
					HEX=0;
					New_Operation=0;
				}
				switch (k)
				{
					case '+':
					LCD_WriteChar('A');
					HEX|=10<<4;
					break;
					
					case '-':
					LCD_WriteChar('B');
					HEX|=11<<4;
					break;
					
					case '*':
					LCD_WriteChar('C');
					HEX|=12<<4;
					break;

					case '/':
					LCD_WriteChar('D');
					HEX|=13<<4;
					break;
				}
				count++;
			}
			else if(k>='0' && k<='9' && count==1)
			{
				count++;
				HEX|=(k-'0');
				LCD_WriteChar(k);
			}
			else if(k=='=')
			{
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"B:   ");
				LCD_GoTo(1,2);
				if(count==1)
				{
					LCD_WriteBinary(HEX>>4);
				}
				else
				LCD_WriteBinary(HEX);
				New_Operation=1;
				LCD_GoTo(0,4);
				count=0;
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From H>");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"                ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"1.B 2.D");
				count=0;
			}
		}
		if(Mode==Hex && flagT==1 && flagF==0)			/**HEX TO DECIMAL**/
		{
			if(k>='0' && k<='9' && count==0)
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,4);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,4);
					HEX=0;
					New_Operation=0;
				}
				count++;
				HEX|=((k-'0')<<4);
				LCD_WriteChar(k);
			}
			else if((k=='+'|| k=='-'|| k=='*'|| k=='/') && count==1)
			{
				switch (k)
				{
					case '+':
					LCD_WriteChar('A');
					HEX|=10;
					break;
					
					case '-':
					LCD_WriteChar('B');
					HEX|=11;
					break;
					
					case '*':
					LCD_WriteChar('C');
					HEX|=12;
					break;
					
					case '/':
					LCD_WriteChar('D');
					HEX|=13;
					break;
				}
					count++;
			}
			else if((k=='+'|| k=='-'|| k=='*'|| k=='/') && count==0)
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,4);
					LCD_WriteString((u8*)"       ");
					LCD_GoTo(0,4);
					HEX=0;
					New_Operation=0;
				}
				switch (k)
				{
					case '+':
					LCD_WriteChar('A');
					HEX|=10<<4;
					break;
					
					case '-':
					LCD_WriteChar('B');
					HEX|=11<<4;
					break;
					
					case '*':
					LCD_WriteChar('C');
					HEX|=12<<4;
					break;

					case '/':
					LCD_WriteChar('D');
					HEX|=13<<4;
					break;
				}
				count++;
			}
			else if(k>='0' && k<='9' && count==1)
			{
				if(New_Operation==1)
				{
					LCD_GoTo(0,4);
					LCD_WriteString((u8*)"      ");
					LCD_GoTo(0,4);
					HEX=0;
					New_Operation=0;
				}
				count++;
				HEX|=(k-'0');
				LCD_WriteChar(k);
			}
			else if(k=='=')
			{
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"D:   ");
				LCD_GoTo(1,2);
				if(count==1)
				{
				LCD_WriteNumber(HEX>>4);
				}
				else
				LCD_WriteNumber(HEX);
				New_Operation=1;
				LCD_GoTo(0,4);
				count=0;
			}
			else if(k=='C')
			{
				flagF=0;
				flagT=0;
				LCD_GoTo(0,0);
				LCD_WriteString((u8*)"Convert From H>");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"                ");
				LCD_GoTo(1,0);
				LCD_WriteString((u8*)"1.B 2.D");
				count=0;
			}
		}
			DIO_WritePin(PINC5,HIGH);
			_delay_ms(30);
			DIO_WritePin(PINC5,LOW);
	}
	}
}

