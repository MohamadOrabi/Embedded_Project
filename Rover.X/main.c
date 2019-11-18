#include "Configurations_Header_File.h"  /*Header file for Configuration Bits*/
#include "functions.h"
#include <stdio.h>

#include <pic18f4550.h>                  /*Header file PIC18f4550 definitions*/

typedef unsigned char bool;
#define true    1
#define false   0

#define IN1A RB0
#define ENA RB1
#define IN2A RB2
#define S1A RD0

#define IN1B RB3
#define ENB RB4
#define IN2B RB5
#define S1B RD1


int xa = 0;
int xb = 0;

void main()
{
    OSCCON=0x72;                /* Use internal oscillator of 8MHz Frequency */
    TRISB=0x00;                 /* Set direction of PORTB as OUTPUT to which LED is connected */
    TRISD=0x03;                 /* Set direction of PORTB as OUTPUT to which LED is connected */
    
    Forward(1);
    Backwards(1);
    Right(1);
    Left(1);
    
   // while(1)
   // {
//        ENB = 1;
//        IN1B = 1;
//        IN1B = 0;
//        MSdelay(5000);
//        
//        IN1A = 0;
//        IN1A = 1;
//        
//        IN1B = 0;
//        IN1B = 1;
//        MSdelay(5000);
    //}
}

void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);         /*This count Provide delay of 1 ms for 8MHz Frequency */
 } 

void Forward(unsigned char chords){
    bool done = false;
    bool S1A_old = S1A;
    bool S1B_old = S1B;
    
    int initial_xa = xa;
    int initial_xb = xb;
    
    ENA = 1;
    IN1A = 1;
    IN2A = 0;

    ENB = 1;
    IN1B = 1;
    IN2B = 0;

    while (!done) {
        
        //Edge Detection
        if (S1A != S1A_old){
            xa++;
            S1A_old = S1A;
        }
        
        if (S1B != S1B_old){
            xb++;
            S1B_old = S1B;
        }
        
        //Check Done flag
        if (xa >= initial_xa + chords * 211 || xb >= initial_xb + chords * 211){
            done = true;
        }
        

    }
    
    ENA = 1;
    IN1A = 0;
    IN2A = 0;

    ENB = 1;
    IN1B = 0;
    IN2B = 0;
}

void Backwards(unsigned char chords){
 bool done = false;
    bool S1A_old = S1A;
    bool S1B_old = S1B;
    
    int initial_xa = xa;
    int initial_xb = xb;
    
    ENA = 1;
    IN1A = 0;
    IN2A = 1;

    ENB = 1;
    IN1B = 0;
    IN2B = 1;

    while (!done) {
        
        //Edge Detection
        if (S1A != S1A_old){
            xa++;
            S1A_old = S1A;
        }
        
        if (S1B != S1B_old){
            xb++;
            S1B_old = S1B;
        }
        
        //Check Done flag
        if (xa >= initial_xa + chords * 211 || xb >= initial_xb + chords * 211){
            done = true;
        }
        

    }
    
    ENA = 1;
    IN1A = 0;
    IN2A = 0;

    ENB = 1;
    IN1B = 0;
    IN2B = 0;
}

void Right(unsigned char chords){

    bool done = false;
    bool S1A_old = S1A;
    bool S1B_old = S1B;
    
    int initial_xa = xa;
    int initial_xb = xb;
    
    ENA = 1;
    IN1A = 1;
    IN2A = 0;

    ENB = 1;
    IN1B = 0;
    IN2B = 1;

    while (!done) {
        
        //Edge Detection
        if (S1A != S1A_old){
            xa++;
            S1A_old = S1A;
        }
        
        if (S1B != S1B_old){
            xb++;
            S1B_old = S1B;
        }
        
        //Check Done flag
        if (xa >= initial_xa + chords * 211 || xb >= initial_xb + chords * 211){
            done = true;
        }
        

    }
    
    ENA = 1;
    IN1A = 0;
    IN2A = 0;

    ENB = 1;
    IN1B = 0;
    IN2B = 0;
}

void Left(unsigned char chords){

    bool done = false;
    bool S1A_old = S1A;
    bool S1B_old = S1B;
    
    int initial_xa = xa;
    int initial_xb = xb;
    
    ENA = 1;
    IN1A = 0;
    IN2A = 1;

    ENB = 1;
    IN1B = 1;
    IN2B = 0;

    while (!done) {
        
        //Edge Detection
        if (S1A != S1A_old){
            xa++;
            S1A_old = S1A;
        }
        
        if (S1B != S1B_old){
            xb++;
            S1B_old = S1B;
        }
        
        //Check Done flag
        if (xa >= initial_xa + chords * 211 || xb >= initial_xb + chords * 211){
            done = true;
        }
        

    }
    
    ENA = 1;
    IN1A = 0;
    IN2A = 0;

    ENB = 1;
    IN1B = 0;
    IN2B = 0;
}