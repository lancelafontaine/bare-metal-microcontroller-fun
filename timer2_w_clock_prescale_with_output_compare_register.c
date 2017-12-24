#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>

void clock_prescale() {
  CLKPR = (1<<CLKPCE); // enable changes to the clock prescaler
  CLKPR = (1<<CLKPS3); // make clock prescaler divide by 256
}

void timer2_init() {
  TCCR2B |= (1<<CS20); // set up timer with no prescaling
  TCCR2A |= (1<<COM2A0); // sets to toggle OC2A at compare value
}


int main(void) {
  OCR2A = 128; // sets to midway through 8-bit count, 50% duty cycle
  DDRB = (1<<PB3); // Setting OC2A data direction as output

  clock_prescale();
  timer2_init(); // initialize the timer

  while (1) {
  }
  return 0;
}
