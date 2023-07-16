/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"
#include "usart.h"
#include "motor.h"
/* USER CODE BEGIN 0 */
#include "printf_on_vofa_float.h"
#include "stdio.h"
/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;


FDCAN_TxHeaderTypeDef fdcan1_TxHeader;
FDCAN_TxHeaderTypeDef fdcan2_TxHeader;
FDCAN_RxHeaderTypeDef fdcan1_RxHeader;
FDCAN_RxHeaderTypeDef fdcan2_RxHeader;


uint8_t fdcan1_msg[8];
uint8_t fdcan2_msg[8];

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

    /* USER CODE BEGIN FDCAN1_Init 0 */

    /* USER CODE END FDCAN1_Init 0 */

    /* USER CODE BEGIN FDCAN1_Init 1 */

    /* USER CODE END FDCAN1_Init 1 */
    hfdcan1.Instance = FDCAN1;
    hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan1.Init.AutoRetransmission = DISABLE;
    hfdcan1.Init.TransmitPause = DISABLE;
    hfdcan1.Init.ProtocolException = DISABLE;
    hfdcan1.Init.NominalPrescaler = 5;
    hfdcan1.Init.NominalSyncJumpWidth = 1;
    hfdcan1.Init.NominalTimeSeg1 = 16;
    hfdcan1.Init.NominalTimeSeg2 = 3;
    hfdcan1.Init.DataPrescaler = 1;
    hfdcan1.Init.DataSyncJumpWidth = 1;
    hfdcan1.Init.DataTimeSeg1 = 1;
    hfdcan1.Init.DataTimeSeg2 = 1;
    hfdcan1.Init.MessageRAMOffset = 0;
    hfdcan1.Init.StdFiltersNbr = 1;
    hfdcan1.Init.ExtFiltersNbr = 0;
    hfdcan1.Init.RxFifo0ElmtsNbr = 8;
    hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan1.Init.RxFifo1ElmtsNbr = 0;
    hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan1.Init.RxBuffersNbr = 0;
    hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
    hfdcan1.Init.TxEventsNbr = 0;
    hfdcan1.Init.TxBuffersNbr = 32;
    hfdcan1.Init.TxFifoQueueElmtsNbr = 8;
    hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
    if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN1_Init 2 */

    /* USER CODE END FDCAN1_Init 2 */

}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

    /* USER CODE BEGIN FDCAN2_Init 0 */

    /* USER CODE END FDCAN2_Init 0 */

    /* USER CODE BEGIN FDCAN2_Init 1 */

    /* USER CODE END FDCAN2_Init 1 */
    hfdcan2.Instance = FDCAN2;
    hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan2.Init.AutoRetransmission = DISABLE;
    hfdcan2.Init.TransmitPause = DISABLE;
    hfdcan2.Init.ProtocolException = DISABLE;
    hfdcan2.Init.NominalPrescaler = 5;
    hfdcan2.Init.NominalSyncJumpWidth = 1;
    hfdcan2.Init.NominalTimeSeg1 = 16;
    hfdcan2.Init.NominalTimeSeg2 = 3;
    hfdcan2.Init.DataPrescaler = 1;
    hfdcan2.Init.DataSyncJumpWidth = 1;
    hfdcan2.Init.DataTimeSeg1 = 1;
    hfdcan2.Init.DataTimeSeg2 = 1;
    hfdcan2.Init.MessageRAMOffset = 0;
    hfdcan2.Init.StdFiltersNbr = 0;
    hfdcan2.Init.ExtFiltersNbr = 0;
    hfdcan2.Init.RxFifo0ElmtsNbr = 8;
    hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan2.Init.RxFifo1ElmtsNbr = 0;
    hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan2.Init.RxBuffersNbr = 0;
    hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
    hfdcan2.Init.TxEventsNbr = 0;
    hfdcan2.Init.TxBuffersNbr = 0;
    hfdcan2.Init.TxFifoQueueElmtsNbr = 8;
    hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
    if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN2_Init 2 */

    /* USER CODE END FDCAN2_Init 2 */

}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED=0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if(fdcanHandle->Instance==FDCAN1)
    {
        /* USER CODE BEGIN FDCAN1_MspInit 0 */

        /* USER CODE END FDCAN1_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        /* FDCAN1 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if(HAL_RCC_FDCAN_CLK_ENABLED==1){
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**FDCAN1 GPIO Configuration
        PA11     ------> FDCAN1_RX
        PA12     ------> FDCAN1_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* FDCAN1 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
        /* USER CODE BEGIN FDCAN1_MspInit 1 */

        /* USER CODE END FDCAN1_MspInit 1 */
    }
    else if(fdcanHandle->Instance==FDCAN2)
    {
        /* USER CODE BEGIN FDCAN2_MspInit 0 */

        /* USER CODE END FDCAN2_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        /* FDCAN2 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if(HAL_RCC_FDCAN_CLK_ENABLED==1){
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN2 GPIO Configuration
        PB12     ------> FDCAN2_RX
        PB13     ------> FDCAN2_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* FDCAN2 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
        /* USER CODE BEGIN FDCAN2_MspInit 1 */

        /* USER CODE END FDCAN2_MspInit 1 */
    }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

    if(fdcanHandle->Instance==FDCAN1)
    {
        /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

        /* USER CODE END FDCAN1_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if(HAL_RCC_FDCAN_CLK_ENABLED==0){
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN1 GPIO Configuration
        PA11     ------> FDCAN1_RX
        PA12     ------> FDCAN1_TX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

        /* FDCAN1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
        /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

        /* USER CODE END FDCAN1_MspDeInit 1 */
    }
    else if(fdcanHandle->Instance==FDCAN2)
    {
        /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

        /* USER CODE END FDCAN2_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if(HAL_RCC_FDCAN_CLK_ENABLED==0){
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN2 GPIO Configuration
        PB12     ------> FDCAN2_RX
        PB13     ------> FDCAN2_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

        /* FDCAN2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
        /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

        /* USER CODE END FDCAN2_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */


/*
 * @param:
 *
 */
void can_init(void) {

    /* USER CODE BEGIN FDCAN1_Init 2 */


    //fdcan1 and fdcan2 filter init//
    FDCAN_FilterTypeDef FDCAN1_RXFilter;

    FDCAN1_RXFilter.IdType=FDCAN_STANDARD_ID;                       //标准ID
    FDCAN1_RXFilter.FilterIndex=0;                                  //滤波器索�?
    FDCAN1_RXFilter.FilterType=FDCAN_FILTER_MASK;                   //滤波器类�?
    FDCAN1_RXFilter.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;           //过滤�?0关联到FIFO0
    FDCAN1_RXFilter.FilterID1=0x0000;                               //32位ID
    FDCAN1_RXFilter.FilterID2=0x0000;                               //如果FDCAN配置为传统模式的话，这里�?32位掩�?
    if(HAL_FDCAN_ConfigFilter(&hfdcan1,&FDCAN1_RXFilter)!=HAL_OK) //滤波器初始化
    {
        Error_Handler();
    }
    HAL_FDCAN_Start(&hfdcan1);                               //�?启FDCAN
    HAL_FDCAN_ActivateNotification(&hfdcan1,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);
    if(HAL_FDCAN_ConfigFilter(&hfdcan2,&FDCAN1_RXFilter)!=HAL_OK) //滤波器初始化
    {
        Error_Handler();
    }
    HAL_FDCAN_Start(&hfdcan2);                               //�?启FDCAN
    HAL_FDCAN_ActivateNotification(&hfdcan2,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);
    /* USER CODE END FDCAN1_Init 2 */






    //fdcan1_txheader init//
    fdcan1_TxHeader.Identifier=0x1ff;
    fdcan1_TxHeader.IdType=FDCAN_STANDARD_ID;
    fdcan1_TxHeader.TxFrameType=FDCAN_DATA_FRAME;
    fdcan1_TxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    fdcan1_TxHeader.BitRateSwitch=FDCAN_BRS_OFF;
    fdcan1_TxHeader.FDFormat=FDCAN_CLASSIC_CAN;
    fdcan1_TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    fdcan1_TxHeader.MessageMarker=0;

    //fdcan2_txheader init//
    fdcan2_TxHeader.Identifier=0x1ff;
    fdcan2_TxHeader.IdType=FDCAN_STANDARD_ID;
    fdcan2_TxHeader.TxFrameType=FDCAN_DATA_FRAME;
    fdcan2_TxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    fdcan2_TxHeader.BitRateSwitch=FDCAN_BRS_OFF;
    fdcan2_TxHeader.FDFormat=FDCAN_CLASSIC_CAN;
    fdcan2_TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    fdcan2_TxHeader.MessageMarker=0;


    //fdcan1 and fdcan2 RxHeader init
    fdcan1_RxHeader.Identifier=0x204;
    fdcan2_RxHeader.DataLength=8;

    fdcan1_RxHeader.IdType=FDCAN_STANDARD_ID;
    fdcan1_RxHeader.RxFrameType=FDCAN_DATA_FRAME;
    fdcan1_RxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    fdcan1_RxHeader.BitRateSwitch=FDCAN_BRS_OFF;
    fdcan1_RxHeader.FDFormat=FDCAN_CLASSIC_CAN;



    fdcan2_RxHeader.Identifier=0x204;
    fdcan2_RxHeader.DataLength=8;

    fdcan2_RxHeader.IdType=FDCAN_STANDARD_ID;
    fdcan2_RxHeader.RxFrameType=FDCAN_DATA_FRAME;
    fdcan2_RxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    fdcan2_RxHeader.BitRateSwitch=FDCAN_BRS_OFF;
    fdcan2_RxHeader.FDFormat=FDCAN_CLASSIC_CAN;


}


uint8_t FDCAN1_Send_Msg(uint8_t* msg,uint32_t len)
{
    fdcan1_TxHeader.DataLength=len;
    if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,&fdcan1_TxHeader,msg)!=HAL_OK) return 0;
    return 1;
}


