#include <xc.h>
#include <pic16f887.h>
#include "adc.h"
#include "config.h"


void adc_int(void){
    ADCON1bits.ADFM = 1; 
    ADCON1bits.VCFG0 = 0; 
    ADCON1bits.VCFG1 = 0; 
    ADCON0bits.ADCS = 0b01; 
    ADRESH=0;
    ADRESL=0;
}


unsigned int adc_read(int channel) {
    
    ADCON0bits.CHS =(0x0F & channel); 
    ADCON0bits.ADON = 1;  
    __delay_us(30);
    ADCON0bits.GO_DONE = 1;     
    while (ADCON0bits.GO_DONE);   
    unsigned int value_adc = ADRESH;
    value_adc =(value_adc<<8)+ADRESL;
    return value_adc; 
}



