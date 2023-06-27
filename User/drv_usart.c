/**
*  drv_usart.c
*
*  @Author：CJQ2805
*/

#include "drv_usart.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_ll_usart.h"

FIFO_CTRL_T UartDataFifo;
#define MAX_FIFO_BUF_LEN  5000
uint8_t UartFifoBuf[MAX_FIFO_BUF_LEN];

//void  USART_CharReception_Callback(void)
//{
//	 uint8_t u8Data;
//	 u8Data = LL_USART_ReceiveData8(USART2);
//	 fifo_add_node_polite(&E95DataFifoCtrl, &u8Data);
//}


void usart_data_decode(void)
{

	uint32_t u32data_len = 0;
	uint8_t buf[100];	
	uint8_t *pNode;
	
	u32data_len = fifo_get_node_num(&UartDataFifo);
	
	if(u32data_len == 0)
		return;
	
	for(uint32_t i = 0; i<u32data_len; i++)
	{
		pNode = fifo_get_node(&UartDataFifo);		
		buf[i] = *pNode;
		fifo_delete_node(&UartDataFifo);		
	}

	u32data_len = u32data_len;
}


int32_t Uart_data_fifo_init(void)
{
	int32_t ret;
	ret = fifo_init(&UartDataFifo, sizeof(UartFifoBuf), 1, UartFifoBuf);
	return ret;
}
