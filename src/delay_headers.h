void delay_sec(unsigned int s)
{
	T0PR  = 15000000 - 1;
	T0TCR = 0X01;
	while(T0TC < s);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void delay_ms(unsigned int s) //ms -> milliseconds
{
	  T0PR  = 15000 - 1;
	  T0TCR = 0X01;
   	while(T0TC < s);
  	T0TCR = 0X03;
   	T0TCR = 0X00;
}
void delay_us(unsigned int s) //us -> microseconds
{
    T0PR  = 15 - 1;
    T0TCR = 0X01;
    while(T0TC < s);
    T0TCR = 0X03;
    T0TCR = 0X00;
}
