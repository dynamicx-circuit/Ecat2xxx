//
// Created by 86136 on 2022/10/15.
//

#include "key.h"
#include "stm32h7xx.h"

unsigned char Enter_Key() {
    unsigned char flag = 0;
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET);
        HAL_Delay(10);

        flag = 1;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET);
        HAL_Delay(10);
        flag = 2;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET);
        HAL_Delay(10);
        flag = 3;
    }
    return flag;
}

void press_key(press_key_t *press_key, uint8_t max_select_num) {

    uint8_t key_flag = Enter_Key();
    if (key_flag == 1) {
        press_key->key_verify = 1;
    } else if (key_flag == 2) {
        press_key->key_select_num = (press_key->key_select_num + 1) % max_select_num;
    }
}