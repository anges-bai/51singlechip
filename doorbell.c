#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
sbit beep=P1^5;
sbit k1=P3^1;
u8 ding,dong,flag,stop;
u16 n;
void delay(u16 i)
{
	while(i--);
}
void time0init()	  //¶¨Ê±Æ÷0³õÊ¼»¯
{
	TMOD=0X01;	 //¶¨Ê±Æ÷0 ·½Ê½1
	TH0=0Xff;
	TL0=0X06; //¶¨Ê±250us
//	TR0=1;
	EA=1;
	ET0=1;
}
void biaohaoinit()	   //¸÷¸ö±êºÅ³õÊ¼»¯
{
	ding=0;		//¶£ÉùÒô  ¼ÆÊý±êÖ¾
	dong=0;		//ßËÉùÒô  ¼ÆÊý±êÖ¾
	n=0;		//¶¨Ê±0.5s±êÖ¾
	flag=0;
	stop=0;	   //½áÊø±êÖ¾
}
void main()
{
	time0init();
	biaohaoinit();
	while(1)
	{
		if(k1==0)	   //ÅÐ¶Ï°´¼üÊÇ·ñ°´ÏÂ
		{
			delay(1000);  //Ïû¶¶
			if(k1==0)
			{
				TR0=1;	//´ò¿ª¶¨Ê±Æ÷0
				while(!stop);
			}
		}	
	}	
}
void time0() interrupt 1
{
	n++;
	TH0=0Xff;
	TL0=0X06; //250us
	if(n==2000)		//¶¨Ê±0.5s  ¶£Ïì0.5Ãë£¬ßËÏì0.5Ãë
	{
		n=0;
		if(flag==0)
		{
			flag=~flag;
		}
		else
		{
			flag=0;
			stop=1;
			TR0=0;	  //¹Ø±Õ¶¨Ê±Æ÷0
		}
	}
	if(flag==0)
	{					   //Í¨¹ý¸Ä±ä¶¨Ê±¼ÆÊýÊ±¼ä¿ÉÒÔ¸Ä±äÃÅÁåµÄÉùÒô
		ding++;			  //¶£
		if(ding==1)
		{
			ding=0;
			beep=~beep;
		}
	}
	else
	{
		dong++;
		if(dong==2)		  //ßË
		{
			dong=0;
			beep=~beep;
		}	
	}
}
