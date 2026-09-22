/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - LED Garland
  ******************************************************************************
  */

#include "main.h"

/* Приватні функції */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  /* Скидання всіх периферійних пристроїв, ініціалізація Flash та Systick */
  HAL_Init();

  /* Налаштування системного тактування */
  SystemClock_Config();

  /* Ініціалізація налаштованих периферійних пристроїв (GPIO) */
  MX_GPIO_Init();

  /* Нескінченний цикл програми */
  while (1)
  {
    /* --- Етап 1: Біжучий вогонь по колу --- */

    // Вмикаємо Green (PD12)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    // Вмикаємо Orange (PD13)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

    // Вмикаємо Red (PD14)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);

    // Вмикаємо Blue (PD15)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
    HAL_Delay(150);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);


    /* --- Етап 2: Попарне інвертування (Toggle) --- */

    for (int i = 0; i < 4; i++)
    {
      // Перемикаємо стан протилежних світлодіодів
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_14); // Green & Red
      HAL_Delay(200);
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13 | GPIO_PIN_15); // Orange & Blue
      HAL_Delay(200);
    }

    // Вимикаємо всі світлодіоди перед наступним етапом
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
    HAL_Delay(100);


    /* --- Етап 3: Синхронне спалахування всіх 4-х світлодіодів --- */

    for (int i = 0; i < 3; i++)
    {
      // Увімкнути всі 4 світлодіоди
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
      HAL_Delay(100);

      // Вимкнути всі 4 світлодіоди
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
      HAL_Delay(100);
    }

    HAL_Delay(300); // Пауза перед початком нового циклу
  }
}

/**
  * @brief Ініціалізація порту GPIOD для світлодіодів PD12, PD13, PD14, PD15
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Тактування GPIOD */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Початковий стан пінів — RESET (вимкнені) */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

  /* Конфігурація пінів PD12, PD13, PD14, PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void SystemClock_Config(void)
{
  /* Стандартні налаштування системного годинника CubeIDE */
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
