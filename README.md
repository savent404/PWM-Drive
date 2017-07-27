# PWM-Drive

# How to use

## PWM Basic
define a PWM basic structure
``` C
#include "PWM-Basic.h"

PWM_Basic_t PWM = {
  .CC_Min = 0x60,
  .CC_Max = 0xA000,
  .ReloadValue = 0xA000,
  .PWM_ID = 1,
  .Frequence = 100e3
};
```
complete function in PWM-Basic.c
``` C
void PWM_BASIC_Init(PWM_Basic_t *ptr)
{
  ...
  switch (ptr->PWM_ID)
  {
  case 0x01: {
    //TODO:Init and Enable PWM
  } break;
  }
  ...
}

void PWM_BASIC_DeInit(PWM_Basic_t *ptr)
{
  ...
  switch (ptr->PWM_ID)
  {
  case 0x01: {
    //TODO:Deinit PWM
  } break;
  }
  ...
}

void PWM_BASIC_SetCC(PWM_Basic_t *ptr)
{
  ...
  switch (ptr->PWM_ID)
  {
  case 0x01: {
    //TODO:Set CC
  } break;
  }
  ...
}

```
then you can use it for fun!

## PWM Regulator
structure define:
``` C
#include "PWM-Regulator.h"

PWM_Basic_t PWM = {
  .CC_Min = 0x60,
  .CC_Max = 0xA000,
  .ReloadValue = 0xA000,
  .PWM_ID = 1,
  .Frequence = 100e3
};

PWM_PID_t PID = {
  .Kp = 1.0,
  .Ki = 0.2,
  .Kd = 0.0
};

PWM_Regulator_t Regulator;
```
complete some code for your PWM opra code
``` C
void PWM_REGU_Init(PWM_Regulator_t *ptr)
{
  ...
  switch(ptr->ID)
  {
    case 0x01: {
      //TODO:Another code like Init ADC sample
    } break;
  }
}
void PWM_REGU_Sample(PWM_Regulator_t *ptr)
{
  switch (ptr->ID)
  {
    case 0x01 : {
      // ADC Sample
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
    } break;
  }
}

void PWM_REGU_Update(PWM_Regulator_t *ptr)
{
  ...
  output = arm_pid_f32(ptr->PWM_PID, error);
  /* 再和拟合函数或者类似方法得到值相加，以提高PID性能
   * etc. output += ptr->PWM_BASIC->CC; 加上过去的值
   */
  ...
}
```
then you can use it:
``` C
Regulator.PWM_BASIC = &PWM;
Regulator.PWM_PID = &PID;
PWM_REGU_SetMode(&Regulator, PWM_REGULATOR_MODE_OUTPUT_V); // 稳定输出电压
PWM_REGU_SetValue(&Regulator, 10); // 设定输出电压为10V
PWM_REGU_Init(&Regulator);  // 初始化

while (1)
{
  PWM_REGU_Sample(&Regulator);  // 电压采样
  PWM_REGU_Update(&Regulator);  // PID控制PWM输出

  Delay(time); // 控制间隔时间不同 PID参数也会发生变化
}
```