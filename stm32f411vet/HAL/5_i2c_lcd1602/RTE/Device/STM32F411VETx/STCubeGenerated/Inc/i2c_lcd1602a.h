
#define ADDR_PCF8574 0x4E
#define SLAVE_ADDRESS_LCD ADDR_PCF8574

void lcd1602a_send_cmd(char _cmd);
void lcd1602a_send_data(char _data);
void lcd1602a_init(void);
void lcd_clear (void);
void lcd_put_cur(int row, int col);

void lcd_send_string (char *str);
