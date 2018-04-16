#ifndef __TIME_H
#define	__TIME_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"


#define TIME_TICK_MS                                     1  
#define TIME_TICK_US                                     (TIME_TICK_MS * 1000)  

extern int times;

extern void System_tim2_init(void);
extern void System_Time2_NVIC_Init(void);
extern void Delay_ms(uint32_t time);
void init_tim2();
#endif /* __TIME_H */

