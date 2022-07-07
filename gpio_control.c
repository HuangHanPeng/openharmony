#include "iot_gpio.h"
#include "iot_gpio_ex.h"
#include "iot_pwm.h"
#include <stdio.h>
#define LED_GPIO_6 6
#define MOTOR_GPIO 2
#define PWM_PORT 2
#define PWM_FEC 4000
#define GPIO_IDX_7 7
#define GPIO_IDX_8 8
#define IOT_GPIO_KEY 5
//红色LED控制
void red_led_control(int sta){

    IoTGpioSetOutputVal(GPIO_IDX_7,sta? 1:0);

}
//蓝色LED控制
void blue_led_control(int sta){

    IoTGpioSetOutputVal(GPIO_IDX_7,sta? 1:0);

}
//电机板上led控制
void led_control(int sta){

    IoTGpioSetOutputVal(LED_GPIO_6, sta ? 1 : 0);
}

//按键回调函数
static void OnButtonPressed(char *arg){


}
//按键初始化
void key_init(){

      /*按键GPIO初始化*/
    IoTGpioInit(IOT_GPIO_KEY);
    hi_io_set_func(IOT_GPIO_KEY, 0);
    /*按键GPIO初始化为输入*/
    IoTGpioSetDir(IOT_GPIO_KEY, IOT_GPIO_DIR_IN);
    hi_io_set_pull(IOT_GPIO_KEY, 1);
    /*注册按键执行函数*/
    IoTGpioRegisterIsrFunc(IOT_GPIO_KEY, IOT_INT_TYPE_EDGE,
    IOT_GPIO_EDGE_FALL_LEVEL_LOW,
    OnButtonPressed,
    NULL);
}

//主板led初始化
void board_led_init(){
    IoTGpioInit(GPIO_IDX_7);
    IoTGpioSetDir(GPIO_IDX_7,IOT_GPIO_DIR_OUT);
    IoTGpioInit(GPIO_IDX_8);
    IoTGpioSetDir(GPIO_IDX_8,IOT_GPIO_DIR_OUT);

}

//电子板上led初始化
void LED_GPIO_Init(){
     //初始化GPIO
    printf("led init\n");
    IoTGpioInit(LED_GPIO_6);
    IoTGpioSetFunc(LED_GPIO_6,IOT_GPIO_FUNC_GPIO_6_GPIO);
    IoTGpioSetDir(LED_GPIO_6,IOT_GPIO_DIR_OUT);

}

//电机控制
void motor_control(int pwmval){
    
    switch (pwmval)
    {
        case 1:
            /* code */
            IoTPwmStart(PWM_PORT, 16, PWM_FEC);
            break;
        case 2:
            IoTPwmStart(PWM_PORT, 32, PWM_FEC);
            break;
        case 3:
            IoTPwmStart(PWM_PORT, 48, PWM_FEC);
            break;
        case 4:
            IoTPwmStart(PWM_PORT, 64, PWM_FEC);
            break;
        case 5:
            IoTPwmStart(PWM_PORT, 80, PWM_FEC);
        default:
            IoTPwmStop(PWM_PORT);
            break;
    }
    
}
//电机初始化
void Motor_GPIO_Init(){
         //初始化GPIO
    printf("motor init\n");
    IoTGpioInit(MOTOR_GPIO);
    IoTGpioSetFunc(MOTOR_GPIO, IOT_GPIO_FUNC_GPIO_2_PWM2_OUT);
    IoTGpioSetDir(MOTOR_GPIO,IOT_GPIO_DIR_OUT);
    int ret = IoTPwmInit(PWM_PORT);
    if(ret != PWM_PORT){
        printf("failed topwm init!\n");
    }
}

