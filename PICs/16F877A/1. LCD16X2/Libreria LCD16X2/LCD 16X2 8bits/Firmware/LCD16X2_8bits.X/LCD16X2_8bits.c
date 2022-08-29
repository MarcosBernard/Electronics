#include "LCD16X2_8bits.h"
#define _XTAL_FREQ 4000000

void exec_time1(void)
{
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}
void exec_time2(void)
{
    EN = 1;
    __delay_us(50);
    EN = 0;
    __delay_us(50);
}
void clear_disp(void)
{
    BUSLCD = 0x01;
    exec_time1();

}
void return_home(void)
{   
    BUSLCD = 0x02;
    exec_time1();

}
void enviar_inst_8bits(unsigned char instruction)
{
    BUSLCD = instruction;
    exec_time2();
    BUSLCD = 0x00;
}
void Init_LCD(void)
{
    TRISEN = 0;
    EN = 0;
    TRISRW = 0;
    RW = 0;
    TRISRS = 0;
    RS = 0;
    TRISBUSLCD = 0;
    BUSLCD = 0;

    clear_disp();
    return_home();
    enviar_inst_8bits(Entry_mode | when_write_cursor_right | when_write_no_shift);
    enviar_inst_8bits(display_on | show_cursor_on | cursor_blink_on);
    enviar_inst_8bits(bus_8bits | lines_2 | dots_5_8);
}
void gotoxy(unsigned char y, unsigned char x)
{
    //Modo 2 líneas
    if (y == 0)
    {
	enviar_inst_8bits(set_DDRAM_add | x + 0x40); //(x >= 0x40 && x <= 0x67)
    }
    else if (y == 1)
    {
	enviar_inst_8bits(set_DDRAM_add | x); //(x>=0&&x<=0x27)
    }
}
void write_DDRAM(char character)
{
    RS = 1;
    BUSLCD = character;
    exec_time2();
    BUSLCD = 0x00;
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

void printCGRAM(char *cadena)
{
    char i = 0;
    while (i < 8)
    {
	write_DDRAM(cadena[i]);
	i++;
    }
}



char get_add(void){
    char add = 0;
    RW = 1;
    __delay_ms(1);
    add = (BUSLCD&(0b01111111));
    __delay_ms(1);
    return(add);
}

void WriteCGRAM(char direccionCGRAM, char *dirSpecialChar){
    char DDRAM_add = get_add();
    direccionCGRAM *= 8;
    enviar_inst_8bits(set_CGRAM_add|direccionCGRAM);
    printCGRAM(dirSpecialChar);
    enviar_inst_8bits(set_DDRAM_add|DDRAM_add);
}