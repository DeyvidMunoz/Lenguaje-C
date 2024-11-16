#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include "seguridad.h"
#include "config.h"
#include "sensores.h"

typedef enum {
    INIT,
    BLOQUEADO,
    MONITOREO_AMBIENTAL,
    MONITOREO_EVENTOS,
    ALARMA,
    ALERTA,
} Estado;

Estado estado_actual = INIT;

int count_1000ms = 0;
int count_2000ms = 0;
int count_3000ms = 0;
unsigned char flag_1s = 0;
unsigned char flag_2s = 0;
unsigned char flag_3s = 0;

#define TIMEROUT_1S 1000
#define TIMEROUT_2S 2000
#define TIMEROUT_3S 3000

float celsius;
int humedad, luz;
int puerta1, puerta2;

void inicializar(){
count_1000ms = 0;
count_2000ms = 0;
count_3000ms = 0;
flag_1s = 0;
flag_2s = 0;
flag_3s = 0;
}

void inicializar_sistema() {
    LCD_Init();
    keypad_init();
    adc_int();
}
unsigned char clave=0;

void manejar_estado_init() {
    funcion_seguridad();
    if (clave == 1) {
        estado_actual = MONITOREO_AMBIENTAL;
        inicializar();
    } else if (clave == 0) {
        estado_actual = INIT;
    } else if (clave == 2) {
        estado_actual = BLOQUEADO;
    }
}

void manejar_estado_bloqueado() {
    sistema_bloqueado();
    if (flag_3s) { 
        estado_actual = INIT;
    }
}

void manejar_estado_monitoreo_ambiental() {
    ambiental();  
    if (celsius > 25 || luz > 700) {
        estado_actual = ALARMA;
        inicializar();
    } else if (flag_3s) {
        estado_actual = MONITOREO_EVENTOS;
        inicializar();
    }
}

void manejar_estado_monitoreo_eventos() {
    puertas();  
    if (puerta1 == 0 || puerta2 == 0) {
        estado_actual = ALERTA;
        inicializar();
    } else if (flag_2s) {
        estado_actual = MONITOREO_AMBIENTAL;
        inicializar();
    }
}

void manejar_estado_alarma() {
    LCD_String_xy(0, 0, "ALARMA");
    if (flag_3s) {
        estado_actual = MONITOREO_AMBIENTAL;
        inicializar();
    }
}

void manejar_estado_alerta() {
    LCD_String_xy(0, 0, "ALERTA");
    if (flag_2s) {
        estado_actual = INIT;
    }
}

void Timer1_start();
void main() {
    inicializar_sistema();
    Timer1_start();
    while (1) {
        switch (estado_actual) {
            case INIT:
                manejar_estado_init();
                break;
            case MONITOREO_AMBIENTAL:
                manejar_estado_monitoreo_ambiental();
                break;
            case MONITOREO_EVENTOS:
                manejar_estado_monitoreo_eventos();
                break;
            case ALARMA:
                manejar_estado_alarma();
                break;
            case ALERTA:
                manejar_estado_alerta();
                break;
            case BLOQUEADO:
                manejar_estado_bloqueado();
                break;
            default:
                estado_actual = INIT;  // Reiniciar en caso de error
                break;
        }
    }
}

// Rutina de Interrupción del Timer
void __interrupt() Timer1_ISR() {
    TMR1 = 0xFC16;  // Recarga para retardo de 1 ms

    // Actualización de contadores y flags
    count_1000ms++;
    count_2000ms++;
    count_3000ms++;

    if (count_1000ms >= TIMEROUT_1S) {
        count_1000ms = 0;
        flag_1s = 1;
    }
    if (count_2000ms >= TIMEROUT_2S) {
        count_2000ms = 0;
        flag_2s = 1;
    }
    if (count_3000ms >= TIMEROUT_3S) {
        count_3000ms = 0;
        flag_3s = 1;
    }

    PIR1bits.TMR1IF = 0; // Limpiar bandera de interrupción
}

void Timer1_start() {
    GIE = 1;          // Habilitar Interrupción Global
    PEIE = 1;         // Habilitar Interrupción de Periféricos
    TMR1IE = 1;       // Habilitar Interrupción de Desbordamiento del Timer1
    TMR1IF = 0;
    T1CON = 0x00;     // Configuración del Timer1
    TMR1 = 0xFC16;    // Cargar el valor para retardo de 1 ms
    TMR1ON = 1;       // Encender Timer1
}
