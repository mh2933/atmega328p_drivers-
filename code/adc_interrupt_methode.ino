#include <avr/io.h>
#include <avr/interrupt.h>

const float Vref   = 4.7;
float Vin          = 0.0;
uint16_t adcResult = 0; 

ISR(ADC_vect)
{
  // Combine ADCL and ADCH to get the full 16-bit ADC result
  adcResult = ADCL;
  adcResult += ADCH << 8;
  ADCSRA |= (1 << ADSC);

  Vin =(adcResult * Vref) / 1024;

  // Display the ADC result to the console
  Serial.println(Vin);
  _delay_ms(100); // Short delay for stability
}

int main(void)
{
  // Initialize serial communication
  Serial.begin(9600); // Adjust baud rate as needed

  DDRC = 0;

  ADCSRA = 0b10001111;
  ADMUX  = 0b01000000;
  ADCSRA |= (1 << ADSC);

  sei();

  while (1);

  return 0;

}