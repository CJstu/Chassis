/**
  ******************************************************************************
  * @file           : BSP_Can.h
  * @author         : z1415
  * @brief          : None
  * @attention      : None
  * @date           : 2023-11-23
  ******************************************************************************
  */



#ifndef CPROJECT_BSP_CAN_H
#define CPROJECT_BSP_CAN_H

#include "main.h"
#include "can.h"



uint8_t Can_TxMessage(uint8_t ide,uint32_t id,uint8_t len,uint8_t *data);


#endif //CPROJECT_BSP_CAN_H
