#define TRISBUSLCD  TRISD
#define BUSLCD    PORTD

#define RS   PORTDbits.RD5
#define RW  PORTDbits.RD6
#define E      PORTDbits.RD7
#define TRIS_RS	 TRISDbits.TRISD5
#define TRIS_RW	 TRISDbits.TRISD6
#define TRIS_E	 TRISDbits.TRISD7

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