#include "fifo.h"



int8_t fifo_init(FIFO_CTRL_T *ptFifoCtrl,uint32_t u32NodeMaxNum,uint32_t u32NodeLen,void *pNodeArray)
{
	LM_ASSERT(ptFifoCtrl != NULL);
	LM_ASSERT(pNodeArray != NULL);
	LM_ASSERT(u32NodeLen != 0 );
	LM_ASSERT(u32NodeMaxNum >= FIFO_NODE_MIN);
	
	memset(pNodeArray,0,u32NodeMaxNum*u32NodeLen);

	ptFifoCtrl->u32NodeMaxNum = u32NodeMaxNum;
	ptFifoCtrl->u32NodeLen = u32NodeLen;
	ptFifoCtrl->u32ReadAdd = 0;
	ptFifoCtrl->u32WriteAdd = 0;

	ptFifoCtrl->ptNodeBufAddr = (uint8_t *)pNodeArray;

	return SUCC;
}

int8_t fifo_is_empty(FIFO_CTRL_T *ptFifoCtrl)
{	
	LM_ASSERT(ptFifoCtrl != NULL);
	
	return (ptFifoCtrl->u32ReadAdd == ptFifoCtrl->u32WriteAdd)?TRUE:FALSE;
}

int8_t fifo_is_full(FIFO_CTRL_T *ptFifoCtrl)
{
	if(((ptFifoCtrl->u32WriteAdd + 1)%ptFifoCtrl->u32NodeMaxNum) == ptFifoCtrl->u32ReadAdd)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

uint32_t fifo_get_node_num(FIFO_CTRL_T *ptFifoCtrl)
{
	if(ptFifoCtrl->u32WriteAdd >= ptFifoCtrl->u32ReadAdd)
	{
		return (ptFifoCtrl->u32WriteAdd - ptFifoCtrl->u32ReadAdd);
	}
	else
	{
		return (ptFifoCtrl->u32WriteAdd + ptFifoCtrl->u32NodeMaxNum - ptFifoCtrl->u32ReadAdd);
	}
	
}

int8_t fifo_add_node_polite(FIFO_CTRL_T *ptFifoCtrl,void *pNodeData)
{
	void *pCurNodeDataAdd = NULL;
	if(fifo_is_full(ptFifoCtrl))
	{
		return FAIL;
	}
	
	pCurNodeDataAdd = (void *)(ptFifoCtrl->ptNodeBufAddr + ptFifoCtrl->u32NodeLen*ptFifoCtrl->u32WriteAdd);
	memcpy(pCurNodeDataAdd,pNodeData,ptFifoCtrl->u32NodeLen);

	ptFifoCtrl->u32WriteAdd = (ptFifoCtrl->u32WriteAdd+1) % ptFifoCtrl->u32NodeMaxNum;
	return SUCC;
}

int8_t fifo_add_node_impolite(FIFO_CTRL_T *ptFifoCtrl,void *pNodeData)
{
	void *pCurNodeDataAdd = NULL;

	if(fifo_is_full(ptFifoCtrl))
	{
		fifo_delete_node(ptFifoCtrl);
	}

	pCurNodeDataAdd = (void *)(ptFifoCtrl->ptNodeBufAddr + ptFifoCtrl->u32NodeLen*ptFifoCtrl->u32WriteAdd);

	memcpy(pCurNodeDataAdd,pNodeData,ptFifoCtrl->u32NodeLen);

	ptFifoCtrl->u32WriteAdd = (ptFifoCtrl->u32WriteAdd+1) % ptFifoCtrl->u32NodeMaxNum;
	
	return SUCC;
}

void * fifo_get_node(FIFO_CTRL_T *ptFifoCtrl)
{
	void * pCurNodeDataAdd = NULL;

	if(ptFifoCtrl->u32ReadAdd == ptFifoCtrl->u32WriteAdd)
		return NULL;
	
	pCurNodeDataAdd = (void *)(ptFifoCtrl->ptNodeBufAddr + ptFifoCtrl->u32NodeLen*ptFifoCtrl->u32ReadAdd);	

	return pCurNodeDataAdd;
}

int8_t fifo_delete_node(FIFO_CTRL_T *ptFifoCtrl)
{
	if(ptFifoCtrl->u32WriteAdd == ptFifoCtrl->u32ReadAdd)
		return FAIL;

	ptFifoCtrl->u32ReadAdd = (ptFifoCtrl->u32ReadAdd+1) % ptFifoCtrl->u32NodeMaxNum; 	
	return SUCC;
}

int8_t fifo_clear(FIFO_CTRL_T *ptFifoCtrl)
{
	LM_ASSERT(ptFifoCtrl != NULL);

	ptFifoCtrl->u32ReadAdd = 0;
	ptFifoCtrl->u32WriteAdd = 0;

	return SUCC;
}

int8_t fifo_delete_latest_node(FIFO_CTRL_T *ptFifoCtrl)
{
	LM_ASSERT(ptFifoCtrl != NULL);

	if(ptFifoCtrl->u32ReadAdd == ptFifoCtrl->u32ReadAdd)
		return FAIL;

	if(ptFifoCtrl->u32WriteAdd > 0)
	{
		ptFifoCtrl->u32WriteAdd--;
	}
	else
	{
		ptFifoCtrl->u32WriteAdd = ptFifoCtrl->u32NodeMaxNum-1;
	}

	return SUCC;
}

int32_t fifo_get_remain_empty_node_num(FIFO_CTRL_T *ptFifoCtrl)
{
	LM_ASSERT(ptFifoCtrl != NULL);

	return (ptFifoCtrl->u32NodeMaxNum - fifo_get_node_num(ptFifoCtrl));	
}

void * fifo_get_node_by_idx(FIFO_CTRL_T *ptFifoCtrl, uint32_t u32Idx)
{
	void * pCurNodeDataAdd = NULL;

	if(ptFifoCtrl->u32ReadAdd == ptFifoCtrl->u32WriteAdd)
		return NULL;
		
	if(u32Idx >= fifo_get_node_num(ptFifoCtrl))
	{
        return NULL;
	}
	
	pCurNodeDataAdd = (void *)(ptFifoCtrl->ptNodeBufAddr
	                     + ptFifoCtrl->u32NodeLen*((ptFifoCtrl->u32ReadAdd+u32Idx)%ptFifoCtrl->u32NodeMaxNum));	                     
	return pCurNodeDataAdd;
}


