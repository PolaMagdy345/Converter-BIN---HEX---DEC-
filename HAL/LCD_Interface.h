#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_



void LCD_Init(void);
void LCD_Clear(void);
void LCD_WriteString(u8* str);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_Write_4D(u16 num);
void LCD_WriteChar(c8 ch);
void LCD_CustomCharacter(u8 address,u8* pattern);   
void LCD_AdvDisplay(u8* str);
/***line 0:1 cell 0:15***/
void LCD_GoTo(u8 line,u8 cell);
void LCD_WriteStringGoTo(u8 line,u8 cell, u8* str);
void LCD_ClearPosition(u8 line,u8 cell,u8 NoCells);





#endif /* LCD_INTERFACE_H_ */