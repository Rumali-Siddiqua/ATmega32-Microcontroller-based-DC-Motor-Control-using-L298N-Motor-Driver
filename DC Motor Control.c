#include <mega32.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <alcd.h>

int rotate=0;
char speed[16];                                                                                        
int OCR_initial=128;
int OCR_minimum=16;
int OCR_maximum=240;
int OCR_step=32;

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
OCR2=OCR2-OCR_step;
if(OCR2<OCR_minimum) OCR2=OCR_minimum;

delay_ms(50);

lcd_clear();
lcd_gotoxy(0,0);
lcd_puts("Speed:");
lcd_puts("Decrease");

delay_ms(200);
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
OCR2=OCR2+OCR_step;
if(OCR2>OCR_maximum) OCR2=OCR_maximum;

delay_ms(50);

lcd_clear();
lcd_gotoxy(0,0);
lcd_puts("Speed:");
lcd_puts("Increase");

delay_ms(200);
}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
if(rotate==0)
{
PORTC.0=1;
PORTC.1=0;
PORTC.2=1;
PORTC.3=0;
}
if(rotate==1)
{
PORTC.0=0;
PORTC.1=1;
PORTC.2=0;
PORTC.3=1;
}
if(rotate==2)
{
PORTC.0=0;
PORTC.1=0;
PORTC.2=0;
PORTC.3=0;

}

if(rotate==3) rotate=0;

lcd_clear();
lcd_gotoxy(0,1);
lcd_puts("Dir:");
if(rotate==0)
lcd_puts("AntiClockwise");
if(rotate==1)
lcd_puts("Clockwise");
if(rotate==2)
lcd_puts("Off");

delay_ms(200);
rotate++;
}


void main(void)
{

DDRC=0xFF;
PORTC.0=1;
PORTC.1=0;
PORTC.2=1;
PORTC.3=0;

DDRD.7=1;


TCCR2=(1<<WGM20)|(1<<COM21)|(0<<COM20)|(1<<WGM21)|(1<<CS22)|(1<<CS21)|(1<<CS20);
TCNT2=0x00;
OCR2= OCR_initial;


GICR|=(1<<INT1) | (1<<INT0) | (1<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);




// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
lcd_init(16);

// Global enable interrupts
#asm("sei")
 lcd_clear();
lcd_gotoxy(0,0);
lcd_puts("Waiting for the command");

while (1)
      {  


      }
}
