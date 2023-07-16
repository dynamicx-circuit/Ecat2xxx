//
// Created by 86136 on 2023/7/7.
//

#include "motor_control.h"
#include "math.h"

extern motor_state_t motor[8];


void set_pid_param(pid_t_ *pid_struct, float kp, float ki, float kd) {
    pid_struct->p = kp;
    pid_struct->i = ki;
    pid_struct->d = kd;
}


void motor_pid_init(pid_t_ *pid_struct, uint16_t id, uint8_t motor_type) {
    motor[id - 1].motor_type = motor_type;
    if (motor_type == MOTOR_3508) { motor[id - 1].motor_decelration = _3508_MOTORDECELRATION; }
    else if (motor_type == MOTOR_2006) { motor[id - 1].motor_decelration == _2006_MOTORDECELRATION; }
    else if (motor_type == MOTOR_6020) { motor[id - 1].motor_decelration == _6020_MOTORDECELRATION; }
    PID_struct_init(pid_struct, POSITION_PID, 20000, 20000, 5.0f, 0.0f, 0.0f);
}

/**
 *
 * @param pid_struct
 * @param id
 * @param speed speed为电机轴的转速，而电机的反馈数据为电机转子的转速，在此需要对不同的电机的轴的转速进行一下简单的换算。
 *          3508减速比为 1:19
 *          2006减速比为 1:36
 *          6020减速比为 1:1
 */
void motor_normal_speed(pid_t_ *pid_struct, uint8_t id, float speed) {

    //计算转子的转速
    float rotor_speed = speed * (float) motor[id - 1].motor_decelration;
    //pid计算并发送数据
    pid_calc(pid_struct, (float) motor[id - 1].motor_measure.speed_rpm, rotor_speed);
    set_motor_current((int16_t) pid_struct->pos_out, id);

    //将数据打印到vofa
    printf_fdata2vofa(motor[id - 1].motor_measure.speed_rpm, speed, pid_struct->pos_out, 0);

}

//正弦函数的参数
const double a = 0.780;
double w = 1.90;
double b = 2.090f - a;

/**
 *
 * @param pid_struct
 * @param id
 * @param speed
 * @param times 时间单位为ms
 */
void motor_sin_speed(pid_t_ *pid_struct, uint8_t id, float speed, uint32_t times) {
    float rotor_speed = 90.0f * a * (sin(w * 0.001 * times) + 1.2 * b) * motor[id - 1].motor_decelration / 3.1415926;

    pid_calc(pid_struct, (float) motor[id - 1].motor_measure.speed_rpm, rotor_speed);
    set_motor_current((int16_t) pid_struct->pos_out, id);

    //将数据打印到vofa
    printf_fdata2vofa(motor[id - 1].motor_measure.speed_rpm, rotor_speed, pid_struct->pos_out, 0);
}