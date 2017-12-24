#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>

int main(void) {
  const int UPPER_BOUND = 16;
  int input = 0;
  int previousInput = 0;
  int counter = 0;

  DDRB = (1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3);

  while (1) {
    input = PIND & (1<<7);
    if (input != previousInput && input) {
      counter = (counter + 1) % UPPER_BOUND;
      PORTB = counter;
    }
    previousInput = input;
  }
  return 0;
}
