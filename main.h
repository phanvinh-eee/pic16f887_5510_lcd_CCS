#include <18F4550.h>
#device PASS_STRINGS=IN_RAM

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(crystal=20000000)
#define lcd_sclk  PIN_A0 
#define lcd_sda   PIN_A1              
#define lcd_dc    PIN_A2                     
#define lcd_cs    PIN_A3                                                                            
#define lcd_res   PIN_A5                                                                                      
                                                                                                     
#include "5110lib\3310(modified).c"
