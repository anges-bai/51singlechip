#include "reg52.h"			 
#include "lcd.h"
sbit output=P2^0;
sbit g=P2^3;
sbit d=P2^4;
sbit key=P3^5;

typedef unsigned int u16;	  
typedef unsigned char u8;

int lk=0,num=0,c1=0,c2=0;
u8 Disp[]="0123456789";
int k,c=1;
int delay(int k)
{
int j;
while(k--)
{	
	j=10;
	while(j--);
}

}
void delay_(int i)
{
 while(i--);
}
	
void Init(void) 
{

TMOD|=0x01;
TH0=(65536-2000)/256; 
TL0=(65536-2000)%256;
EA=1;
ET0=1;
TR0=1;
}


//void Timer1Init()
//{
//	TMOD|=0X10;

//	TH1=0XFC;	
//	TL1=0X18;	
//	ET1=1;
//	EA=1;
//	TR1=1;		
//}

void Int0Init()
{
	
	IT0=1;
	EX0=1;	
	EA=1;
}
void UsartInit()
{
	SCON=0X50;			
	TMOD=0X20;			
	PCON=0X80;			
	TH1=0XF3;				
	TL1=0XF3;
	ES=1;						
	EA=1;					
	TR1=1;					
}	
int PI(int get,int set)
 {
	 static float Bias,Last_bias;
	 static int PWM;
	 Bias=set-get;
	 PWM+=6*Bias+0.8*(Bias-Last_bias);
	 Last_bias=Bias;
	 if(PWM<=0)
		 PWM=1;
	 return PWM;
 }

void main()
{	
	int i;
	g=1;
	d=0;
	c2=1;
//	Timer1Init(); 
	UsartInit();
  Init();	
	Int0Init();		
	LcdInit();
	PI();
	while(1)
	{
		LcdWriteCom(0x80+0x04); 
		LcdWriteData(Disp[lk%10]);
		
		LcdWriteCom(0x80+0x03); 
		LcdWriteData(Disp[lk/10%10]);	
		
		LcdWriteCom(0x80+0x02); 
		LcdWriteData(Disp[lk/100%10]);	
		
	  LcdWriteCom(0x80+0x01); 
		LcdWriteData(Disp[lk/1000%10]);	
	
		delay(100);
		if(key==0)
	{ 
	delay(10);
	while(key==0);
  c2=c2+2;
	} 
  if(c2>=50) c2=1;
	}
	
	

}

//   void Timero() interrupt 3
//{
//	static u16 i;
//	TH1=0XFC;	
//	TL1=0X18;
//	i++;
//	if(i==500)
//	{
//		i=0;//lk=0;
//	  
//	}	
//}
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
TH0=(65536-(10000-k))/256; 
TL0=(65536-(10000-k))%256;
g=0;d=0;	
}
c=~c;
if(c==1)c1++;
if(c1>2)
{	
lk=num,num=0,c1=0;
	
k=PI(lk,c2);
	
	
}
}

void Int0()	interrupt 0		
{

		num++;
	
}
void Usart() interrupt 4
{ 
	
	RI=0;
	SBUF=Disp[lk/10];
	SBUF=Disp[lk%10];
	while(!TI);
	TI=0;						 

}
#include "lcd.h"

/*******************************************************************************
* º¯ Êý Ãû         : Lcd1602_Delay1ms
* º¯Êý¹¦ÄÜ		   : ÑÓÊ±º¯Êý£¬ÑÓÊ±1ms
* Êä    Èë         : c
* Êä    ³ö         : ÎÞ
* Ëµ    Ãû         : ¸Ãº¯ÊýÊÇÔÚ12MHZ¾§ÕñÏÂ£¬12·ÖÆµµ¥Æ¬»úµÄÑÓÊ±¡£
*******************************************************************************/

void Lcd1602_Delay1ms(uint c)   //Îó²î 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

