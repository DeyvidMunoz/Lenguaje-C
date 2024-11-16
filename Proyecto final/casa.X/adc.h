/* 
 * File:   adc.h
 * Author: usuario
 *
 * Created on 17 de octubre de 2024, 7:56
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

    void adc_int(void);
    unsigned int adc_read(int channel);
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

