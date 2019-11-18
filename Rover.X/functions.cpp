/*
 * File:   functions.cpp
 * Author: mohamadorabi
 *
 * Created on November 9, 2019, 7:21 PM
 */


#include <xc.h>
#include "functions.h"

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
