#include <xc.h>
#include "Configuration_bits.h"
#include "LCD16x2.h"

void main(void) 
{
    LCD_delay();
    LCD_Init();
      
    escribir_comando(0b00001111);
    escribir_caracter('3');
    escribir_cadena("Prueba 3");
    escribir_caracter_especial(0b00000000);
    escribir_caracter(0);
    
    while(1);
    return;
}