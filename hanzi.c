//¸Ã°å×ÓÉÏµÄµãÕóÎª8*8£¬Ö»ÄÜÏÔÊ¾¼òµ¥µÄÒ»Ð©ºº×Ó£¬Èç¹ûÒªÏÔÊ¾ÕæÕýµÄºº×Ö
//Í¨¹ýÈ¡Ä£Èí¼þÈ¡µÄ¿ÉÒÔÑ¡Ôñ16*16µãÕóµÄ°å×Ó

#include<reg51.h>
#include<intrins.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

//--¶¨ÒåÒªÊ¹ÓÃµÄIO¿Ú--//
#define COMMONPORTS		P0

//--ÁÐÑ¡Í¨¿ØÖÆ--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

//--µãÕó×ÖÂë--//
unsigned char code CHARCODE[4][8]=
{

0x00,0x12,0x14,0x78,0x14,0x12,0x00,0x00,  //´ó
0x00,0x08,0x12,0x01,0xFF,0x00,0x10,0x08,   //Ð¡
0x7F,0x41,0x5D,0x55,0x5D,0x41,0x7F,0x00,  //»Ø

{0x7C,0x48,0x48,0xFF,0x48,0x48,0x7C,0x00}  //ÖÐ

};
void delay(unsigned int time)
{
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++);
}

/*******************************************************************************
* º¯ÊýÃû         : Hc595SendByte(unsigned char dat)
* º¯Êý¹¦ÄÜ		   : Ïë74H595·¢ËÍÒ»¸ö×Ö½ÚµÄÊý¾Ý
* ÊäÈë           : ÎÞ
* Êä³ö         	 : ÎÞ
*******************************************************************************/
void Hc595SendByte(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}
/*******************************************************************************
* º¯ÊýÃû         : main
* º¯Êý¹¦ÄÜ		   : Ö÷º¯Êý
* ÊäÈë           : ÎÞ
* Êä³ö         	 : ÎÞ
*******************************************************************************/

void main()
{	
 	unsigned char tab, j;
	unsigned int  i;

	while(1)
	{	
		for(i= 0; i<50; i++ )   //Á½¸ö×ÖÖ®¼äµÄÉ¨Ãè¼ä¸ôÊ±¼ä
		{
			for(tab=0;tab<8;tab++)
			{	

				Hc595SendByte(0x00);			     //ÏûÒþ																
				COMMONPORTS	= TAB[tab];				 //Êä³ö×ÖÂë	
				Hc595SendByte(CHARCODE[j][tab]);	
				delay(2);		
			}
			 
		}
		j++;
		if(j == 4)
		{
			j = 0;
		}
	}	
}
