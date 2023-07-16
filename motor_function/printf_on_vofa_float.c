//
// Created by 86136 on 2023/7/8.
//

#include "printf_on_vofa_float.h"
#include "usart.h"

#define FLOATDATA_SIZES 4
struct fdata {
    float fdata[FLOATDATA_SIZES];
    unsigned char tail[4];
};

struct fdata data2vofa = {0.0f, 0.0f, 0.0f, 0.0f, 0x00, 0x00, 0x80, 0x7f};

void printf_fdata2vofa(float data1, float data2, float data3, float data4) {
    data2vofa.fdata[0] = data1;
    data2vofa.fdata[1] = data2;
    data2vofa.fdata[2] = data3;
    data2vofa.fdata[3] = data4;


    HAL_UART_Transmit(&huart2, (uint8_t *) &data2vofa.fdata, sizeof(float) * 4, HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart2, data2vofa.tail, 4, HAL_MAX_DELAY);

}