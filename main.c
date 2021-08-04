#define MAIN_Fosc 12000000L
#include "LCD1602.h"
#include "STC15Fxxxx.H"
#define uchar unsigned char			    
#define uint unsigned int

sbit s1=P1^0; 						   
sbit s2=P1^1;
sbit s3=P1^2;
sbit s4=P1^3;
sbit s5=P1^4;
sbit s6=P1^5;
sbit s7=P3^0;
sbit FMQ=P3^6;									   
char num,boxing,u;					  
int pinlv=100,bujin=10,bujin1=10;
int chh=20;
uchar code table[]="0123456789";		 
uchar code table1[]="pinlv:boxing:";
unsigned long int m;
int n=0;
int a,b,h,num1;
int z=0;
uchar shi0,ge0,ge1,shi1,bai1,qian1,wan1;
uint c=0;
uint d=0;
uchar code sin[64]={
128,140,152,164,176,187,198,208,217,226,233,240,245,249,252,254,255,254,252,249,245,240,233,226,217,208,
198,187,176,164,152,140,127,115,103,91,79,68,57,47,38,29,22,15,10,6,3,1,1,1,3,6,10,15,22,29,38,47,57,68,79,91,103,115
};					  
uchar code juxing[64]={
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};					  
uchar code juchi[64]={
0,4,8,12,16,20,24,28,32,36,40,45,49,53,57,61,65,69,73,77,81,85,89,93,97,101,105,109,113,117,121,125,130,134,138,142,
146,150,154,158,162,166,170,174,178,182,186,190,194,198,202,206,210,215,219,223,227,231,235,239,243,247,251,255
};					  
uchar code sanjiao[64]={
0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,248,
248,240,232,224,216,208,200,192,184,176,168,160,152,144,136,128,120,112,104,96,88,80,72,64,56,48,40,32,24,16,8,0
};						 
void Delay_500us(void)
{
	int t;
	for(t=0; t<550; t++)
	;
}
void Beep(void)
{
	int i;
	for(i=0; i<10; i++)
	{
		Delay_500us();
		FMQ = ~FMQ;
	}
}
void initclock()			    
{
	uint i;
	TMOD=0x01;
	TH0=a;
	TL0=b;
	EA=1;
	ET0=1;
	TR0=1;
	write_com(0x80);
	delay(500);
	for(i=6;i<13;i++)			    
	{
		write_date(table1[i]);
		delay(2);
	}
	write_com(0x80+0x40);
	for(i=0;i<6;i++)
	{
		write_date(table1[i]);
		delay(2);
	}
	write_com(0x80+7);
		write_date('s');
		write_date('i');
		write_date('n');
		write_date(' ');
		write_date(' ');
		write_date(' ');
		write_date(' ');
		write_com(0x80+0x40+0xa);
		write_date('1');
		write_date('0');
		write_date('0');
		write_date('H');
		delay(2);
		write_date('Z');
		delay(2);
	write_com(0x80+14);
	write_date('2');
	write_date('0');
	delay(2);
}
void display()				   
{
	uchar wan,qian,bai,shi,ge;
	uint a=0;
	a=pinlv;
	wan=a/10000;
	qian=a/1000%10;
	bai=a/100%10;
	shi=a%100/10;
	ge=a%100%10;
	write_com(0x80+0x40+8);
	write_date(table[wan]);
	delay(2);
	write_date(table[qian]);
	delay(2);
	write_date(table[bai]);
	delay(2);
	write_date(table[shi]);
	delay(2);
	write_date(table[ge]);
	delay(2);
	write_date('H');
	delay(2);
	write_date('Z');
	delay(2);

	c=chh;
	shi0=c/10;
	ge0=c%10;
	write_com(0x80+14);
	write_date(table[shi0]);
	delay(2);
	write_date(table[ge0]);
	delay(2);
	if(boxing==0)
	{
		write_com(0x80+7);
		write_date('s');
		write_date('i');
		write_date('n');
		write_date(' ');
		write_date(' ');
		write_date(' ');
		write_date(' ');
	}
	if(boxing==1)
	{
		write_com(0x80+7);
		write_date('j');
		write_date('u');
		write_date('x');
		write_date('i');
		write_date('n');
		write_date('g');
	}

	if(boxing==2)
	{
		write_com(0x80+7);
		write_date('s');
		write_date('a');
		write_date('n');
		write_date('j');
		write_date('i');
		write_date('a');
		write_date('o');
	}
	if(boxing==3)
	{
		write_com(0x80+7);
		write_date('j');
		write_date('u');
		write_date('c');
		write_date('h');
		write_date('i');
		write_date(' ');
		write_date(' ');
	}

}
void keyscan()					 
{
 
	if(s1==0)
	{	 
		EA=0;
		delay(1);
		if(s1==0)
		{
			while(!s1);
			pinlv+=bujin;
			if(pinlv>5000)
			{
				pinlv=5000;
			}
			EA=1;
			display();
			m=65536-(15625/pinlv);
			a=m/256;
			b=m%256;
			Beep();
		}
	}
	if(s2==0)
	{	 
		
		delay(1);
		if(s2==0)
		{
			EA=0;	
			while(!s2);
			pinlv-=bujin;
			if(pinlv<100)
			{
				pinlv=100;
			}
			m=65536-(15625/pinlv);
			a=m/256;
			b=m%256;
			display();	
			EA=1;
			Beep();
		}
	}
	if(s3==0)
	{	 
		delay(1);
		if(s3==0)
		{
			EA=0;
			while(!s3);
			boxing++;
			if(boxing==4)
			{
				boxing=0;
			}
			display();
			EA=1;
			Beep();
		}
	}
	if(s5==0)
	{
		delay(1);
		if(s5==0)
		{
			EA=0;
			while(!s5);
			chh++;
			if(chh>20){
				chh=20;
			}
			display();
			EA=1;
			Beep();
		}
	}
	if(s6==0)
	{
		delay(1);
		if(s6==0)
		{
			EA=0;
			while(!s6);
			chh--;
			if(chh<0)
			{
				chh=0;
			}
			display();
			EA=1;
			Beep();
		}
	}
	if(s7==0)
	{
		delay(1);
		if(s7==0)
		{
			EA=0;
			while(!s7);
			z++;
			if(z==1)
			{
			LCD_Clear();
      delay(500);
			write_com(0x80);
				 write_date('z');delay(1);
				 write_date('h');delay(1);
				 write_date('o');delay(1);
			   write_date('u');delay(1);
				 write_date('q');delay(1);
				 write_date('i');delay(1);
				 write_date(':');delay(1);
			d=1000000/pinlv;
	    wan1=d/10000;
	    qian1=d/1000%10;
	    bai1=d/100%10;
	    shi1=d%100/10;
	    ge1=d%100%10;
			write_com(0x80+7);
			write_date(table[wan1]);
	    delay(1);
			write_date(table[qian1]);
	    delay(1);
	    write_date(table[bai1]);
	    delay(1);
	    write_date(table[shi1]);
	    delay(1);
	    write_date(table[ge1]);
	    delay(1);
			write_com(0x80+12);
			write_date('u');delay(1);
			write_date('s');delay(1);
		}
			if(z==2)
			{
				z=0;
				init_lcd();
				initclock();
				display();
		}
			Beep();
	}
}
	}
