#pragma once

// place to include GPIO hw header
#include <stm32f4xx.h>

//#define GPIO_USE_CPP_STYLE // uncomment this string for using c++ style

#define GPIO_PORT_TYPE GPIO_TypeDef
#define GPIO_PIN_TYPE  uint16_t

#define GPIO_READ(pGPIO) (HAL_GPIO_ReadPin((pGPIO)->port, (pGPIO)->pin) == GPIO_PIN_SET)
#define GPIO_WRITE(pGPIO, state) HAL_GPIO_WritePin((pGPIO)->port, (pGPIO)->pin, ((state) ? GPIO_PIN_SET : GPIO_PIN_RESET))
