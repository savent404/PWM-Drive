#ifndef _PWM_REGULATOR_H_
#define _PWM_REGULATOR_H_

#include <PWM-Basic.h>
#include <PWM-PID.h>

#ifndef USE_SAMPLE_PT
#define USE_SAMPLE_PT 0
#endif

typedef enum _pwm_regulator_mode {
  PWM_REGULATOR_MODE_INPUT_I,
  PWM_REGULATOR_MODE_INPUT_V,
  PWM_REGULATOR_MODE_OUTPUT_I,
  PWM_REGULATOR_MODE_OUTPUT_V
} PWM_Regulator_Mode_t;

typedef struct _pwm_regulator_structure
{
  PWM_Basic_t *PWM_BASIC;
  PWM_PID_t *PWM_PID;

#if USE_SAMPLE_PT == 0
  float Input_V;
  float Input_I;
  float Output_V;
  float Output_I;
#else
  float *Input_V;
  float *Input_I;
  float *Output_V;
  float *Output_I;
#endif
  float SetValue;

  PWM_Regulator_Mode_t Mode;

  uint32_t ID;

  uint32_t Enable;

} PWM_Regulator_t;

/**
 * @brief  初始化PWM/PID以及结构体变量
 * @note   根据PWM设定CC值启动PWM
 */
void PWM_REGU_Init(PWM_Regulator_t *ptr);

/**
 * @brief  注销Regulator
 */
void PWM_REGU_DeInit(PWM_Regulator_t *ptr);

/**
 * @brief  采样
 */
void PWM_REGU_Sample(PWM_Regulator_t *ptr);

/**
 * @brief  运行PID并输出结果到PWM
 */
void PWM_REGU_Update(PWM_Regulator_t *ptr);

/**
 * @brief  设定输出结果稳定值
 */
void PWM_REGU_SetValue(PWM_Regulator_t *ptr, float setvalue);

/**
 * @brief  设定输出稳定模式
 */
void PWM_REGU_SetMode(PWM_Regulator_t *prt, PWM_Regulator_Mode_t mode);

#endif
