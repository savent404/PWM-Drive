#include "PWM-Basic.h"

/** Usr Include */
/*
#include "hrtim.h"
#include "stm32f3xx_hal.h"
*/

void PWM_BASIC_Init(PWM_Basic_t *ptr)
{
  // Update DutyCycle Value
  ptr->DutyCycle = (float)ptr->CC / (float)ptr->ReloadValue;
  switch (ptr->PWM_ID)
  {
  case 0x01:
  {
    // TODO:Enable PWM
    /*
      __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, ptr->CC);
      HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
      HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
      */
    ptr->Enable = 1;
  }
  break;

  case 0x02:
  {
    // TODO:Enable PWM
    /*
      __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2, ptr->CC);
      HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA2);
      HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
      */
    ptr->Enable = 1;
  }
  break;

  default:
  {
    ptr->Enable = 0;
    ptr->Frequence = 0;
    ptr->ReloadValue = 0;
    ptr->DutyCycle = 0;
  }
  break;
  }
}

void PWM_BASIC_DeInit(PWM_Basic_t *ptr)
{
  switch (ptr->PWM_ID)
  {
  case 0x01:
  {
    // TODO:DeInit PWM
    /*
      HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1);
      */
    ptr->Enable = 0;
  }
  break;

  case 0x02:
  {
    // TODO:DeInit PWM
    /*
      HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA2);
      */
    ptr->Enable = 0;
  }
  break;
  }
}

void PWM_BASIC_SetDC(PWM_Basic_t *ptr, float dutycycle)
{
  if (dutycycle <= 1.0f && dutycycle >= 0.0f)
  {
    ptr->DutyCycle = dutycycle;
    ptr->CC = (uint32_t)(dutycycle * ptr->ReloadValue);
    PWM_BASIC_SetCC(ptr, ptr->CC);
  }
}

void PWM_BASIC_SetCC(PWM_Basic_t *ptr, uint32_t CC)
{
  if (CC > ptr->CC_Max && (ptr->CC_Max > 0))
    CC = ptr->CC_Max;
  else if (CC > ptr->ReloadValue)
    CC = ptr->ReloadValue;

  if (CC < ptr->CC_Min)
    CC = ptr->CC_Min;

  ptr->DutyCycle = (float)CC / (float)ptr->ReloadValue;
  ptr->CC = CC;
  switch (ptr->PWM_ID)
  {
  case 0x01:
  {
    // TODO:Set CC
    /*
    __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, ptr->CC);
    */
  }
  break;

  case 0x02:
  {
    // TODO:Set CC
    /*
    __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2, ptr->CC);
    */
  }
  break;
  }
}
