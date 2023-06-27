#ifndef _FIFO_H_
#define _FIFO_H_


/********************************************************************** 
头文件引用声明
***********************************************************************/

#include "stdint.h"
#include "string.h"

//#include "Jlog.H"
/********************************************************************** 
宏定义
***********************************************************************/

									
#ifndef TRUE
#define TRUE							1
#endif
									
#ifndef FALSE
#define FALSE 							0
#endif


#ifndef SUCC
#define SUCC							0
#endif

#ifndef FAIL
#define FAIL							(-1)
#endif

#define LM_ASSERT(express)			do	\
									{	\
										if(!(express))	\
										{				\
											;	\
										}	\
									}while(0)


#define FIFO_INVAID_ID 					((uint32_t)(-1))
#define FIFO_NODE_MIN 					(3)

/********************************************************************** 
结构、枚举、公用体等结构定义
***********************************************************************/
typedef volatile struct
{
	uint32_t u32NodeMaxNum;					/* 最大节点数 */	
	uint32_t u32NodeLen;					/* 节点单元所占字节数 */	
	uint32_t u32ReadAdd;					/* 指向第一个有效的节点地址 READ*/	
	uint32_t u32WriteAdd;					/* 指向第一个空闲的地址 WRITE*/
	uint8_t *ptNodeBufAddr;					/* FIFO缓冲池地址 */	
}FIFO_CTRL_T;

/********************************************************************** 
源文件定义变量声明

extern 外部变量声明
***********************************************************************/


/********************************************************************** 
源文件函数声明

extern 外部函数声明
***********************************************************************/


/********************************************************************** 
*  函数名称: fifo_init
*  功能描述: 定义并初始化一个环形队列
*  参数说明:
*  输    入: ptFifoCtrl:环形队列的控制参数结构体；
*			 u32NodeMaxNum:环形队列节点个数；
*			 u32NodeLen:每个节点长度；
*			 pNodeArray:环形队列地址；
*  输    出: 无
*  返 回 值: FAIL: 失败;  SUCC: 成功  
***********************************************************************/
int8_t fifo_init(FIFO_CTRL_T *ptFifoCtrl,uint32_t u32NodeMaxNum,
									uint32_t u32NodeLen,void *pNodeArray);

/********************************************************************** 
*  函数名称: fifo_is_empty
*  功能描述: 检查是否为空
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int8_t fifo_is_empty(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_is_full
*  功能描述: 检查是否为满
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int8_t fifo_is_full(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_get_node_num
*  功能描述: 获取节点个数
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
uint32_t fifo_get_node_num(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_add_node_polite
*  功能描述: 礼貌方式添加一个节点，若满则返回FAIL;
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: FAIL:缓冲池已满；SUCC:添加成功
***********************************************************************/
int8_t fifo_add_node_polite(FIFO_CTRL_T *ptFifoCtrl,void *pNodeData);

/********************************************************************** 
*  函数名称: fifo_add_node_impolite
*  功能描述: 非礼貌方式添加一个节点，即若满则删除一个头节点，并加到尾节点；
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: SUCC:添加成功
***********************************************************************/
int8_t fifo_add_node_impolite(FIFO_CTRL_T *ptFifoCtrl,void *pNodeData);

/********************************************************************** 
*  函数名称: fifo_get_node
*  功能描述: 获取一个头节点地址；
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 为空则返回NULL,否则返回节点地址；
***********************************************************************/
void * fifo_get_node(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_delete_node
*  功能描述: 删除一个头节点；
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int8_t fifo_delete_node(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_clear
*  功能描述: 清空fifo；
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int8_t fifo_clear(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_delete_latest_node
*  功能描述: 删除一个尾节点
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int8_t fifo_delete_latest_node(FIFO_CTRL_T *ptFifoCtrl);

/********************************************************************** 
*  函数名称: fifo_get_remain_empty_node_num
*  功能描述: 获取剩余空间节点数
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/
int32_t fifo_get_remain_empty_node_num(FIFO_CTRL_T *ptFifoCtrl);


/********************************************************************** 
*  函数名称: fifo_get_node_by_idx
*  功能描述: 获取指定节点
*  参数说明: 
*  输    入: 
*  输    出: 
*  返 回 值: 
***********************************************************************/

void * fifo_get_node_by_idx(FIFO_CTRL_T *ptFifoCtrl, uint32_t u32Idx);

#endif

