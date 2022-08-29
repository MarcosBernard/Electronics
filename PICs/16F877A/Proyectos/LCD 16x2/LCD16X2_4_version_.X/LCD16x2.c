#include <xc.h>
#include "Configuration_bits.h"
#include "LCD16x2.h"

void LCD_delay (void){
    __delay_us(1);
}
void LCD_Init(void){ 
    TRIS_RS = 0;TRIS_RW = 0;TRIS_E = 0;
    RS=0;RW=0;E=0;
    TRISBUSLCD = 0x01;
    //BUSLCD = 0x00; 
    BUSLCD = 0b00100000;
    LCD_delay();
    E = 1;
    LCD_delay();
    E = 0;
    BUSLCD = 0x00;
    
}
void escribir_comando(char comando){
    BUSLCD = (comando)&0xF0;
    LCD_delay();E = 1;LCD_delay();E = 0;LCD_delay();
    BUSLCD = (comando<<4)&0xF0;
    LCD_delay();E = 1;LCD_delay();E = 0;LCD_delay();
    BUSLCD = 0x00;
}
void escribir_caracter(char caracter){
    BUSLCD = (caracter)&0xF0;
    RS = 1; LCD_delay();E = 1;LCD_delay();E = 0;LCD_delay();RS = 0; //Rutina de escritura
    BUSLCD = (caracter<<4)&0xF0;
    RS = 1;LCD_delay();E = 1;LCD_delay();E = 0;LCD_delay();RS = 0;//Rutina de escritura
    BUSLCD = 0x00;
}
void escribir_cadena(char *cadena){
    char i = 0;
    while(cadena[i]!=0) {
	escribir_caracter(cadena[i]);
	i++;
    }
}
char leer_direccion_DDRAM(void){
    TRISBUSLCD=0xF0;
    RW=1; LCD_delay();E=1;LCD_delay();
    direccion_DDRAM=(BUSLCD&0xF0);
    E=0;LCD_delay();E=1;LCD_delay();
    direccion_DDRAM=(((BUSLCD&0xF0)>>4)&0x0F)|direccion_DDRAM;
    E=0;RW=0;LCD_delay();
    TRISBUSLCD=0x00;
    return(direccion_DDRAM);
}
void escribir_caracter_especial(char*DirCGRAM){
    direccion_DDRAM =  leer_direccion_DDRAM();
    escribir_comando(0b01000000|*DirCGRAM);
    for(char i = 0; i<8;i++){
	escribir_caracter(CGRAM1[i]);
    }
    escribir_comando(0b10000000|direccion_DDRAM);
}