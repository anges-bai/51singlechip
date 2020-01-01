#include"reg51.h"

#include <intrins.h>
sbit RX=P3^1;
sbit TX=P3^0;
unsigned int  time=0;
unsigned int  timer=0;
unsigned char posit=0;
//unsigned long S=0;
bit      flag =0;
//--¶¨ÒåÊ¹ÓÃµÄIO--//
#define GPIO_DIG P0
int S;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--¶¨ÒåÈ«¾Ö±äÁ¿--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0¡¢1¡¢2¡¢3¡¢4¡¢5¡¢6¡¢7¡¢8¡¢9¡¢A¡¢b¡¢C¡¢d¡¢E¡¢FµÄÏÔÊ¾Âë
unsigned char disbuff[4]	   ={ 0,0,0,0,};
/*******************************************************************************
* º¯ Êý Ãû         : DigDisplay
* º¯Êý¹¦ÄÜ		   : Ê¹ÓÃÊýÂë¹ÜÏÔÊ¾
* Êä    Èë         : ÎÞ
* Êä    ³ö         : ÎÞ
*******************************************************************************/
void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //Î»Ñ¡£¬Ñ¡ÔñµãÁÁµÄÊýÂë¹Ü£¬
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//ÏÔÊ¾µÚ0Î»
			case(1):
				LSA=1;LSB=0;LSC=0; break;//ÏÔÊ¾µÚ1Î»
			case(2):
				LSA=0;LSB=1;LSC=0; break;//ÏÔÊ¾µÚ2Î»
			case(3):
				LSA=1;LSB=1;LSC=0; break;//ÏÔÊ¾µÚ3Î»
			case(4):
				LSA=0;LSB=0;LSC=1; break;//ÏÔÊ¾µÚ4Î»
			case(5):
				LSA=1;LSB=0;LSC=1; break;//ÏÔÊ¾µÚ5Î»
			case(6):
				LSA=0;LSB=1;LSC=1; break;//ÏÔÊ¾µÚ6Î»
			case(7):
				LSA=1;LSB=1;LSC=1; break;//ÏÔÊ¾µÚ7Î»	
		}
		GPIO_DIG=disbuff[i];//·¢ËÍ¶ÎÂë
		j=10;						 //É¨Ãè¼ä¸ôÊ±¼äÉè¶¨
		while(j--);	
		GPIO_DIG=0x00;//ÏûÒþ
	}
}
/********************************************************/
    void Conut(void)
	{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	  S= (long)(time*0.17);     //Ëã³öÀ´ÊÇCM
	 if((S>=4000)||flag==1) //³¬³ö²âÁ¿·¶Î§ÏÔÊ¾¡°ERR0¡±
	 {	 
	  flag=0;
	  disbuff[0]=0x3f;	   //¡°-¡±
	  disbuff[1]=0x50;	   //¡°-¡±
	  disbuff[2]=0x50;	   //¡°-¡±
	  disbuff[3]=0x79;	   //¡°-¡±
	 }
	 else
	 {
	  disbuff[3]=DIG_CODE[S%10000/1000];
	  disbuff[2]=DIG_CODE[S%1000/100];
	  disbuff[1]=DIG_CODE[S%100/10];
	  disbuff[0]=DIG_CODE[S%10/1];
	 }
	}
/********************************************************/
     void zd0() interrupt 1 		 //T0ÖÐ¶ÏÓÃÀ´¼ÆÊýÆ÷Òç³ö,³¬¹ý²â¾à·¶Î§
  {
    flag=1;							 //ÖÐ¶ÏÒç³ö±êÖ¾
  }
/********************************************************/
   void  zd3()  interrupt 3 		 //T1ÖÐ¶ÏÓÃÀ´É¨ÃèÊýÂë¹ÜºÍ¼Æ800MSÆô¶¯Ä£¿é
  {
	 TH1=0xf8;
	 TL1=0x30;
	 DigDisplay();
	 timer++;
	 if(timer>=100)
	 {
	  timer=0;
	  TX=1;			                //800MS  Æô¶¯Ò»´ÎÄ£¿é
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
	 } 
  }
/*********************************************************/

	void  main(  void  )

  {  
    TMOD=0x11;		   //ÉèT0Îª·½Ê½1£¬GATE=1£»
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS¶¨Ê±
	TL1=0x30;
	ET0=1;             //ÔÊÐíT0ÖÐ¶Ï
	ET1=1;			   //ÔÊÐíT1ÖÐ¶Ï
	TR1=1;			   //¿ªÆô¶¨Ê±Æ÷
	EA=1;			   //¿ªÆô×ÜÖÐ¶Ï

	while(1)
	{
	 while(!RX);		//µ±RXÎªÁãÊ±µÈ´ý
	 TR0=1;			    //¿ªÆô¼ÆÊý
	 while(RX);			//µ±RXÎª1¼ÆÊý²¢µÈ´ý
	 TR0=0;				//¹Ø±Õ¼ÆÊý
     Conut();			//¼ÆËã
	}

  }
