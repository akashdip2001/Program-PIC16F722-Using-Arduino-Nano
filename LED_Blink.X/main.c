#include <xc.h>

// Configuration Bits (Adjust for Your Setup)
#pragma config FOSC = INTOSCIO  // Internal Oscillator with I/O function
#pragma config WDTE = OFF       // Watchdog Timer Disable
#pragma config PWRTE = OFF      // Power-up Timer Disable
#pragma config MCLRE = ON       // MCLR Enable
#pragma config CP = OFF         // Code Protection Off
#pragma config BOREN = OFF      // Brown-out Reset Disable

#define _XTAL_FREQ 4000000  // 4MHz Internal Oscillator

void main() {
    TRISB0 = 0;  // Set RB0 as output (LED pin)

    while(1) {
        RB0 = 1;  // Turn LED ON
        __delay_ms(500);
        RB0 = 0;  // Turn LED OFF
        __delay_ms(500);
    }
}
