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
<<<<<<< HEAD
void LCD_Command(char);
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char, char, const char*);
void LCD_Clear();

void MSdelay(unsigned int);
=======
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);

void MSdelay(unsigned int );
>>>>>>> 6e777632c9f94abb11d48e192a73f4a1c30ce2b0

void process_data(char);

void ADC_Init();
float ADC_Read(int);

void External_Interrupt_Init();
<<<<<<< HEAD
void Timer1_start();

int count = 0;
int pressCount = 0;
int time[3];

/*****************************Main Program*******************************/

void main(void) {
    OSCCON = 0x72; /* Use Internal Oscillator with Frequency 8MHZ */

    char result[10];
    ADC_Init(); /*Initialize 10-bit ADC*/
    External_Interrupt_Init();
    TRISCbits.TRISC6 = 0;
    LED = 0;
    //digital = 100.0;

    float seed = ADC_Read(7);
    srand(seed); // Initialization, should only be called once.
    float r = rand() * (3000 / 255) + 1000; // Returns a pseudo-random integer between 0 and RAND_MAX.
    
    LCD_Init(); /* Initialize 16x2 LCD */
    sprintf(result, "%.2f", r);
    LCD_String_xy(1, 0, result);
    MSdelay((int) r);
    LED = 1;
    Timer1_start();
    while (1);



=======


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
 
    
>>>>>>> 6e777632c9f94abb11d48e192a73f4a1c30ce2b0
}

/****************************Functions********************************/
void process_data(char data) {
    ldata_A = data;
    ldata_E = (data >> 6) & 0x03;
}

<<<<<<< HEAD
/***************Interrupt Service Routine for Button******************/

void External_Interrupt_Init() {
    TRISBbits.TRISB0 = 1; /* Make INT0 pin as an input pin*/

    /* Also make PBADEN off in Configuration file or
    clear ADON in ADCON0 so as to set analog pin as digital*/

    INTCON2 = 0x00; /* Set Interrupt on falling Edge*/
    INTCONbits.INT0IF = 0; /* Clear INT0IF flag*/
    INTCONbits.INT0IE = 1; /* Enable INT0 external interrupt*/
    INTCONbits.GIE = 1; /* Enable Global Interrupt*/
}

__interrupt() void MY_ISR(void) {
    if (INTCONbits.INT0IF) {
        if (pressCount < 3) {
            time[pressCount] = count;
            pressCount++;

            if (pressCount == 3) {
                int totalTime = 0;
                T1CON = 0x00;
                char result[10];
                LCD_Clear();
                for (int i = 0; i < 3; i++) {
                    sprintf(result, "%d", time[i]);
                    LCD_String_xy(1, 4 * i, result);
                    totalTime += time[i];
                }
                sprintf(result, "%d", totalTime);
                LCD_String_xy(2, 0, result);
            }

            count = 0;
                    PIR1bits.TMR1IF = 0; /* Make Timer1 Overflow Flag to '0' */
                    INTCONbits.INT0IF = 0;
        }
    }

    if (PIR1bits.TMR1IF) {
        TMR1 = 0xF856;
        if (count < 1000) {
            count++;
                    PIR1bits.TMR1IF = 0; /* Make Timer1 Overflow Flag to '0' */
        } else {

            LCD_String_xy(1, 0, "TOO SLOW!!");
        }
    }
}

/***************Interrupt Service Routine for Timer1******************/

void Timer1_start() {

    GIE = 1; /* Enable Global Interrupt */
            PEIE = 1; /* Enable Peripheral Interrupt */
            TMR1IE = 1; /* Enable Timer1 Overflow Interrupt */
            TMR1IF = 0;

            /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
            T1CON = 0x80;

            TMR1 = 0xF856; /* Load Count for generating delay of 1ms */
            TMR1ON = 1; /* Turn ON Timer1 */
}

/***************LCD Functions******************/
void LCD_Init() {

    MSdelay(15); /* 15ms,16x2 LCD Power on delay */
            LCD_Port_A = 0x00;
            LCD_Port_E = 0x04; /* Set PORTB as output PORT for LCD data(D0-D7) pins */
            LCD_Control = 0x00;
            LCD_Command(0x38); /* uses 2 line and initialize 5*7 matrix of LCD */
            LCD_Command(0x01); /* clear display screen */
            LCD_Command(0x0c); /* display on cursor off */
            LCD_Command(0x06); /* increment cursor (shift cursor to right) */
}

void LCD_Clear() {

    LCD_Command(0x01); /* clear display screen */
}

void LCD_Command(char cmd) {

    process_data(cmd); /* Send data to PORT as a command for LCD */
            RS = 0; /* Command Register is selected */
            EN = 1; /* High-to-Low pulse on Enable pin to latch data */
            NOP();
            EN = 0;
            MSdelay(3);
}

void LCD_Char(char dat) {

    process_data(dat); /* Send data to LCD */
            RS = 1; /* Data Register is selected */
            EN = 1; /* High-to-Low pulse on Enable pin to latch data */
            NOP();
            EN = 0;
            MSdelay(1);
}

void LCD_String(const char *msg) {
    while ((*msg) != 0) {

        LCD_Char(*msg);
                msg++;
    }

}

void LCD_String_xy(char row, char pos, const char *msg) {
    char location = 0;
    if (row <= 1) {
        location = (0x80) | ((pos) & 0x0f); /*Print message on 1st row and desired location*/
                LCD_Command(location);
    } else {

        location = (0xC0) | ((pos) & 0x0f); /*Print message on 2nd row and desired location*/
                LCD_Command(location);
    }
=======
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
>>>>>>> 6e777632c9f94abb11d48e192a73f4a1c30ce2b0
    LCD_String(msg);

}

/*********************************ADC Functions********************************/
<<<<<<< HEAD
void ADC_Init() {
    //    TRISA = 0xff;		/*Set as input port*/

    ADCON1 = 0x07; /*Ref vtg is VDD & Configure pin as analog pin*/
            ADCON2 = 0x92; /*Right Justified, 4Tad and Fosc/32. */
            ADRESH = 0; /*Flush ADC output Register*/
            ADRESL = 0;
}

float ADC_Read(int channel) {
    float digital;
            ADCON0 = (ADCON0 & 0b11000011) | ((channel << 2) & 0b00111100);

            /*channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000)& ADC is disabled*/
            ADCON0 |= 0b11; /*Enable ADC and start conversion*/

            /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
    while (ADCON0bits.GO_nDONE == 1);

            digital = (ADRESH * 256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
            //    digital = ADRESH;

        return (digital);
    }

/*********************************Delay Function********************************/
void MSdelay(unsigned int val) {
    unsigned int i, j;
    for (i = 0; i < val; i++)
        for (j = 0; j < 165; j++); /*This count Provide delay of 1 ms for 8MHz Frequency */
        }
=======
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
>>>>>>> 6e777632c9f94abb11d48e192a73f4a1c30ce2b0
