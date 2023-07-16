//
// Created by 86136 on 2023/7/7.
//

#ifndef DEBUGGER_CODE_F407_MOTOR_CONTROL_INIT_H
#define DEBUGGER_CODE_F407_MOTOR_CONTROL_INIT_H

#include "main.h"
#include "pid.h"
#include "motor.h"
#include "printf_on_vofa_float.h"

void motor_pid_init(pid_t_ *pid_struct, uint16_t id, uint8_t motor_type);

void set_pid_param(pid_t_ *pid_struct, float kp, float ki, float kd);

void motor_normal_speed(pid_t_ *pid_struct, uint8_t id, float speed);

void motor_sin_speed(pid_t_ *pid_struct, uint8_t id, float speed, uint32_t times);

#endif //DEBUGGER_CODE_F407_MOTOR_CONTROL_INIT_H
