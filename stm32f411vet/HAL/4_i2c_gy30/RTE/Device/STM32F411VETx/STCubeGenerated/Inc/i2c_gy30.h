//ADDR = 'L'
// slave addr = 0b0100011

#define BH_Addr 0b0100011
#define BH_AddrRead  ((0b0100011<<1) | 1)
#define BH_AddrWrite ((0b0100011<<1) | 0)

#define BH_PowerOn   0x01
#define BH_PowerDown 0x00
#define BH_Reset     0x07 
#define BH_ModeH1    0x10
#define BH_ModeH2    0x11
#define BH_ModeL     0x13
#define BH_SigModeH  0x20
#define BH_SigModeH2 0x21
#define BH_SigModeL  0x23

void gy30_init(void);
double gy30_read(void);
