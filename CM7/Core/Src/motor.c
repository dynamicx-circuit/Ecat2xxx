//
// Created by 58286 on 2022/7/19.
//
#include "motor.h"
#include "usart.h"


static FDCAN_TxHeaderTypeDef hfcan_tx_header;
static uint8_t can_tx_data[8];
extern FDCAN_HandleTypeDef hfdcan1;


int16_t get_motor_measure(motor_measure_t *ptr, uint8_t can_data[8]) {
    ptr->last_angle = ptr->angle;
    ptr->angle = (uint16_t) (can_data[0] << 8 | can_data[1]);
    ptr->real_current = (int16_t) (can_data[2] << 8 | can_data[3]);
    ptr->speed_rpm = C1 * ptr->real_current + C2 * ptr->last_speed_rpm;    //这里是因为两种电调对应位不一样的信息
    ptr->last_speed_rpm = ptr->speed_rpm;
    ptr->given_current = (int16_t) (can_data[4] << 8 | can_data[5]) / -5;
    ptr->hall = can_data[6];
    if (ptr->angle - ptr->last_angle > 4096)
        ptr->round_cnt--;
    else if (ptr->angle - ptr->last_angle < -4096)
        ptr->round_cnt++;
    ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;

    return ptr->speed_rpm;
}

/**
 * 将电流传输给指定id的电机
 * @param current 电机的转速
 * @param id 电机的id
 */
void set_motor_current(int16_t current, uint16_t id) {
    hfcan_tx_header.IdType = FDCAN_STANDARD_ID;      //当该位为0时，为标准帧；当该位为1时，为拓展帧
    hfcan_tx_header.IdType=FDCAN_STANDARD_ID;
    hfcan_tx_header.TxFrameType=FDCAN_DATA_FRAME;
    hfcan_tx_header.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    hfcan_tx_header.BitRateSwitch=FDCAN_BRS_OFF;
    hfcan_tx_header.FDFormat=FDCAN_CLASSIC_CAN;
    hfcan_tx_header.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    hfcan_tx_header.MessageMarker=0;
    hfcan_tx_header.DataLength = 8;               //数据位
    hfcan_tx_header.Identifier=0x1ff;
    if (id >= 9 && id <= 12) {
        hfcan_tx_header.Identifier = 0x2FF;         //ID
        id -= 8;
    }
    if (id >= 5 && id <= 8) {
        hfcan_tx_header.Identifier = 0x1FF;         //ID
        id -= 4;

    } else if (id >= 1 && id <= 4) {
        hfcan_tx_header.Identifier = 0x200;         //ID
    }

    can_tx_data[0] = current >> 8;
    can_tx_data[1] = current & 0xFF;
    can_tx_data[2] = 0;
    can_tx_data[3] = 0;
    can_tx_data[4] = 0;
    can_tx_data[5] = 0;
    can_tx_data[6] = 0;
    can_tx_data[7] = 0;

    uint32_t tx_mailbox;
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,&hfcan_tx_header,can_tx_data);

}
