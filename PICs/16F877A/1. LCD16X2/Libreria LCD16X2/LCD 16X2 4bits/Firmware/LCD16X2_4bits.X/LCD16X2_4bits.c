#include "LCD16X2_4bits.h"
#include "Conf_bits.h"

void exec_time1(void)
{
    //__delay_ms(1);
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void exec_time2(void)
{
//    __delay_us(1);
    EN = 1;
    __delay_us(50);
    EN = 0;
    __delay_us(50);
}

void clear_disp(void)
{
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    exec_time1();
    D4 = 1;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    exec_time1();
}

void return_home(void)
{
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    exec_time1();
    D4 = 0;
    D5 = 1;
    D6 = 0;
    D7 = 0;
    exec_time1();
}

void enviar_inst_4bits(unsigned char instruction)
{
    unsigned char instruction1 = 0x00, instruction2 = 0x00;
    instruction1 = (instruction >> 4)&0x0F;
    instruction2 = instruction & 0x0F;
    D4 = instruction1 & 0x01;
    D5 = (instruction1 & 0x02) >> 1;
    D6 = (instruction1 & 0x04) >> 2;
    D7 = (instruction1 & 0x08) >> 3;
    exec_time2();
    D4 = instruction2 & 0x01;
    D5 = (instruction2 & 0x02) >> 1;
    D6 = (instruction2 & 0x04) >> 2;
    D7 = (instruction2 & 0x08) >> 3;
    exec_time2();
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
}

void Init_LCD(void)
{
    TRISEN = 0;
    EN = 0;
    TRISRW = 0;
    RW = 0;
    TRISRS = 0;
    RS = 0;
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;

    //Inicialización 4 bits
    D7 = 0;
    D6 = 0;
    D5 = 1;
    D4 = 0;
    exec_time1();
    
    clear_disp();
    return_home();
    enviar_inst_4bits(bus_4bits | lines_2 | dots_5_8);
    enviar_inst_4bits(Entry_mode | when_write_cursor_right | when_write_no_shift);
    enviar_inst_4bits(display_on | show_cursor_on | cursor_blink_on);
}

void gotoxy(unsigned char y, unsigned char x)
{
    //Modo 2 líneas
    if (y == 0)
    {
	enviar_inst_4bits(set_DDRAM_add | x + 0x40); //(x >= 0x40 && x <= 0x67)
    }
    else if (y == 1)
    {
	enviar_inst_4bits(set_DDRAM_add | x); //(x>=0&&x<=0x27)
    }
}

void write_DDRAM(char character)
{
    RS = 1;
    enviar_inst_4bits(character);
    RS = 0;
}

void printLCD(char *cadena)
{
    char i = 0;
    while (cadena[i] != 0)
    {
	write_DDRAM(cadena[i]);
	i++;
    }
}
