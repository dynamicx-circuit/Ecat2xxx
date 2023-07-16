//
// Created by 58286 on 2022/7/19.
//

#ifndef MOTOR_TEST_CORE_INC_MOTOR_H_
#define MOTOR_TEST_CORE_INC_MOTOR_H_

#include "main.h"

#define CAN_ID 0x201
#define RC (1/(2*3.1415926f*10))
#define SAMPLE_FREQ 1000

#define C1 (1/(1+RC*SAMPLE_FREQ))
#define C2 (1-C1)

#define FILTER_BUF_LEN 2
typedef enum {
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,

    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,
    CAN_TRIGGER_MOTOR_ID = 0x207,
    CAN_GIMBAL_ALL_ID = 0x1FF,

} can_msg_id_e;


typedef enum {
    MOTOR_2006,
    MOTOR_6020,
    MOTOR_3508
} motor_type;

#define _3508_MOTORDECELRATION 19.2f
#define _2006_MOTORDECELRATION 36.0f
#define _6020_MOTORDECELRATION 1.0f

typedef struct {
    int16_t speed_rpm;
    int16_t last_speed_rpm;
    int16_t real_current;
    int16_t given_current;
    uint8_t hall;
    uint16_t angle;                //abs angle range:[0,8191]
    uint16_t last_angle;    //abs angle range:[0,8191]
    uint16_t offset_angle;
    int32_t round_cnt;
    int32_t total_angle;
    uint8_t buf_idx;
    uint16_t angle_buf[FILTER_BUF_LEN];
    uint16_t fited_angle;
    uint32_t msg_cnt;
} motor_measure_t;

//电机状态的结构体
typedef struct {
    int motor_type;              //结构体
    uint8_t _flag;            //判断电机是否开启
    uint16_t id;                //电机的id
    float motor_decelration;     //电机的减速比
    float set_speed;           //设置的转子的速度
    motor_measure_t motor_measure;//电机信息的结构体
} motor_state_t;


int16_t get_motor_measure(motor_measure_t *ptr, uint8_t can_data[8]);

void set_motor_current(int16_t current, uint16_t id);


#endif // MOTOR_TEST_CORE_INC_MOTOR_H_
