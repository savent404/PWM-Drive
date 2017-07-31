#ifndef _PWM_SPWM_H_
#define _PWM_SPWM_H_

#include "PWM-Basic.h"
#include <math.h>

#ifndef PI
#define PI 3.1415926535897932384626433832795f
#endif

typedef struct _spwm_structure
{
  PWM_Basic_t *PWM_BASIC1;
  PWM_Basic_t *PWM_BASIC2;

  float Target_Frequence;
  float Step_Frequence;
  float Phase; // ±PI
  float Range; // DutyCycle 0.0~1.0

  double step_now; //0.0~1.0

  enum
  {
    SPWM_MODE_Unipolar, //单极性
    SPWM_MODE_Bipolar,  //双极性
  } Mode;

  enum
  {
    SPWM_BRIGE_Half, //半桥
    SPWM_BRIGE_Full, //全桥
  } Brige;

  uint32_t ID;
  uint32_t Enable;
} SPWM_t;

void SPWM_Init(SPWM_t *ptr);
void SPWM_DeInit(SPWM_t *ptr);
void SPWM_Step(SPWM_t *ptr);

#endif
