#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"
#include "Utils.h"
#define F_CPU 8000000
#include <util/delay.h>

u8 G_line, G_cell;
static u8 LCD_StrLen(u8 str[]);

#if LCD_MODE==_8_BIT

void WriteIns(u8 ins)
{
		DIO_WritePin(RS,LOW);
		DIO_WritePort(LCD_PORT,ins);			//8 BIT 16
		DIO_WritePin(EN,HIGH);
		_delay_ms(1);
		DIO_WritePin(EN,LOW);
		_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);			//8 BIT 16
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
		_delay_ms(50);
		WriteIns(0x38);		//0b00111000
		WriteIns(0x0c);		//0x0e ,0x0f
		WriteIns(0x01);		//clear screen
		_delay_ms(1);
		WriteIns(0x06);		
}

#else

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);

	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);

	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);		
	WriteIns(0x0c);		//0x0e ,0x0f
	WriteIns(0x01);		//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}
void LCD_WriteChar(c8 ch)
{
	WriteData(ch);
}
void LCD_GoTo(u8 line,u8 cell)
{
	G_line=line;
	G_cell=cell;
	if(line==0)
	{
		WriteIns(0x80+cell);
	}
	else if(line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}
void LCD_WriteString(u8*str)
{
	u8 i,n;
	if(G_cell>=0 && G_cell<=15 && G_line==0)
	{
			n=G_cell;
			for(i=0;str[i] && n<=15;n++,i++)
			{
				LCD_WriteChar(str[i]);
			}
			if(n==15)
			{
			LCD_GoTo(1,0);
			for(;str[i];i++)
			{
				LCD_WriteChar(str[i]);
			}
			}

	}
	else
	{
		for(i=0;str[i];i++)
		{
			LCD_WriteChar(str[i]);
		}

	}
}
void LCD_WriteNumber(s32 num)
{
	c8 str[20];
	u8 i=0;
	if(num<0)
	{
		LCD_WriteChar('-');
		num=-num;
	}
	else if(num==0)
	{
		LCD_WriteChar('0');
		return ;
	}
	while(num)
	{
		str[i]=(s32)((num%10))+'0';
		i++;
		num/=10;
	}
	for(;i>0;i--)
	{
		LCD_WriteChar(str[i-1]);
	}
}
/*void LCD_WriteBinary(u8 num)
{
	u8 str[8],temp,j=7;
	for(int i=0;i<8;i++)
	{
		str[i]=(READ_BIT(num,i)+'0');
	}
	for(int i=0;i<=j;i++)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;
		j--;
	}
	for(int i=0;i<8;i++)
	{
		LCD_WriteChar(str[i]);
	}
}*/
void LCD_Write_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar((num%10)+'0');

}
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}


void LCD_WriteHex(u8 num)
{
	LCD_WriteString((u8*)"0X");
		if(((num&0xf0)>>4)>9)
		{
			switch ((num&0xf0)>>4)
			{
				case 10:
				LCD_WriteChar('A');
				break;
				case 11:
				LCD_WriteChar('B');
				break;
				case 12:
				LCD_WriteChar('C');
				break;
				case 13:
				LCD_WriteChar('D');
				break;
				case 14:
				LCD_WriteChar('E');
				break;
				case 15:
				LCD_WriteChar('F');
				break;
			}
		}
		else if(((num&0xf0)>>4)<=9)
		{
			LCD_WriteNumber((num&0xf0)>>4);
		}
		if((num&0x0f)>9)
		{
			switch (num&0x0f)
			{
				case 10:
				LCD_WriteChar('A');
				break;
				case 11:
				LCD_WriteChar('B');
				break;
				case 12:
				LCD_WriteChar('C');
				break;
				case 13:
				LCD_WriteChar('D');
				break;
				case 14:
				LCD_WriteChar('E');
				break;
				case 15:
				LCD_WriteChar('F');
				break;
			}
		}
		else if((num&0x0f)<=9)
		{
			LCD_WriteNumber(num&0x0f);
		}
}

void LCD_AdvDisplay(u8* str)
{
	u8 i=0,n=0,c=0,len;
	static u8 Mode=0,flag=0;
	i=LCD_StrLen(str);
	n=len=i-1;
	while(i+16)
	{
		if(i>0 && flag==0)
		{
			n=i;
			LCD_GoTo(Mode,0);
			for(;str[n];n++)
			{
				LCD_WriteChar(str[n]);

			}
			_delay_ms(250);
			i--;
		}
		if(i==0)
		{
			n=c;
			flag=1;
			LCD_GoTo(Mode,0);
			while(n)
			{
				LCD_WriteChar(' ');
				n--;
			}
			LCD_WriteString(str);
			_delay_ms(250);
			c++;
			if(c==17)
			{
				c=0;
				flag=0;
				i=len;
				Mode^=1;
			}
		}
	}
		
}
void LCD_WriteStringGoTo(u8 line,u8 cell, u8* str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}
void LCD_ClearPosition(u8 line,u8 cell,u8 NoCells)
{
	LCD_GoTo(line,cell);
	for(u8 i=0;i<NoCells;i++)
	{
		LCD_WriteChar(' ');
	}
}
static u8 LCD_StrLen(u8 str[])
{
	u8 n=0;
	for(u8 i=0;str[i];i++)
	{
		n++;
	}
	return n;
}
void LCD_CustomCharacter(u8 address,u8* pattern)
{
	WriteIns(0x40+address*8);
	for(u8 i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}