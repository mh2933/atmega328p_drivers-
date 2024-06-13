#include <avr/io.h>
#include <avr/interrupt.h>

  /******************************************************************** 
   The right order the code should be written:

   1. Make the pin for the selected ADC channel an input pin.
      DDRC = 0x00.  

   2. ADCSRA Register - 
      Turn on the ADC module of the AVR because it is disabled upon 
      power-on reset to save power, and enable interrupt mode. Bit ADEN 
      and bit ADIE respectivly.
   3. Select the conversion speed. Setting bits ADPS2:0. 

   4. ADMUX Register - 
      Select voltage reference and ADC input channels. 
      Bit REFS0 and REFS1 sets the voltage reference. 

   5. ADCSRA Register - 
      Start the ADC conversion by setting bit ADSC to one.  

   6. Call the ISR with sei() function, Interrupt Service Routine.   

   7. adcResult - ADCL | ADCH << 8;
      The ADC conversion data is saved inside the two registers ADCL 
      and ADCH, register ADCH needs to be shifted one byte to the left
      and added to ADCL to get the whole 10 bit value.

   8. Vin =(adcResult * Vref) / 1024;
      Formatting to the right voltage value and printing that value
      to the console.

   9. ADCSRA |= (1 << ADSC);
      Bit ADSC is set to one again to enable a new conversion and then 
      the ISR function repeats.          

  ********************************************************************/

const float Vref   = 4.7;
float Vin          = 0.0;
uint16_t adcResult = 0; 

ISR(ADC_vect)
{
   /******************************************************************* 
      To fit the whole 10 bit value the ADCH register needs to be 
      leftshifted by 8 and bitwised AND with ADCL register and then
      assigned to a variable. 
    *******************************************************************/
   adcResult = ADCL | ADCH << 8;
  
   Vin = (adcResult * Vref) / 1024;
   
   Serial.print("Vin: ");
   Serial.println(Vin); // Print in decimal format
   
   /* New conversion is enabled with bit ADSC */
   ADCSRA |= (1 << ADSC);
}

int main(void)
{
  // Initialize serial communication
  Serial.begin(9600); // Adjust baud rate as needed

  DDRC = 0x00;

  
  /******************************************************************** 
  ADCSRA-register // Status And Control Register of ADC

     7    6    5     4    3    2     1     0
  |ADEN|ADSC|ADATE|ADIF|ADIE|ADPS2|ADPS1|ADPS0|

  Bit 7 (ADEN), ADC Enable.
  -To start each conversion you have to set this bit to one.

  Bit 3 (ADIE), Interrupt Enable.
  -This bit is set when an ADC conversion completes and the data 
  registers are updated. 

  Bit 2-0 (ADPS2-0), ADC Prescaler Select Bits.
  -These bits determine the division factor between the XTAL frequency
  and the input clock to the ADC. 
  All ones is equal to = CK/128 -> 125 kHz.
  ********************************************************************/
  ADCSRA = 0b10001111;

  /******************************************************************* 
  ADMUX-register 
    
     7     6     5     4    3    2    1    0
  |REFS1|REFS0|ADLAR|empty|MUX3|MUX2|MUX1|MUX0|

  bits 7 and 6(REFS1, REFS0) that sets 
  the reference voltage (AREF(external), AVCC or Internal 1,1 V).

  bits MUX3-MUX0 sets the ADC-channel 7-0.

  bit 5 ADLAR is by default set to 0 which is equal to left-justified 
  registers ADCH and ADCL, these two registers stores the ADC conversion 
  value. 
  10 bits are used and the first 8 bits are 
  spaced inside the first byte and and the remaining 2 bits are spaced
  inside the second register, in default-mode i.e. left shifted the 
  remaining two bits are fitted inside ADCL register.  

  AVCC and Analog channel ADC0 is set with the binary value 
  0b01000000. 
  ********************************************************************/
  ADMUX  = 0b01000000;

  /******************************************************************** 
  ADCSRA-register // Status And Control Register of ADC

     7    6    5     4    3    2     1     0
  |ADEN|ADSC|ADATE|ADIF|ADIE|ADPS2|ADPS1|ADPS0|

  Bit 6 (ADSC), ADC start conversion
  -To start each conversion you have to set this bit to one.
  ********************************************************************/
  ADCSRA |= (1 << ADSC);

  sei();

  while (1);

  return 0;

}