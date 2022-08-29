#include <xc.h>
#include "Configuration_bits.h"



void main(void)
{
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    
    TRISD = 0x00;
    PORTD = 0b10101010;
    while(1);
    return;
}

void __interrupt() ISR(){
    if(INTCONbits.INTF == 1){
	PORTD = (~PORTD);
	INTCONbits.INTF = 0;
    }
}