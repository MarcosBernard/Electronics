#include <xc.h>
#include "LCD16X2_8bits.h"
#include "Conf_bits.h"

void main(void)
{
    Init_LCD();
    gotoxy(1,2);
    printLCD("Test");
    gotoxy(0,2);
    printLCD("8bits");
    WriteCGRAM(0, SPCH1);
    printLCD(0);
    
    while(1);
    return;
}
