/*
ʹ��STC15ϵ�е�Ƭ�����ƿ���SI4136���2037MHzƵ�ʣ�SI4133���1537MHz��500MHz
��ϵ���Ź�
QQ��1024289556
*/
#include <reg51.h>
#include <intrins.h>

/*���嵥Ƭ������ӿ�*/
sbit SCLK = P3^2;//3�ߴ���ͨ�Žӿ�ʱ��
sbit SDATA = P3^1;//3�ߴ���ͨ�Žӿ����ݴ���
sbit SENB1 = P3^4;//3�ߴ���ͨ�Žӿ�Ƭѡ�źţ�SI4136
sbit SENB2 = P3^5;//3�ߴ���ͨ�Žӿ�Ƭѡ�źţ�SI4133
//sbit AUXOUT1 = P3^3;//����ӿڣ���Ư����ʱ���ó���
//sbit AUXOUT2 = P3^0;//����ӿڣ���Ư����ʱ���ó���

void delay(void)
{
	_nop_();
	//_nop_();
	//_nop_();
	//_nop_();
}

void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time; i>0; i--)
		for(j=144; j>0; j--);
}

void Si4136_write(unsigned long dat)
{
	unsigned long mask;
	SCLK = 1;
	SENB1 = 1;
	delay();
	SENB1 = 0;
	SCLK = 0;
	delay();
	delay();

	for(mask=0x200000; mask!=0; mask>>=1)
	{
		if((mask & dat) == 0)
			SDATA = 0;
		else
			SDATA = 1;
		delay();
		SCLK = 1;
		//delay();
		SCLK = 0;
		delay();
	}
	SENB1 = 1;
	delay();//ten3
	SCLK = 1;
	delay();//tw
	SENB1 = 1;
	delay(); 
}

void Si4133_write(unsigned long dat)
{
	unsigned long mask;
	SCLK = 1;
	SENB2 = 1;
	delay();
	SENB2 = 0;
	SCLK = 0;
	delay();
	delay();

	for(mask=0x200000; mask!=0; mask>>=1)
	{
		if((mask & dat) == 0)
			SDATA = 0;
		else
			SDATA = 1;
		delay();
		SCLK = 1;
		//delay();
		SCLK = 0;
		delay();
	}
	SENB2 = 1;
	delay();//ten3
	SCLK = 1;
	delay();//tw
	SENB2 = 1;
	delay(); 
}

void Si4136_Init(void)//SI4136�Ĵ������ã�ֻ��ҪRF2���2037Mhz������
{
	Si4136_write((0x0000)<<4 | 0);
	//delay1();	

	Si4136_write((0x0000)<<4 | 1);
	//delay1();

	Si4136_write((0x0001)<<4 | 2);
	//delay1();
	
	Si4136_write((0x7f5)<<4 | 4);
	//delay1();

	Si4136_write((0x1a)<<4 | 7);
	//delay1();	
}



void Si4133_Init(void)//SI4133�Ĵ������ã�RF1537Mhz��IF���500Mhz������
{	
	Si4133_write((0xc)<<4 | 0);
	//delay1();	

	Si4133_write((0x601)<<4 | 3);
	//delay1();	

	Si4133_write((0x01f4)<<4 | 5);
	//delay1();	

	Si4133_write((0xd)<<4 | 6);
	//delay1();	

	Si4133_write((0xd)<<4 | 8);
	//delay1();
}

int main(void) 
{
	delay_ms(10);
	Si4133_Init();
	delay_ms(50);
	Si4136_Init();
	while(1)
	{
	//	if(AUXOUT1)
			//Si4136_Init(2037);
	//	if(AUXOUT2)
			//Si4133_Init();
	}
	
}