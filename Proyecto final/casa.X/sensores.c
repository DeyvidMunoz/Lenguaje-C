#include <xc.h>
#include <pic16f887.h>
#include <stdio.h>
#include "string.h"
#include "config.h"
#include "lcd.h"
#include "adc.h"
#include "sensores.h"

char StringTemperature[16];
extern int luz;
int luz1;
void ambiental(){
    OSCCON = 0x71;
    LCD_Init();
    LCD_String_xy(0,0,"MONITOREO AMBIENTAL");
    __delay_ms(2000);
    LCD_Clear();
    TRISA0 = 1;
    TRISA1 = 1;
    ANSEL = 0x03;
    ANSELH= 0x00;
    adc_int();  
    
        LCD_String_xy (0,0,"Sensor");
        LCD_Command (0xC0);
        unsigned int temperatura = adc_read(0);
          luz = adc_read(1);
       // celsius = (temperatura*4.88);
        //celsius = (celsius/10.00);
        //sprintf(StringTemperature, "%d%cC  ",(int)celsius, 0xDF);
        int value_adc = 1023-(int)temperatura;
        celsius = (float)(value_adc * 0.04058);
        sprintf(StringTemperature, "T: %.2f L:%d", celsius, luz);   
        //LCD_String_xy (1,0,"TEMP: ");
        LCD_String(StringTemperature);
        //LCD_String ("   " );
        __delay_ms(2000);
        LCD_Clear();
}
void puertas(){
    TRISA2 = 1;  
    TRISA3 = 1;  
    ANSEL = 0x03;
    int puerta1 = RA2;  
    int puerta2 = RA3;  

    LCD_String_xy(0, 0, "Puertas:");

    if (puerta1 == 1 && puerta2 == 1) {
        LCD_String_xy(1, 0, "Ambas Cerradas");
    } else if (puerta1 == 1 && puerta2 == 0) {
        LCD_String_xy(1, 0, "P1 Ce ,P2 Ab");
    } else if (puerta1 == 0 && puerta2 == 1) {
        LCD_String_xy(1, 0, "P1 Ab, P2 Ce");
    } else {
        LCD_String_xy(1, 0, "Ambas Abiertas");
    }

    __delay_ms(2000);
    LCD_Clear();
}





