#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

int j,k=0;

void delay(u16 k)
{
	while(k--);	
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
	int j;
	Timer1Init(); 
  Int0Init();	
	while(1);
  	
}


void Timer1() interrupt 3
{

	TH1=0XFC;	
	TL1=0X18;
	j++;
	if(j==1000)
	{
		j=0;k=0;
		
		
	}	
}
void Int0()	interrupt 0		
{
	k++;	 
	
}
