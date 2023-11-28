/**
  ******************************************************************************
  * @file           : BSP_Can.c
  * @author         : z1415
  * @brief          : None
  * @attention      : None
  * @date           : 2023-11-23
  ******************************************************************************
  */
#include "BSP_Can.h"

/***********************************************
函数功能：can发送数据
入口参数：
			ide：	0：标准帧
					1：扩展帧
			id：	帧ID
			len：	数据长度
			data：	数据
返回值：0：成功。1：失败
************************************************/
uint8_t Can_TxMessage(uint8_t ide,uint32_t id,uint8_t len,uint8_t *data)
{
    uint32_t   TxMailbox;
    CAN_TxHeaderTypeDef CAN_TxHeader;
    HAL_StatusTypeDef   HAL_RetVal;
    uint16_t i=0;
    if(ide == 0)
    {
        CAN_TxHeader.IDE = CAN_ID_STD;	//标准帧
        CAN_TxHeader.StdId = id;
    }
    else
    {
        CAN_TxHeader.IDE = CAN_ID_EXT;			//扩展帧
        CAN_TxHeader.ExtId = id;
    }
    CAN_TxHeader.DLC = len;
    CAN_TxHeader.RTR = CAN_RTR_DATA;//数据帧,CAN_RTR_REMOTE遥控帧
    CAN_TxHeader.TransmitGlobalTime = DISABLE;
    while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
    {
        i++;
        if(i>0xfffe)
            return 1;
    }
    HAL_Delay(500);
    HAL_RetVal = HAL_CAN_AddTxMessage(&hcan,&CAN_TxHeader,data,&TxMailbox);
    if(HAL_RetVal != HAL_OK)
        return 1;
    return 0;
}


/*******************************************
函数功能：接受中断回调函数
返回值：无
********************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef CAN_RxHeader;
    HAL_StatusTypeDef HAL_Retval;
    uint8_t Rx_Data[8];
    uint8_t Data_Len=0;
    uint32_t ID=0;
    uint8_t i;
    HAL_Retval = HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,Rx_Data);
    if(HAL_Retval == HAL_OK)
    {
        Data_Len = CAN_RxHeader.DLC;
        if(CAN_RxHeader.IDE)
            ID = CAN_RxHeader.ExtId;
        else
            ID = CAN_RxHeader.StdId;
//        Printf(USART1,"id:%x\r\n",ID);
//        Printf(USART1,"Data_Len:%d\r\n",Data_Len);
//        for(i=0;i<8;i++)
//            Printf(USART1,"Rx_Data[%d]=%x\r\n",i,Rx_Data[i]);
    }
}