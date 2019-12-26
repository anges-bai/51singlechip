#include "reg52.h"			
sbit output=P2^0;
sbit g=P2^3;
sbit d=P2^4;
sbit key=P3^5;
unsigned char u16; 
unsigned int u8;
int k,c=1;
int delay(int k)
{
int i;
while(k--)
{	i=1000;
	while(i--);
}

}
void Init(void) 
{

TMOD=0x01;
TH0=(65536-2000)/256; 
TL0=(65536-2000)%256;
EA=1;
ET0=1;
TR0=1;
}
main()
{Init();
	g=1;
	d=0;
	k=100;
while(1)
{
	if(key==0)
	{ 
	delay(10);
	while(key==0);
	k=k+200;
	} 
  if(k>=1800) k=100; 
}
}
void Timer_0(void) interrupt 1 
{
if(c==1)	
{	
TH0=(65536-k)/256; 
TL0=(65536-k)%256;
	g=1;d=0;		
}	
else	
{	
TH0=(65536-(2000-k))/256; 
TL0=(65536-(2000-k))%256;
g=0;d=0;	
}
c=~c;

}

