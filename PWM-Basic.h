#ifndef PWM_BASIC_H_
#define PWM_BASIC_H_

#include <stdint.h>

typedef struct _pwm_basic_structure
{

  // 是否在运行的标志，用于PWM_BASIC_SetDC函数
  uint8_t Enable;

  // PWM输出频率
  uint32_t Frequence;

  // PWM预装载值
  uint32_t ReloadValue;

  // 标识该PWM结构体
  uint32_t PWM_ID;

  uint32_t CC_Max;
  uint32_t CC_Min;

  // 当前占空比
  float DutyCycle;

  // 比较值
  uint32_t CC;
} PWM_Basic_t;

/**
 * @brief  初始化PWM
 * @note   需要按照PWM_Basic结构体中的信息开启PWM输出， 占空比应与DutyCycle值相符
 */
extern void PWM_BASIC_Init(PWM_Basic_t *ptr);

/**
 * @brief  注销驱动
 */
extern void PWM_BASIC_DeInit(PWM_Basic_t *ptr);

/**
 * @brief  重设PWM占空比大小
 * @note   更改PWM占空比时应同时修改结构体中的值
 */
extern void PWM_BASIC_SetDC(PWM_Basic_t *ptr, float dutycycle);

/**
 * @brief  重设PWM占空比大小
 * @note   更改PWM占空比时应同时修改结构体中的值
 */
extern void PWM_BASIC_SetCC(PWM_Basic_t *ptr, uint32_t CC);

#endif
