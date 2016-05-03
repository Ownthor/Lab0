/* 
 * File:   switch.c
 * Collin Reed
 * 4/11/2016
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1 
#define DISABLED 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;       // Set as input
    CNPUDbits.CNPUD6 = ENABLED;     // use pull up res
    CNENDbits.CNIED6 = ENABLED;     // use CN pin
    CNCONDbits.ON = ENABLED;        // enable interupt
    IFS1bits.CNDIF = 0;             // zero flag
    IPC8bits.CNIP = 7;              // Interrupt priority
    IEC1bits.CNDIE = ENABLED;       // enable D pins interrupt
}