void bujindisplay()
{
	uint bai,shi,ge;
	bai=bujin1/100;
	shi=bujin1%100/10;
	ge=bujin1%100%10;
	write_com(0x80+6);
	write_date(table[bai]);
	delay(1);
	write_date(table[shi]);
	delay(1);
	write_date(table[ge]);
	delay(1);
}
void bujinjiance()
{
	if(s4==0)
	{
		delay(3);
		if(s4==0)
		{
			 while(!s4);
			 h++;
			 if(h==1)
			 {
			 	 LCD_Clear();
				 delay(500);
				 write_com(0x80);
				 write_date('b');delay(1);
				 write_date('u');delay(1);
				 write_date('j');delay(1);
				 write_date('i');delay(1);
				 write_date('n');delay(1);
				 write_date(':');delay(1);
				 bujin1=bujin;
				 
				 bujindisplay();
			 }
			 if(h==2)
			 {
			 	h=0;
				bujin=bujin1;
				
				init_lcd();
				initclock();
				display();
			 }
			 Beep();
		}
	}
	if(h==1)
	{
		if(s1==0)
		{
			delay(5);
			if(s1==0)
			{
				while(!s1);
				bujin1++;
				if(bujin1==101)
				{
					bujin1=100;
				}
				bujindisplay();
			}
			Beep();
		}
		if(s2==0)
		{
			delay(5);
			if(s2==0)
			{
				while(!s2);
				bujin1--;
				if(bujin1==0)
				{
					bujin1=100;
				}
				bujindisplay();
			}
			Beep();
		}
	}
}
void main()					  
{	
	Pin_Mode();
	P3M0=0x00;
	P3M1=0x00;
	P2M0=0x00;
	P2M1=0x00;
	init_lcd();
	LCD_Clear();
	m=65536-(15625/pinlv);
	a=m/256;
	b=m%256;
	initclock();
	display();
  
	while(1)
	{ 
		if(h==0)
		{
			keyscan();
		}
		 
		bujinjiance();
		 switch(boxing)
		 {
		 	case 0:	P2=sin[u]*chh/20;
				break;
			case 1:	 P2=juxing[u]*chh/20;
				break;
			case 2:	 	P2=sanjiao[u]*chh/20;
				break;
			case 3:	 	P2=juchi[u]*chh/20;
				break;
		 }
	}
}
void T0_time()interrupt 1		    
{
		TH0=a;
		TL0=b;
	  u++;
	  if(u>=64)
	  u=0;
}

