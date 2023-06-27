/**
*	drv_usart.h
*	@Author:CJQ2805
*/

#ifndef __DRV_USART_H
#define __DRV_USART_H
#include "main.h"
#include "fifo.h"
int32_t E95_data_fifo_init(void);

extern FIFO_CTRL_T UartDataFifo;
#endif
