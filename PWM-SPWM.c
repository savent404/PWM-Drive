#include "PWM-SPWM.h"

/** Usr Include */
/*
#include <stm32f3xx_hal.h>
*/

void SPWM_Init(SPWM_t *ptr)
{
  PWM_BASIC_Init(ptr->PWM_BASIC1);
  if (ptr->Mode == SPWM_BRIGE_Full)
  {
    PWM_BASIC_Init(ptr->PWM_BASIC2);
  }
  ptr->step_now = 0;
  ptr->Enable = 1;
}

void SPWM_DeInit(SPWM_t *ptr)
{
  PWM_BASIC_DeInit(ptr->PWM_BASIC1);
  if (ptr->Mode == SPWM_BRIGE_Full)
  {
    PWM_BASIC_DeInit(ptr->PWM_BASIC2);
  }
  ptr->step_now = 0;
  ptr->Enable = 0;
}

void SPWM_Step(SPWM_t *ptr)
{
  float step = ptr->step_now;
  float STEP = ptr->Step_Frequence / ptr->Target_Frequence;
  float rad = ptr->Phase + step * 2 * PI, buf = 0;

  buf = sin(rad);
  buf *= ptr->Range;

  if (ptr->Mode == SPWM_MODE_Bipolar)
  {
    PWM_BASIC_SetDC(ptr->PWM_BASIC1, (buf + 0.5) / 2);
  }
  else
  {
    // PWM1 output and PWM2 NOT
    if (buf > 0)
    {
      PWM_BASIC_SetDC(ptr->PWM_BASIC1, buf);
      PWM_BASIC_SetDC(ptr->PWM_BASIC2, 0);
    }
    else
    {
      PWM_BASIC_SetDC(ptr->PWM_BASIC1, 0);
      PWM_BAISC_SetDC(ptr->PWM_BASIC2, -buf);
    }
  }

  ptr->step_now += 1.0f / STEP;
  if (ptr->step_now >= 1.00f)
    ptr->step_now = 0.0f;
}
