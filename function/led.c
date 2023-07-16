#include "led.h"
#include "gpio.h"
#include "usart.h"


#define LED1_Port GPIOE
#define LED2_port GPIOE

#define LED1_Pin GPIO_PIN_7
#define LED2_pin GPIO_PIN_8

/**
 *
 * @param count 该参数为计数值，当该值达到阈值时，会翻转LED对应的GPIO的电平。
 */
void led_can_rx(unsigned short *count) {

    if (*count > 200) {
        HAL_GPIO_TogglePin(LED1_Port, LED1_Pin);
        *count = 0;
    }
}

/**
 *
 * @param count 该参数为计数值，当该值达到阈值时，会翻转LED对应的GPIO的电平。
 */
void led_can_tx(unsigned short *count) {
    if (*count > 200) {
        HAL_GPIO_TogglePin(LED2_port, LED2_pin);
        *count = 0;
    }
}