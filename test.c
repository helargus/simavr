#define F_CPU 16000000

#include <avr/io.h>
#include <stdint.h>
#include <sim_vcd_file.h>
#include <avr/avr_mcu_section.h>

// Tell simulator the AVR type
AVR_MCU(F_CPU, "atmega32");

// Tell simulator file name and length of simulation in micro seconds
AVR_MCU_VCD_FILE("test-output.vcd", 1000);

/*
 * Define three 8-bit signals to record for vcd-output file.
 * In the output it can be seen that on PINC data arrives from
 * vcd-input but on PORTC there is no change.
*/
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
  { AVR_MCU_VCD_SYMBOL("PORT_B"), .what = (void*)&PORTB, },
  { AVR_MCU_VCD_SYMBOL("PIN_C"), .what = (void*)&PINC, },
  { AVR_MCU_VCD_SYMBOL("PORT_C"), .what = (void*)&PORTC, },
};

void main(void)
{
  // configure PINC as input
  DDRC = 0x00;
  DDRB = 0x01;
  uint8_t c = 0;
  for (uint8_t i=0; i<255; i++)
    {
      c = PINC;
      if (c >= 1)
	{
           PORTB = c;
	}
      else
	{
           PORTB = i;
	}
    }
}

