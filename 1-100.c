#include "reg52.h"			 

typedef unsigned int u16;	  
typedef unsigned char u8;

sbit key1=P2^3;
sbit key2=P2^4;
sbit key3=P2^5;
sbit beep=P2^2;
sbit key4=P3^2;

u8 code smgduan[10]={0xe7,0x21,0xcb,0x6b,0x2d,0x6e,0xee,0x23,0xef,0x6f};
int num=0;
u16 i;

void delay(int i)
{
 while(i--);
}
void Timer1Init()
{
	TMOD|=0X10;

	TH1=0XFC;	
	TL1=0X18;	
	ET1=1;
	EA=1;
	TR1=1;		
}
void Int0Init()
{
	
	IT0=1;
	EX0=1;	
	EA=1;
}


void main()
{	
	
	Timer1Init();  
	Int0Init();	

while(1)
 {
	 key1=1,key2=0,key3=1;
   P1=smgduan[num%10];
   delay(100);
   P0=0x00;
	 
	 key1=1,key2=1,key3=0;
	 P1=smgduan[num/10%10];
	 delay(100);
	 P0=0x00;
	 
	 key1=0,key2=1,key3=1;
	 P1=smgduan[num/100];
	 delay(100);
	 P0=0x00;
 }
}
void Timer1() interrupt 3
{
	static u16 i;
	TH1=0XFC;	//¸ø¶¨Ê±Æ÷¸³³õÖµ£¬¶¨Ê±1ms
	TL1=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		num++;
		if(num==100)num=0;
		
		if(num>=95)
		{
			beep=1;
		  delay(10);
			beep=0;
		}


	}	
}

void Int0()	interrupt 0		
{
	delay(1000);	
	if(key4==0)
	{
		TR1=~TR1;
	}
}
