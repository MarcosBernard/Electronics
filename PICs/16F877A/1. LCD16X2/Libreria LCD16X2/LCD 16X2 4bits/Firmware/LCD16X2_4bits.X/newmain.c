#include <xc.h>
#include "Conf_bits.h"
#include "LCD16X2_4bits.h"

void main(void)
{
    Init_LCD();
    gotoxy(0,2);
    printLCD("Hola mundo!");
    
    while(1);
    return;
}
