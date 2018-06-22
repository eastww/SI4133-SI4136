/*
使用STC15系列单片机控制控制SI4136输出2037MHz频率，SI4133输出1537MHz和500MHz
联系：张工
QQ：1024289556
*/
#include <reg51.h>
#include <intrins.h>

/*定义单片机输出接口*/
sbit SCLK = P3^2;//3线串行通信接口时钟
sbit SDATA = P3^1;//3线串行通信接口数据传输
sbit SENB1 = P3^4;//3线串行通信接口片选信号，SI4136
sbit SENB2 = P3^5;//3线串行通信接口片选信号，SI4133
//sbit AUXOUT1 = P3^3;//输入接口，温漂严重时重置程序
//sbit AUXOUT2 = P3^0;//输入接口，温漂严重时重置程序

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

void Si4136_Init(void)//SI4136寄存器配置，只需要RF2输出2037Mhz的数据
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



void Si4133_Init(void)//SI4133寄存器配置，RF1537Mhz，IF输出500Mhz的数据
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