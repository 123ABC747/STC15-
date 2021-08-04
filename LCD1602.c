#ifndef MAIN_Fosc
#define MAIN_Fosc 12000000L
#endif

#include "STC15Fxxxx.H"
#include "LCD1602.h"
sbit RS=P1^6;					 
sbit EN=P1^7;
void delay(unsigned int xms)	 
{
	int a,b;
	for(a=xms;a>0;a--)
		for(b=110;b>0;b--);
}
void Pin_Mode(void)
{
	P0M1 = 0x00;
	P0M0 = 0x00;
	P1M1 = 0x00;
	P1M0 = 0x00;
}

void write_com(unsigned char com)		 
{
	RS=0;
	P0=com;	
	delay(1);
	EN=1;
	delay(1);						 			  
	EN=0;
}

void write_date(unsigned char date)		 
{
	RS=1;
	P0=date;
	delay(1);
	EN=1;
	delay(1);
	EN=0;
}

void init_lcd()				 
{								  
	EN=0;					 
	write_com(0x0c);
	delay(5);
	write_com(0x38);
  delay(5);	
	write_com(0x01);	
  delay(5);	
	write_com(0x06);	
  delay(5);	
	write_com(0x80);			 
}
void LCD_Clear(void)
{
	write_com(0x01);
	delay(5);
}