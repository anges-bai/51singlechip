#include<reg52.h>			
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit rw=P2^5;
sbit rs=P2^6;
sbit e=P2^7;
sbit led=P3^7;

sbit beep=P2^0;
uint8 key,num;
uint8 fuhao;//¶¨Òå¾ßÌåµÄÄÇ¸ö·ûºÅ£¬ÊÇ¼Ó¼õ»¹ÊÇ³Ë³ý¡£
uint8 flag;	//¶¨ÒåÓÐÃ»ÓÐ°´ÏÂ·ûºÅ¼ü£¬Õâ¸öÊÇÍ³³Æ
long a,b,c,d;	//¶¨ÒåÔËËãÊý¾ÝµÄµÚÒ»¸öºÍµÚ¶þ¸ö¼°µÈÓÚµÄÊý±äÁ¿
uint8 k; //¶¨ÒåÐ¡ÊýµãºóÃæÏÔÊ¾µÄÎ»Êý
uint8 biao;

uint8 dat1[]={1,2,3,0x2b-0x30, 4,5,6,0x2d-0x30, 7,8,9,0x2a-0x30, 0,0x01-0x30,0x3d-0x30,0x2b-0x30 };//±£´æÏÔÊ¾µÄÊý¾Ý

void delay(uint16 i)
{
	while(i--);
}
void lcdwrc(uint8 c)
{
	delay(1000);
	rs=0;
	rw=0;
	e=0;
	P0=c;
	e=1;
	delay(1000);
	e=0;
}
void lcdwrd(uint8 dat)
{
	delay(1000);
	rs=1;
	rw=0;
	e=0;
	P0=dat;
	e=1;
	delay(1000);
	e=0;
	rs=0;
}

