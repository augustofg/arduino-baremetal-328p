#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <stdint.h>

/*
 * Timer0 interrupt
 */
ISR(TIMER0_COMPA_vect) {
    static uint8_t cnt = 0;

    /*
     * Toggle pin PD4 every 250ms (Arduino D4 pin)
     */
    if (cnt < 250) {
        cnt++;
    } else {
        cnt = 0;
        PORTD ^= (1 << 4);
    }
}

int main(void) {
    /*
     * Configure pin PD4 as an output
     */
    DDRD |= (1 << 4);

    /*
	 * Enable the Timer0 interrupt, 1ms period (assuming a 16MHz clock)
     */
    TCNT0 = 0;
    OCR0A = 250;
    TIMSK0 = (1 << OCIE0A);
    TCCR0A = 0;
    TCCR0B = (1 << CS01) | (1 << CS00);
    sei();

    while (1);

    return 0;
}
