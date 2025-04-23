#include <stdint.h>
#include <LPC21xx.h>
#include "delay_headers.h"
#include "LCD_4Bit_header.h"

// GPIO Assignments
#define SENSOR   7           // P0.7 - Tap sensor input
#define RED      (1 << 8)    // P0.8
#define GREEN    (1 << 9)    // P0.9
#define YELLOW   (1 << 10)   // P0.10
#define BLUE     (1 << 11)   // P0.11
#define PURPLE   (1 << 12)   // P0.12

#define TIME_WINDOW 1000     // 1 second in ms

// Function Prototypes
void init_system(void);
void monitor_tap_window(void);
void display_status(uint16_t time_ms, uint8_t taps);
void update_led(uint8_t count);

// Global veriable
uint8_t tap_count = 0;

int main()
{
    init_system();
    while (1)
    {
        monitor_tap_window();  // Detect taps within the window
		update_led(tap_count);
        delay_ms(500);
    }
}

void init_system(void)
{
    LCD_INIT();
    IODIR0 |= RED | GREEN | YELLOW | BLUE | PURPLE;
    IODIR0 &= ~(1 << SENSOR);  // Sensor as input
    LCD_CMD(0x80);
    LCD_STRING("BILIMBE DIGITAL");
    delay_ms(1000);
}

void monitor_tap_window(void)
{
    if (((IOPIN0 >> SENSOR) & 1) == 1)  // Initial tap
    {
        uint16_t t;
        tap_count = 1;
        while (((IOPIN0 >> SENSOR) & 1) == 1);  // Wait for release
        
        for (t = 0; t < TIME_WINDOW; t += 100)
        {
            display_status(t, tap_count);
            delay_ms(100);

            if (((IOPIN0 >> SENSOR) & 1) == 1)
            {
                tap_count++;
                if (tap_count > 5) tap_count = 1;
                while (((IOPIN0 >> SENSOR) & 1) == 1);
                delay_ms(50);
            }
            delay_ms(50);
        }
    }
}

void update_led(uint8_t count)
{
	IOCLR0 = RED | GREEN | YELLOW | BLUE | PURPLE;
	LCD_CMD(0x01);  // clear the LCD display
	LCD_CMD(0x80);  // Line 1
	LCD_STRING("LED COLOR");

	LCD_CMD(0xC0);  // Line 2
	switch (count)
	{
			case 1: IOSET0 = RED;    LCD_STRING("RED");        ; break;
			case 2: IOSET0 = GREEN;  LCD_STRING("GREEN");      ; break;
			case 3: IOSET0 = YELLOW; LCD_STRING("YELLOW");     ; break;
			case 4: IOSET0 = BLUE;   LCD_STRING("BLUE");       ; break;
			case 5: IOSET0 = PURPLE; LCD_STRING("PURPLE");     ; break;
			default: IOSET0 = RED;   LCD_STRING("DEFAULT-RED");
	}

}

void display_status(uint16_t time_ms, uint8_t taps)
{
    LCD_CMD(0x01);
    LCD_CMD(0x80);
    LCD_STRING("Time(ms):");
    LCD_CMD(0x8B);
    LCD_INTEGER(time_ms);

    LCD_CMD(0xC0);
    LCD_STRING("Taps:");
    LCD_CMD(0xC6);
    LCD_INTEGER(taps);
}
