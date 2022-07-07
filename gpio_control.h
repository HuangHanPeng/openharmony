#ifndef __GPIO_CONTROL_H__
#define __GPIO_CONTROL_H__

void LED_GPIO_Init();
void led_control(int sta);
void motor_control(int pwmval);
void Motor_GPIO_Init();
void board_led_init();
void key_init();
void blue_led_control(int sta);
void red_led_control(int sta);
#endif /* __WIFI_CONNECT_H__ */