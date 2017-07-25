#include "PWM-Regulator.h"

/** Usr Include */
/*
#include <hrtim.h>
#include <stm32f3xx_hal.h>
*/

/**
 * @brief  初始化PWM/PID以及结构体变量
 * @note   根据PWM设定CC值启动PWM
 */
void PWM_REGU_Init(PWM_Regulator_t *ptr)
{
  PWM_BASIC_Init(ptr->PWM_BASIC);
  arm_pid_init_f32(ptr->PWM_PID, 1);

  switch (ptr->ID)
  {
  default:
    break;
  }

  ptr->Enable = 1;
}

/**
 * @brief  注销Regulator
 */
void PWM_REGU_DeInit(PWM_Regulator_t *ptr)
{
  PWM_BASIC_DeInit(ptr->PWM_BASIC);
  arm_pid_reset_f32(ptr->PWM_PID);
  ptr->Enable = 0;
}

/**
 * @brief  采样
 */
void PWM_REGU_Sample(PWM_Regulator_t *ptr)
{
  switch (ptr->ID)
  {
  case 0x01:
  {
#if USE_SAMPLE_PT == 0
/*
      (ptr->Input_V) = ....
      (ptr->Input_I) = ....
      (ptr->Output_V) = ....
      (ptr->Output_I) = ....
      */
#else
/*
      *(ptr->Input_V) = ....
      *(ptr->Input_I) = ....
      *(ptr->Output_V) = ....
      *(ptr->Output_I) = ....
      */
#endif
  }
  break;

  case 0x02:
  {
#if USE_SAMPLE_PT == 0
/*
      (ptr->Input_V) = ....
      (ptr->Input_I) = ....
      (ptr->Output_V) = ....
      (ptr->Output_I) = ....
      */
#else
/*
      *(ptr->Input_V) = ....
      *(ptr->Input_I) = ....
      *(ptr->Output_V) = ....
      *(ptr->Output_I) = ....
      */
#endif
  }
  break;
  }
}

/**
 * @brief  运行PID并输出结果到PWM
 */
void PWM_REGU_Update(PWM_Regulator_t *ptr)
{
  float error = ptr->SetValue, output;
  switch (ptr->Mode)
  {
#if USE_SAMPLE_PT == 0
  case PWM_REGULATOR_MODE_INPUT_I:
  {
    error -= (ptr->Input_I);
  }
  break;
  case PWM_REGULATOR_MODE_INPUT_V:
  {
    error -= (ptr->Input_V);
  }
  break;
  case PWM_REGULATOR_MODE_OUTPUT_V:
  {
    error -= (ptr->Output_V);
  }
  break;
  case PWM_REGULATOR_MODE_OUTPUT_I:
  {
    error -= (ptr->Output_I);
  }
  break;
#else
  case PWM_REGULATOR_MODE_INPUT_I:
  {
    error -= *(ptr->Input_I);
  }
  break;
  case PWM_REGULATOR_MODE_INPUT_V:
  {
    error -= *(ptr->Input_V);
  }
  break;
  case PWM_REGULATOR_MODE_OUTPUT_V:
  {
    error -= *(ptr->Output_V);
  }
  break;
  case PWM_REGULATOR_MODE_OUTPUT_I:
  {
    error -= *(ptr->Output_I);
  }
  break;
#endif
  }

  output = arm_pid_f32(ptr->PWM_PID, error);
  /* 再和拟合函数或者类似方法得到值相加，以提高PID性能
   * etc. output += ptr->PWM_BASIC->CC; 加上过去的值
   */

  /* PID 错误处理 */
  if (output > ptr->PWM_BASIC->CC_Max || output < ptr->PWM_BASIC->CC_Min)
  {
    arm_pid_reset_f32(ptr->PWM_PID);
    output = output < ptr->PWM_BASIC->CC_Min ? ptr->PWM_BASIC->CC_Min : ptr->PWM_BASIC->CC_Max;
  }

  PWM_BASIC_SetCC(ptr->PWM_BASIC, (uint32_t)output);
}

/**
 * @brief  设定输出结果稳定值
 */
void PWM_REGU_SetValue(PWM_Regulator_t *ptr, float setvalue)
{
  // 判断数值合法性
  if (setvalue < 0)
    return;

  ptr->SetValue = setvalue;
}

/**
 * @brief  设定输出稳定模式
 */
void PWM_REGU_SetMode(PWM_Regulator_t *ptr, PWM_Regulator_Mode_t mode)
{
  ptr->Mode = mode;
}
