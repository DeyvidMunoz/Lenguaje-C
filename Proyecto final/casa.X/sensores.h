/* 
 * File:   sensores.h
 * Author: usuario
 *
 * Created on 18 de octubre de 2024, 15:50
 */

#ifndef SENSORES_H
#define	SENSORES_H

#ifdef	__cplusplus
extern "C" {
#endif

    void ambiental();
    void puertas();
    extern float celsius;
    extern int luz;
    extern int puerta1;
    extern int puerta2;
    unsigned int read_temperatura();
    unsigned int read_luz();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSORES_H */

