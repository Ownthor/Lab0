/* 
 * File:   main.c
 * Author: Collin Reed
 * Description: lab 0. Part 2
 * Edited on 4/11/2016
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define UP 1
#define DOWN 0

//Define states of the state machine
typedef enum stateTypeEnum{
    LED1, LED2, LED3, debounceDown, DebounceUp, Wait, Forward, Backwards
} stateType;

volatile stateType state = LED1;
volatile stateType CurrentLED = LED1;
volatile stateType Direction = Forward;

int main() {
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){
        switch (state)  {
            case LED1:
                turnOnLED(1);
                break;
            case LED2:
                turnOnLED(2);
                break;
            case LED3:
                turnOnLED(3);
                break;
            case debounceDown:
                delayMs(10);
                state = Wait;
                break;
            case DebounceUp:
                IFS0bits.T1IF = 0;
                T1CONbits.ON = 0;
                delayMs(10);
                if(Direction == Forward){
                    switch (CurrentLED)  {
                        case LED1:
                            state = LED2;
                            break;
                        case LED2:
                            state = LED3;
                            break;
                        case LED3:
                            state = LED1;
                            break;
                        default:
                            break;
                    }
                }else if(Direction == Backwards){
                    switch (CurrentLED)  {
                        case LED1:
                            state = LED3;
                            break;
                        case LED2:
                            state = LED1;
                            break;
                        case LED3:
                            state = LED2;
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
        
    }
    
    return 0;
}

// Button change interrupt
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
	IFS1bits.CNDIF = 0;
	unsigned Button = PORTDbits.RD6;
	if (Button == DOWN && (state == LED1||state == LED2||state == LED3)) {
		TMR1 = 0;
        T1CONbits.ON = 1;
        Direction = Forward;
        //FORWARD
        CurrentLED = state;
        state = debounceDown;
	}

	else if (Button == UP && state == Wait) {
        state = DebounceUp;
	}
}

// 1 second or more timer for holding down btn
void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0;
    T1CONbits.ON = 0;
    //BACKWARDS
    Direction = Backwards;
}