uint8_t FDCAN2_Send_Msg(uint8_t* msg,uint32_t len)
{


    fdcan2_TxHeader.DataLength=len;
    if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2,&fdcan2_TxHeader,msg)!=HAL_OK) return 0;
    return 1;
}





uint8_t FDCAN1_Rec_Msg(uint8_t* buf,uint32_t len)
{
    fdcan1_RxHeader.DataLength=len;
    if(HAL_FDCAN_GetRxMessage(&hfdcan1,FDCAN_RX_FIFO0,&fdcan1_RxHeader,buf)!=HAL_OK)return 0;//接收数据
    return 1;
}


uint8_t FDCAN2_Rec_Msg(uint8_t* buf,uint32_t len)
{
    if(HAL_FDCAN_GetRxMessage(&hfdcan2,FDCAN_RX_FIFO0,&fdcan2_RxHeader,buf)!=HAL_OK)return 0;//接收数据
    return 1;
}


 uint8_t can_rx_data[8];
motor_state_t motor[8];


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
//    if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE)!=RESET)
//    {
//
//        FDCAN1_Rec_Msg(fdcan1_msg,8);
//        FDCAN2_Rec_Msg(fdcan2_msg,8);
//    }

    if (hfdcan->Instance == FDCAN2||hfdcan->Instance == FDCAN1) {
        FDCAN_RxHeaderTypeDef rx_header;
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header,  can_rx_data);


        switch (rx_header.Identifier) {
            case 0x201:
            case 0x202:
            case 0x203:
            case 0x204:
            case 0x205:
            case 0x206:
            case 0x207:
            case 0x208: {
                static uint8_t i = 0;
                //get motor id
                i = rx_header.Identifier - 0x201;
                get_motor_measure(&motor[i].motor_measure, can_rx_data);
                //printf_fdata2vofa(motor[i].motor_measure.speed_rpm, i,0,0);
                //motor[i].id = rx_header.StdId;
                break;
            }

            default: {
                break;
            }
        }
    }
}



/* USER CODE END 1 */
