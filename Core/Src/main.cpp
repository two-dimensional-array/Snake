/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <hd44780u.h>
#include <button_driver.h>
#include <gpio.hpp>
#include <stdio.h>
#include <string.h>
#include <snake.hpp>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct SButtonEvent
{
  size_t idx;
  bool state;
};

typedef struct SButtonEvent button_evn_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define GET_ARR_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Definitions for refreshSnakeTas */
osThreadId_t refreshSnakeTasHandle;
const osThreadAttr_t refreshSnakeTas_attributes = {
  .name = "refreshSnakeTas",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for buttonTask */
osThreadId_t buttonTaskHandle;
const osThreadAttr_t buttonTask_attributes = {
  .name = "buttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buttonQueue */
osMessageQueueId_t buttonQueueHandle;
const osMessageQueueAttr_t buttonQueue_attributes = {
  .name = "buttonQueue"
};
/* Definitions for buttonTimer */
osTimerId_t buttonTimerHandle;
const osTimerAttr_t buttonTimer_attributes = {
  .name = "buttonTimer"
};
/* Definitions for displayMutex */
osMutexId_t displayMutexHandle;
const osMutexAttr_t displayMutex_attributes = {
  .name = "displayMutex"
};
/* USER CODE BEGIN PV */

const gpio_t kDisplayData[] =
{
  {DISP_DB4_GPIO_Port, DISP_DB4_Pin},
  {DISP_DB5_GPIO_Port, DISP_DB5_Pin},
  {DISP_DB6_GPIO_Port, DISP_DB6_Pin},
  {DISP_DB7_GPIO_Port, DISP_DB7_Pin}
};

hd44780u_t gDisplay =
{
  en : {DISP_EN_GPIO_Port, DISP_EN_Pin},
  rw : {DISP_RW_GPIO_Port, DISP_RW_Pin},
  rs : {DISP_RS_GPIO_Port, DISP_RS_Pin},
  dataPins : ((gpio_t* const)kDisplayData)
};

const gpio_t kButtonsGPIO[] =
{
  {SW1_GPIO_Port, SW1_Pin},
  {SW3_GPIO_Port, SW3_Pin},
  {SW4_GPIO_Port, SW4_Pin},
  {SW5_GPIO_Port, SW5_Pin},
  {SW2_GPIO_Port, SW2_Pin}
};

button_hanler_t gButtonHandlers[GET_ARR_COUNT(kButtonsGPIO)];
EMoveDirection gCurrDirection;
uint32_t gRenderTimeTick;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void RefreshSnakeTask(void *argument);
void ButtonTask(void *argument);
void ButtonTimer(void *argument);

/* USER CODE BEGIN PFP */
void DrawScreen();
void SnakeMoveController(size_t idx);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static_assert(GET_ARR_COUNT(kButtonsGPIO) == GET_ARR_COUNT(gButtonHandlers), "Invalid buttons configuration!!!");
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of displayMutex */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of buttonTimer */
  buttonTimerHandle = osTimerNew(ButtonTimer, osTimerPeriodic, NULL, &buttonTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of buttonQueue */
  buttonQueueHandle = osMessageQueueNew (8, sizeof(button_evn_t), &buttonQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of refreshSnakeTas */
  refreshSnakeTasHandle = osThreadNew(RefreshSnakeTask, NULL, &refreshSnakeTas_attributes);

  /* creation of buttonTask */
  buttonTaskHandle = osThreadNew(ButtonTask, NULL, &buttonTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DISP_RS_Pin|DISP_RW_Pin|DISP_EN_Pin|DISP_DB4_Pin
                          |DISP_DB5_Pin|DISP_DB6_Pin|DISP_DB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DISP_RS_Pin DISP_RW_Pin DISP_EN_Pin DISP_DB4_Pin
                           DISP_DB5_Pin DISP_DB6_Pin DISP_DB7_Pin */
  GPIO_InitStruct.Pin = DISP_RS_Pin|DISP_RW_Pin|DISP_EN_Pin|DISP_DB4_Pin
                          |DISP_DB5_Pin|DISP_DB6_Pin|DISP_DB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SW4_Pin SW5_Pin SW3_Pin SW1_Pin */
  GPIO_InitStruct.Pin = SW4_Pin|SW5_Pin|SW3_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SW2_Pin */
  GPIO_InitStruct.Pin = SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SW2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HD44780UDelayUS(volatile uint32_t micros)
{
  if (micros % 1000)
  {
    micros /= 1000;
    ++micros;
  }
  else
  {
    micros /= 1000;
  }

  osDelay(micros);
}

void ButtonEventHanler(size_t idx, bool state)
{
  button_evn_t event{idx, state};
  osMessageQueuePut(buttonQueueHandle, &event, 0, 0);
}

void DrawScreen()
{
  char field[kMaxSnakeSize + 1];
  memset(field, ' ', kMaxSnakeSize);
  field[kMaxSnakeSize] = '\0';

  if (SnakeMove(gCurrDirection))
  {
    SnakeGenerateAple(osKernelGetSysTimerCount());
  }

  DrawSnake([&field](SPoint& point) -> void
  {
    field[(point.y * (kMaxPoint.x + 1)) + point.x] = 'O';
  });

  field[(gAple.y * (kMaxPoint.x + 1)) + gAple.x] = '+';

  if (osMutexAcquire(displayMutexHandle, osWaitForever) == osOK)
  {
    HD44780UWriteString(&gDisplay, field);
    osMutexRelease(displayMutexHandle);
    gRenderTimeTick = osKernelGetTickCount() + 1000;
  }
}

void SnakeMoveController(size_t idx)
{
  const EMoveDirection directions [] =
  {
    EMoveDirection::Right,
    EMoveDirection::Left,
    EMoveDirection::Up,
    EMoveDirection::Down
  };

  const EMoveDirection reversedDirections [] =
  {
    EMoveDirection::Left,
    EMoveDirection::Right,
    EMoveDirection::Down,
    EMoveDirection::Up
  };

  if ((directions[idx] != gCurrDirection) && (reversedDirections[idx] != gCurrDirection))
  {
    gCurrDirection = directions[idx];
    DrawScreen();
  }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_RefreshSnakeTask */
/**
  * @brief  Function implementing the refreshSnakeTas thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_RefreshSnakeTask */
void RefreshSnakeTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  gDisplay.blinkCursorState = false;
  gDisplay.cursorState = false;
  HD44780UInit(&gDisplay);
  SnakeReset();
  SnakeGenerateAple(osKernelGetSysTimerCount());
  gCurrDirection = EMoveDirection::Right;
  displayMutexHandle = osMutexNew(&displayMutex_attributes);
  /* Infinite loop */
  for(;;)
  {
    DrawScreen();
    osDelayUntil(gRenderTimeTick);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_ButtonTask */
/**
* @brief Function implementing the buttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonTask */
void ButtonTask(void *argument)
{
  /* USER CODE BEGIN ButtonTask */
  ButtonHandlerInit(gButtonHandlers, kButtonsGPIO, GET_ARR_COUNT(gButtonHandlers));
  osTimerStart(buttonTimerHandle, 5);
  /* Infinite loop */
  for(;;)
  {
    button_evn_t event;

    if (osMessageQueueGet(buttonQueueHandle, &event, NULL, osWaitForever) == osOK)
    {
      if (event.idx < 4)
      {
        if (event.state)
        {
          SnakeMoveController(event.idx);
        }
      }
      else
      {
        //
      }
    }
  }
  /* USER CODE END ButtonTask */
}

/* ButtonTimer function */
void ButtonTimer(void *argument)
{
  /* USER CODE BEGIN ButtonTimer */
  ButtonHandler(gButtonHandlers, GET_ARR_COUNT(gButtonHandlers));
  /* USER CODE END ButtonTimer */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
