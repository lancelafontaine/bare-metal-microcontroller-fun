#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

void timer0_init() {
  TCCR0B |= (1<<CS00); // set up timer with no prescaling
  TCNT0 = 0; // initial counter value
}


int main(void) {
  DDRC = (1<<PC0); // connects LED as output

  timer0_init(); // initialize the timer

  while (1) {
    if (TCNT0 >= 191) {
      PORTC ^= (1<<0); // toggle LED
      TCNT0 = 0; // reset timer
      _delay_ms(500);
    }
  }
  return 0;
}

