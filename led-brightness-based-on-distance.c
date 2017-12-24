#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#include <util/setbaud.h>
#endif

#include <avr/io.h>
#include <util/delay.h>


void timer2_init() {
  TCCR2B |= (1<<CS20); // required to set up timer with no prescaling
  TCCR2A |= (1<<COM2A1 | 1<<WGM21 |1<<WGM20); // required to fast pwm in non-inverting mode
}

void AD_setup(){
  ADCSRA|=(1<<ADEN)|(1<<ADPS2); //enable with prescalar  at 16 (65kHz conversion clock speed)
  ADMUX|= (1<<6);// RFS0 // Vcc ( 5v) conversion scale
}

int main(void){
  AD_setup();
  timer2_init();
  DDRB = (1<<PB3); // Setting OC2A data direction as output
  while(1) {
    ADCSRA |= (1<<ADSC); //Start Conversion
    while(!(ADCSRA & (1<<ADIF))){} //wait for ADIF to go to 0, indicating conversion complete.
    ADCSRA |= (1<<ADIF); //Reset ADIF to 1 for the next conversion
    // ADC tends to range from ~200..~1000
    // Scale to desired 0..255 range for LED
    int brightness = ((float) (ADC - 100.0)) / 4.0;
    if (brightness < 0) {
      brightness = 0;
    }
    if (brightness > 255) {
      brightness = 255;
    }
    OCR2A = brightness;
     _delay_ms(512);
  }
}