void lcdinit()
{
	delay(1500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	lcdwrc(0x08);
	lcdwrc(0x01);
	lcdwrc(0x06);
	lcdwrc(0x0c);
	key=0;
	num=0;
	flag=0;
	fuhao=0;
	a=0;
	b=0;
	c=0;
	d=0;
	biao=0;
	led=0;

}

void keyscan()
{
	P1=0xfe;   //ÁîµÚÒ»ÐÐÎª0£¬È»ºóÅÐ¶ÏÊÇÄÄÒ»ÁÐ°´ÏÂ
	if(P1!=0xfe)
	{
		delay(1000);
		if(P1!=0xfe)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=0;break;	  //1
				case 0xd0: num=1;break;	  //2
				case 0xb0: num=2;break;	  //3
				case 0x70: num=3;break;	  //¼Ó
			}
		}
		while(P1!=0xfe);
		if(num==0||num==1||num==2)	 //È·ÈÏµÚÒ»ÐÐµÄÊý1,2,3
		{
			if(flag==0)	 //Ã»ÓÐ°´ÏÂ·ûºÅ¼ü
			{
				//led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				//led=1;
				b=b*10+dat1[num];
			}
		
		}
		if(num==3)
		{
			//led=0;
			flag=1;
			fuhao=1;//¼ÓºÅ+	
		}
		lcdwrd(0x30+dat1[num]);
	}


	P1=0xfd;				//ÁîµÚ¶þÐÐÎª0£¬ÅÐ¶ÏÊÇÄÄÒ»ÁÐ°´ÏÂ
	if(P1!=0xfd)
	{
		delay(1000);
		if(P1!=0xfd)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=4;break;	  //4
				case 0xd0: num=5;break;	  //5
				case 0xb0: num=6;break;	  //6
				case 0x70: num=7;break;	  //¼õ¡ª
			}	
		}
		while(P1!=0xfd);
		if(num==4||num==5||num==6)
		{
			if(flag==0)	 //Ã»ÓÐ°´ÏÂ·ûºÅ¼ü
			{
				//led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				//led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			flag=1;
			fuhao=2;//´ø±í¼õºÅ
		}
		lcdwrd(0x30+dat1[num]);
	}


	P1=0xfb;		 //ÁîµÚÈýÐÐÎª0£¬ÅÐ¶ÏÄÄÒ»ÁÐ°´ÏÂ
	if(P1!=0xfb)
	{
		delay(1000);
		if(P1!=0xfb)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=8;break;	  //7
				case 0xd0: num=9;break;	  //8
				case 0xb0: num=10;break;  //9
				case 0x70: num=11;break;  //³Ë*
			}	
		}
		while(P1!=0xfb);
		if(num==8||num==9||num==10)
		{
			if(flag==0)	 //Ã»ÓÐ°´ÏÂ·ûºÅ¼ü
			{
				//led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				//led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			flag=1;
			fuhao=3;//´ø±í³ËºÅ*
		}
		lcdwrd(0x30+dat1[num]);
	}


	P1=0xf7;		 //ÁîµÚËÄÐÐÎª0£¬ÅÐ¶ÏÄÄÒ»ÁÐ°´ÏÂ
	if(P1!=0xf7)
	{
		delay(1000);
		if(P1!=0xf7)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=12;break;  //0
				case 0xd0: num=13;break;  //Çå³ýrst
				case 0xb0: num=14;break;  //µÈºÅ=
				case 0x70: num=15;break;  //³ý/
			}	
		}
		while(P1!=0xf7);
		switch(num)
		{
			case 12: 
					if(flag==0)	 //Ã»ÓÐ°´ÏÂ·ûºÅ¼ü
					{
						//led=1;
						a=a*10+dat1[num];
						lcdwrd(0x30);	
					}
					else
					{
						//led=1;
						b=b*10+dat1[num];
						lcdwrd(0x30);
					}
					break;
			
			case 13: 
					lcdwrc(0x01);	//ÇåÆÁÖ¸Áî			
					a=0;
					b=0;
					flag=0;
					fuhao=0;
					break;

			case 15:
			
					flag=1;
					fuhao=4;
					lcdwrd(0x2f);//³ýºÅ/
					break;
					
			case 14: 
					if(fuhao==1)//¼Ó
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//ÉèÖÃ¹â±ê×óÒÆ£¬ÆÁÄ»²»ÒÆ¶¯
						c=a+b;
						while(c!=0)	 //Ò»Î»Ò»Î»ÏÔÊ¾
						{
							lcdwrd(0x30+c%10);//ÏÔÊ¾½á¹ûµÄ×îºóÒ»Î»ÔÚ0x4fµÄÎ»ÖÃ
							c=c/10;//È¡Ç°ÃæµÄ½á¹ûÊý¾Ý	
						}
						lcdwrd(0x3d); //ÏÔÊ¾µÈÓÚºÅ=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//È«²¿Çå³ýÎª0
					}
					if(fuhao==2)   //¼õ
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//ÉèÖÃ¹â±ê×óÒÆ£¬ÆÁÄ»²»ÒÆ¶¯
						if(a>b)
							c=a-b;
						else
							c=b-a;
						
						while(c!=0)	 //Ò»Î»Ò»Î»ÏÔÊ¾
						{
							lcdwrd(0x30+c%10);//ÏÔÊ¾½á¹ûµÄ×îºóÒ»Î»ÔÚ0x4fµÄÎ»ÖÃ
							c=c/10;//È¡Ç°ÃæµÄ½á¹ûÊý¾Ý	
						}
						if(a<b)	lcdwrd(0x2d); //ÏÔÊ¾-ºÅ
						lcdwrd(0x3d); //ÏÔÊ¾µÈÓÚºÅ=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//È«²¿Çå³ýÎª0
					}
					if(fuhao==3)//³Ë·¨		
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//ÉèÖÃ¹â±ê×óÒÆ£¬ÆÁÄ»²»ÒÆ¶¯
						c=a*b;
						while(c!=0)	 //Ò»Î»Ò»Î»ÏÔÊ¾
						{
							lcdwrd(0x30+c%10);//ÏÔÊ¾½á¹ûµÄ×îºóÒ»Î»ÔÚ0x4fµÄÎ»ÖÃ
							c=c/10;//È¡Ç°ÃæµÄ½á¹ûÊý¾Ý	
						}
						lcdwrd(0x3d); //ÏÔÊ¾µÈÓÚºÅ=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//È«²¿Çå³ýÎª0	
					}
					if(fuhao==3)//³Ë·¨		
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//ÉèÖÃ¹â±ê×óÒÆ£¬ÆÁÄ»²»ÒÆ¶¯
						c=a*b;
						while(c!=0)	 //Ò»Î»Ò»Î»ÏÔÊ¾
						{
							lcdwrd(0x30+c%10);//ÏÔÊ¾½á¹ûµÄ×îºóÒ»Î»ÔÚ0x4fµÄÎ»ÖÃ
							c=c/10;//È¡Ç°ÃæµÄ½á¹ûÊý¾Ý	
						}
						lcdwrd(0x3d); //ÏÔÊ¾µÈÓÚºÅ=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//È«²¿Çå³ýÎª0	
					}
					if(fuhao==4)
					{
						k=0;
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//ÉèÖÃ¹â±ê×óÒÆ£¬ÆÁÄ»²»ÒÆ¶¯
						c=(long)(((float)a/b)*1000);//Ç¿ÖÆ×ª»»Îªlong¡£
						while(c!=0)	 //Ò»Î»Ò»Î»ÏÔÊ¾
						{
							k++;
							lcdwrd(0x30+c%10);//ÏÔÊ¾½á¹ûµÄ×îºóÒ»Î»ÔÚ0x4fµÄÎ»ÖÃ
							c=c/10;//È¡Ç°ÃæµÄ½á¹ûÊý¾Ý
							if(k==3)
							{
								lcdwrd(0x2e);
								k=0;
							}		
						}
						if(a/b<0)	  //Èç¹ûa±ÈbÐ¡µÄ»°ÄÇÃ´³ýµÄ½á¹û×î¸ßÎ»ÊÇ0
						{
							lcdwrd(0x30);	
						}
						lcdwrd(0x3d); //ÏÔÊ¾µÈºÅ
						a=0;
						b=0;
						flag=0;
						fuhao=0;//È«²¿Çå³ýÎª0
					}
					break;

		}
	}

}



void main()
{
	lcdinit();
	while(1)
	{
		keyscan();	
	}
}
