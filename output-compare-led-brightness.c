#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#include <util/setbaud.h>
#endif

#include <avr/io.h>

// Configuring UART Communication in order to send data to the serial monitor
void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // Enable RX and TX
}

void uart_write(char c) {
  // Sends 1 byte of data to the serial Monitor
  // Waits for USART Data Register to be empty by checking if the UDRE flag is set
  loop_until_bit_is_set(UCSR0A, UDRE0); // Wait until data register empty.
  UDR0 = c;
}

char uart_read(void) {
  // Receives  1 byte of data from the serial Monitor
  // Waits for UDR0 Data Register to have data that can be read by checking the RXC0 flag
  loop_until_bit_is_set(UCSR0A, RXC0); // Wait until data exists.
  return UDR0;
}

void uart_println(char *s) {
  // loop through entire string
  while (*s) {
    uart_write(*s);
    s++;
  }
  uart_write('\n');
}

void timer2_init() {
  TCCR2B |= (1<<CS20); // required to set up timer with no prescaling
  TCCR2A |= (1<<COM2A1 | 1<<WGM21 |1<<WGM20); // required to fast pwm in non-inverting mode
}

int main(void) {
  const int UPPER_BOUND = 9;
  const int STEP = 9;
  uart_init(); //initialising uart for serial communication
  uart_println("Please enter an integer value between 0 and 9:");
  int brightness = uart_read() - '0'; // convert ascii value to actual value
  if (brightness >= 0 || brightness <= UPPER_BOUND) {
    timer2_init();
    DDRB = (1<<PB3); // Setting OC2A data direction as output
    OCR2A = 255 * ( (float) brightness / (float) UPPER_BOUND ); // lower values == lower brightness

    while (1) {}
  } else {
    uart_println("Invalid value entered. Exiting.");
    return 1;
  }
  return 0;
}
