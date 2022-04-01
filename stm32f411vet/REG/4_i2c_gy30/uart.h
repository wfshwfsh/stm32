#include <stdint.h>
void uart2_config(void);
void UART2_SendChar (uint8_t c);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);