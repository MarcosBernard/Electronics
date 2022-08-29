#define TRISBUSLCD  TRISB
#define BUSLCD    PORTB

#define RS   PORTBbits.RB1
#define RW  PORTBbits.RB2
#define E      PORTBbits.RB3
#define TRIS_RS	 TRISBbits.TRISB1
#define TRIS_RW	 TRISBbits.TRISB2
#define TRIS_E	 TRISBbits.TRISB3

void LCD_delay (void);
void LCD_Init(void);
void escribir_comando(char comando);
void escribir_caracter(char caracter);
void escribir_cadena(char *cadena);
char leer_direccion_DDRAM(void);
void escribir_caracter_especial(char*DirCGRAM);

char direccion_DDRAM;
char CGRAM1[] ={0b00001010,
                                0b00001010,
                                0b00001010,
                                0b00001010,
                                0b00000000,
                                0b00010001,
                                0b00001110,
                                0b00000000,};