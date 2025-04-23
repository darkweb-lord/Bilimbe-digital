// it only LCD header file

#define LCD_D 0xf<<0
#define RS 1<<4
#define RW 1<<5
#define E 1<<6

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int n);
void LCD_FLOAT(float f);
void LCD_STRING(unsigned char *);

void LCD_INIT(void)
{
	PINSEL0= 0x00000000;
	IODIR0 |= LCD_D | RS | RW | E;	//P0.0 TO P0.6 AS OUTPUI PINS
	LCD_CMD(0X01);		   			//To clear the display
	LCD_CMD(0X02);	     			//Return cursor to home postion
	LCD_CMD(0X0C);		   			//Display on cursor off
	LCD_CMD(0X28);		   			//4 bit interface mode with both lines 
	LCD_CMD(0X80);		   			//select starting address of DDRAM
}

void LCD_CMD(unsigned char cmp)
{
	
	IOCLR0 = LCD_D;
	IOSET0 = (cmp&0xF0)>>4;
	IOCLR0 = RS;
	IOCLR0 = RW;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
	
	IOCLR0 = LCD_D;
	IOSET0 = (cmp&0x0F);
	IOCLR0 = RS;
	IOCLR0 = RW;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

}

void LCD_DATA(unsigned char data)
{
	
	IOCLR0 = LCD_D;
	IOSET0 = (data&0xF0)>>4;
	IOSET0 = RS;
	IOCLR0 = RW;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
	
	IOCLR0 = LCD_D;
	IOSET0 = (data&0x0F);
	IOSET0 = RS;
	IOCLR0 = RW;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

}

void LCD_INTEGER(int n)
{
	unsigned char arr[10];
	signed char i = 0;
	if(n == 0)
		LCD_DATA(0);
	else
	{
		if ( n < 0)
		{
			LCD_DATA('-');
			n = -n;
		}
		while( n > 0)
		{
			arr[i++] = n%10;
			n/=10;
		}
		for ( i = i-1 ; i >= 0; i--)
			LCD_DATA(arr[i]+48);
	}
}
void LCD_FLOAT(float f)
{
	int temp;
	temp = f;
	LCD_INTEGER(temp);
	LCD_DATA('.');

	temp = (f - temp)*100;
	LCD_INTEGER(temp);
}
void LCD_STRING(unsigned char *s)
{
	while(*s)
	{
	 	LCD_DATA(*s++);
	}
}
