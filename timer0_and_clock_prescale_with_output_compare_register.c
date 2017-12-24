#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>

void clock_prescale() {
  CLKPR = (1<<CLKPCE); // enable changes to the clock prescaler
  CLKPR = (1<<CLKPS3); // make clock prescaler divide by 256
}

void timer0_init() {
  //TCCR0B |= (1<<CS00 | 1<<CS02); // set up timer with clk/1024 prescaling
  TCCR0A |= (1<<COM0A0); // sets to toggle OC0A at compare value
}


int main(void) {
  OCR0A = 128; // sets to midway through 8-bit count, 50% duty cycle
  DDRD = (1<<PD6); // Setting OC0A data direction as output

  clock_prescale();
  timer0_init(); // initialize the timer

  while (1) {
  }
  return 0;
}
