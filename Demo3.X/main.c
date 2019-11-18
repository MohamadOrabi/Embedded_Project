/*
 * Interfacing 16x2 LCD with PIC18F4550
 * www.electronicwings.com
 */


#include <pic18f4550.h>
#include "Configurations_Header_File.h"
#include <stdio.h> 

#define RS LATD2                   /* PORTD 2 pin is used for Register Select */
#define EN LATD3                   /* PORTD 3 pin is used for Enable */
#define ldata_A LATA                 /* PORTB is used for transmitting data to LCD */
#define ldata_E LATE                 /* PORTB is used for transmitting data to LCD */

#define rnd RE2

#define LCD_Port_A TRISA              
#define LCD_Port_E TRISE              
#define LCD_Control TRISD

#define LED LATC6

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);

void MSdelay(unsigned int );

void process_data(char);

void ADC_Init();
float ADC_Read(int);

void External_Interrupt_Init();


/*****************************Main Program*******************************/

void main(void)
{       
    OSCCON=0x72;                   /* Use Internal Oscillator with Frequency 8MHZ */ 
    float digital;  
    char result[10];
    ADC_Init();			/*Initialize 10-bit ADC*/
    LCD_Init();                    /* Initialize 16x2 LCD */
    External_Interrupt_Init();
    TRISCbits.TRISC6 = 0;
    LED = 1;
    //digital = 100.0;

    while(1) {
        digital = ADC_Read(7);
        sprintf(result, "%.2f", digital);
        MSdelay(1000);
        LCD_String_xy(1,0,result);
    }
 
    
}

/****************************Functions********************************/
void process_data(char data) {
    ldata_A = data;
    ldata_E = (data >> 6) & 0x03;
}

void External_Interrupt_Init()
{
    TRISBbits.TRISB0=1;		/* Make INT0 pin as an input pin*/

    /* Also make PBADEN off in Configuration file or
    clear ADON in ADCON0 so as to set analog pin as digital*/
  
    INTCON2=0x00;		/* Set Interrupt on falling Edge*/
    INTCONbits.INT0IF=0;	/* Clear INT0IF flag*/
    INTCONbits.INT0IE=1;	/* Enable INT0 external interrupt*/
    INTCONbits.GIE=1;		/* Enable Global Interrupt*/
}

__interrupt() void MY_ISR(void) {   
    LED = ~(LED);		/* Toggle LED on interrupt*/
    MSdelay(200);
    INTCONbits.INT0IF=0;
}

void LCD_Init()
{
    MSdelay(15);           /* 15ms,16x2 LCD Power on delay */
    LCD_Port_A = 0x00; 
    LCD_Port_E = 0x04;      /* Set PORTB as output PORT for LCD data(D0-D7) pins */
    LCD_Control = 0x00;
    LCD_Command(0x38);     /* uses 2 line and initialize 5*7 matrix of LCD */
    LCD_Command(0x01);     /* clear display screen */
    LCD_Command(0x0c);     /* display on cursor off */
    LCD_Command(0x06);     /* increment cursor (shift cursor to right) */
}

void LCD_Clear()
{
    	LCD_Command(0x01); /* clear display screen */
}

void LCD_Command(char cmd )
{
	process_data(cmd);            /* Send data to PORT as a command for LCD */   
	RS = 0;                /* Command Register is selected */
	EN = 1;                /* High-to-Low pulse on Enable pin to latch data */ 
	NOP();
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char dat)
{
	process_data(dat);            /* Send data to LCD */  
	RS = 1;                /* Data Register is selected */
	EN=1;                  /* High-to-Low pulse on Enable pin to latch data */   
	NOP();
	EN=0;
	MSdelay(1);
}

void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    	}
		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f); /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f); /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    LCD_String(msg);

}

/*********************************ADC Functions********************************/
void ADC_Init()
{    
//    TRISA = 0xff;		/*Set as input port*/
    ADCON1 = 0x07;  		/*Ref vtg is VDD & Configure pin as analog pin*/    
    ADCON2 = 0x92;  		/*Right Justified, 4Tad and Fosc/32. */
    ADRESH=0;  			/*Flush ADC output Register*/
    ADRESL=0;   
}

float ADC_Read(int channel)
{
    float digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);

    /*channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000)& ADC is disabled*/
    ADCON0 |= 0b11;/*Enable ADC and start conversion*/

    /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);/*Combine 8-bit LSB and 2-bit MSB*/
//    digital = ADRESH;
    return(digital);
}
/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }