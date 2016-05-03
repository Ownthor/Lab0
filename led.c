/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define INPUT 1

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

#define ON 1
#define OFF 0

void initLEDs(){
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    if(led == 1){
        LED1 = ON;
        LED2 = OFF;
        LED3 = OFF;
    }
    else if(led == 2){
        LED1 = OFF;
        LED2 = ON;
        LED3 = OFF;
    }
    else if(led == 3){
        LED1 = OFF;
        LED2 = OFF;
        LED3 = ON;
    }
    else {
        LED1 = OFF;
        LED2 = OFF;
        LED3 = OFF;
    }
}