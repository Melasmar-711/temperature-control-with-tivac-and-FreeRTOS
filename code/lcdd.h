
#define LCD_CTRLP GPIO_PORTA_DATA_R
#define LCD_DATAP GPIO_PORTB_DATA_R
#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */
#define HIGH 1
#define LOW 0


#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80



void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD4bit_Cmd(unsigned char command);
void LCD4bit_Data(unsigned char data);
void LCD4bit_String(const char *Str);
void int_to_number_print(int number);
	void LCD_moveCursor(unsigned char row,unsigned char col);