/*******************************************************************************
* º¯ Êý Ãû         : LcdWriteCom
* º¯Êý¹¦ÄÜ		   : ÏòLCDÐ´ÈëÒ»¸ö×Ö½ÚµÄÃüÁî
* Êä    Èë         : com
* Êä    ³ö         : ÎÞ
*******************************************************************************/
//#ifndef 	LCD1602_4PINS	 //µ±Ã»ÓÐ¶¨ÒåÕâ¸öLCD1602_4PINSÊ±
//void LcdWriteCom(uchar com)	  //Ð´ÈëÃüÁî
//{
//	LCD1602_E = 0;     //Ê¹ÄÜ
//	LCD1602_RS = 0;	   //Ñ¡Ôñ·¢ËÍÃüÁî
//	LCD1602_RW = 0;	   //Ñ¡ÔñÐ´Èë
//	
//	LCD1602_DATAPINS = com;     //·ÅÈëÃüÁî
//	Lcd1602_Delay1ms(1);		//µÈ´ýÊý¾ÝÎÈ¶¨

//	LCD1602_E = 1;	          //Ð´ÈëÊ±Ðò
//	Lcd1602_Delay1ms(5);	  //±£³ÖÊ±¼ä
//	LCD1602_E = 0;
//}
//#else 
void LcdWriteCom(uchar com)	  //Ð´ÈëÃüÁî
{
	LCD1602_E = 0;	 //Ê¹ÄÜÇåÁã
	LCD1602_RS = 0;	 //Ñ¡ÔñÐ´ÈëÃüÁî
	LCD1602_RW = 0;	 //Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = com;	//ÓÉÓÚ4Î»µÄ½ÓÏßÊÇ½Óµ½P0¿ÚµÄ¸ßËÄÎ»£¬ËùÒÔ´«ËÍ¸ßËÄÎ»²»ÓÃ¸Ä
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //·¢ËÍµÍËÄÎ»
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* º¯ Êý Ãû         : LcdWriteData
* º¯Êý¹¦ÄÜ		   : ÏòLCDÐ´ÈëÒ»¸ö×Ö½ÚµÄÊý¾Ý
* Êä    Èë         : dat
* Êä    ³ö         : ÎÞ
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//Ð´ÈëÊý¾Ý
{
	LCD1602_E = 0;	//Ê¹ÄÜÇåÁã
	LCD1602_RS = 1;	//Ñ¡ÔñÊäÈëÊý¾Ý
	LCD1602_RW = 0;	//Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = dat; //Ð´ÈëÊý¾Ý
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);   //±£³ÖÊ±¼ä
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//Ð´ÈëÊý¾Ý
{
	LCD1602_E = 0;	  //Ê¹ÄÜÇåÁã
	LCD1602_RS = 1;	  //Ñ¡ÔñÐ´ÈëÊý¾Ý
	LCD1602_RW = 0;	  //Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = dat;	//ÓÉÓÚ4Î»µÄ½ÓÏßÊÇ½Óµ½P0¿ÚµÄ¸ßËÄÎ»£¬ËùÒÔ´«ËÍ¸ßËÄÎ»²»ÓÃ¸Ä
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //Ð´ÈëµÍËÄÎ»
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* º¯ Êý Ãû       : LcdInit()
* º¯Êý¹¦ÄÜ		 : ³õÊ¼»¯LCDÆÁ
* Êä    Èë       : ÎÞ
* Êä    ³ö       : ÎÞ
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD³õÊ¼»¯×Ó³ÌÐò
{
 	LcdWriteCom(0x38);  //¿ªÏÔÊ¾
	LcdWriteCom(0x0c);  //¿ªÏÔÊ¾²»ÏÔÊ¾¹â±ê
	LcdWriteCom(0x06);  //Ð´Ò»¸öÖ¸Õë¼Ó1
	LcdWriteCom(0x01);  //ÇåÆÁ
	LcdWriteCom(0x80);  //ÉèÖÃÊý¾ÝÖ¸ÕëÆðµã
}
#else
void LcdInit()						  //LCD³õÊ¼»¯×Ó³ÌÐò
{
	LcdWriteCom(0x32);	 //½«8Î»×ÜÏß×ªÎª4Î»×ÜÏß
	LcdWriteCom(0x28);	 //ÔÚËÄÎ»ÏßÏÂµÄ³õÊ¼»¯
	LcdWriteCom(0x0c);  //¿ªÏÔÊ¾²»ÏÔÊ¾¹â±ê
	LcdWriteCom(0x06);  //Ð´Ò»¸öÖ¸Õë¼Ó1
	LcdWriteCom(0x01);  //ÇåÆÁ
	LcdWriteCom(0x80);  //ÉèÖÃÊý¾ÝÖ¸ÕëÆðµã
}
#endif
