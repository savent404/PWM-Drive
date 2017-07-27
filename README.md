# PWM-Drive

# How to use

## PWM Basic
define a PWM basic structure
``` C
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
