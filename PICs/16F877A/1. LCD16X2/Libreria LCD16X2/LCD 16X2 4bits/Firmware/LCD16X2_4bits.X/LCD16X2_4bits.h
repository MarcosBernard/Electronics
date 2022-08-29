#include <xc.h>
void Init_LCD(void); //Inicializa por defecto en escritura latino europea
void exec_time1(void);
void exec_time2(void);
void enviar_inst_4bits(unsigned char instruction);
#define TRISEN TRISDbits.TRISD5
#define TRISRW TRISDbits.TRISD6
#define TRISRS TRISDbits.TRISD7
#define EN PORTDbits.RD5
#define RW PORTDbits.RD6
#define RS PORTDbits.RD7
#define TRIS_D4 TRISDbits.TRISD0
#define TRIS_D5 TRISDbits.TRISD1
#define TRIS_D6 TRISDbits.TRISD2
#define TRIS_D7 TRISDbits.TRISD3    
#define D4 PORTDbits.RD0
#define D5 PORTDbits.RD1
#define D6 PORTDbits.RD2
#define D7 PORTDbits.RD3

void clear_disp(void); //funcion dedicada
void return_home(void); //funcion dedicada

#define Entry_mode                  0b00000100
#define when_write_cursor_right     0b00000010  //DDRAM increments when write
#define when_write_cursor_left      0b00000000  //DDRAM decrements when write
#define when_write_shift            0b00000001  //when write display shift accordingly to I/D
#define when_write_no_shift         0b00000000  //when write display won't shift

#define disp_on_off_control 0b00001000
#define display_on          0b00001100
#define display_off         0b00001000
#define show_cursor_on      0b00001110
#define show_cursor_off     0b00001100
#define cursor_blink_on     0b00001001
#define cursor_blink_off    0b00001000

#define cursor_disp_shift   0b00010000
#define shift_display       0b00011000
#define shift_cursor        0b00010000
#define shift_right         0b00010100
#define shift_left          0b00010000

#define function_set        0b00100000
#define bus_8bits           0b00110000
#define bus_4bits           0b00100000
#define lines_2             0b00101000
#define line_1              0b00100000
#define dots_5_10           0b00100100
#define dots_5_8            0b00100000

#define set_CGRAM_add       0b01000000

#define set_DDRAM_add       0b10000000

//Lectura (RS=0 RW=1):
void leer_busy_flag(void);

//Escribir en DDRAM (RS = 1 RW = 0):
void write_DDRAM(char character); ////void write_DDRAM(void);

//Escribir en CGRAM (RS = 1 RW = 0):
void write_CGRAM(char *character);

//Leer dato en DDRAM o CGRAM(RS=1 RW=1):
void read_DDRAM_or_CGRAM(void);

//Funciones de programa
void gotoxy(unsigned char x, unsigned char y); //X: posición horizontal (depende 1 linea: 00-4F o dos lineas: Y=0:40h-67h  Y=1: 0-27h)
//Y: posición vertical (0 o 1)
void printLCD(char *cadena);

/*Instrucciones:
 * Escritura (RS=0 RW=0):
 * 1. clear display:    0x01
 * 2. Return home:      0x02
 * 
 * 3. Entry mode set:   0b000001 ID S
 * ID: when write display cursor movement control
 * S:  when write display shift control
 * 
 * 4. Dis/onoff control:0b00001DCB
 * D: display on when 1 and off when 0
 * C: show cursor when 1 and not when 0
 * B: cursor blinks whe 1 and not when 0
 * 
 * 5. Cursor/dis_shift: 0b0001 S/C R/L 00
 * S/C: Display shift when 1 or Cursor shift when 0
 * R/L: Shift to righy when 1 or Shift to left when 0 
 * 
 * 6. Function set:     0b001 DL N F 00
 * DL: 8bits when 1 or 4bits when 0
 * N: 2 lines when 1 or 1 line when 0
 * F: 5x10 dots when 1 or 5x8 dots when 0
 * 
 * 7. Set CGRAM add:    0b01xxxxxx
 * 
 * 8. Set DDRAM add:    0b1xxxxxxx
 *
 * Lectura (RS=0 RW=1):
 * 1. Read busy flag
 *    and address   :   BF AC AC AC AC AC AC AC
 *    BF=1: internal operation is being performed
 *    AC=Address counter content
 * 
 * Escribir caracter (DDRAM) o linea n en CGRAM
 * (RS=1 RW=0):         0bxxxxxxxx
 *  xxxxxxxx: dato a escribir
 * 
 * Leer dato desde la DDRAM o CGRAM
 * (RS=1 RW=1):         0brrrrrrrr
 *  rrrrrrrr: dato a leer
 */