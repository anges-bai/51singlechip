#include "reg52.h"			 //´ËÎÄ¼þÖÐ¶¨ÒåÁËµ¥Æ¬»úµÄÒ»Ð©ÌØÊâ¹¦ÄÜ¼Ä´æÆ÷
#include "lcd.h"

typedef unsigned int u16;	  //¶ÔÊý¾ÝÀàÐÍ½øÐÐÉùÃ÷¶¨Òå
typedef unsigned char u8;

int lk=0;
u8 Disp[]="0123456789";


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
	int i;
	Timer1Init();  
	Int0Init();		
	LcdInit();
	
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
		
	}


	
}

   void Timero() interrupt 3
{
	static u16 i;
	TH1=0XFC;	
	TL1=0X18;
	i++;
	if(i==500)
	{
		i=0;lk=0;
	  
	}	
}

void Int0()	interrupt 0		
{

		lk++;
	
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

