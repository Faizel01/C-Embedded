
#include "main.h"

// Визначення пінів світлодіодів
#define LED_GREEN_PIN   GPIO_PIN_12
#define LED_ORANGE_PIN  GPIO_PIN_13
#define LED_RED_PIN     GPIO_PIN_14
#define LED_BLUE_PIN    GPIO_PIN_15
#define LED_PORT        GPIOD

// Змінні для контролю часу та вибору режиму
uint32_t last_mode_switch = 0;
uint8_t current_mode = 0;

// Прототипи функцій
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void Run_Algorithm_0(void);
void Run_Algorithm_1(void);
void Run_Algorithm_2(void);
void Run_Algorithm_3(void);
void Error_Handler(void);


int main(void)
{
    // Ініціалізація HAL та системного годинника
    HAL_Init();
    SystemClock_Config();

    // Ініціалізація GPIO
    MX_GPIO_Init();

    last_mode_switch = HAL_GetTick();

    while (1)
    {
        // Автоматичне перемикання алгоритмів кожні 3 секунди
        if (HAL_GetTick() - last_mode_switch >= 3000)
        {
            last_mode_switch = HAL_GetTick();
            current_mode = (current_mode + 1) % 4;

            // Гасіння всіх світлодіодів
            HAL_GPIO_WritePin(
                LED_PORT,
                LED_GREEN_PIN | LED_ORANGE_PIN |
                LED_RED_PIN | LED_BLUE_PIN,
                GPIO_PIN_RESET
            );
        }

        // Виконання поточного алгоритму
        switch (current_mode)
        {
            case 0:
                Run_Algorithm_0();
                break;

            case 1:
                Run_Algorithm_1();
                break;

            case 2:
                Run_Algorithm_2();
                break;

            case 3:
                Run_Algorithm_3();
                break;
        }
    }
}


// Алгоритм 0: Послідовний бігучий вогонь
void Run_Algorithm_0(void)
{
    uint16_t leds[] = {
        LED_GREEN_PIN,
        LED_ORANGE_PIN,
        LED_RED_PIN,
        LED_BLUE_PIN
    };

    for (int i = 0; i < 4; i++)
    {
        if (HAL_GetTick() - last_mode_switch >= 3000)
            return;

        HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_SET);
        HAL_Delay(150);
        HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_RESET);
    }
}


// Алгоритм 1: Попарне перемикання
void Run_Algorithm_1(void)
{
    if (HAL_GetTick() - last_mode_switch >= 3000)
        return;

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_GREEN_PIN | LED_RED_PIN,
        GPIO_PIN_SET
    );

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_ORANGE_PIN | LED_BLUE_PIN,
        GPIO_PIN_RESET
    );

    HAL_Delay(250);

    if (HAL_GetTick() - last_mode_switch >= 3000)
        return;

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_GREEN_PIN | LED_RED_PIN,
        GPIO_PIN_RESET
    );

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_ORANGE_PIN | LED_BLUE_PIN,
        GPIO_PIN_SET
    );

    HAL_Delay(250);
}


// Алгоритм 2: Синхронний стробоскоп
void Run_Algorithm_2(void)
{
    if (HAL_GetTick() - last_mode_switch >= 3000)
        return;

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_GREEN_PIN | LED_ORANGE_PIN |
        LED_RED_PIN | LED_BLUE_PIN,
        GPIO_PIN_SET
    );

    HAL_Delay(200);

    if (HAL_GetTick() - last_mode_switch >= 3000)
        return;

    HAL_GPIO_WritePin(
        LED_PORT,
        LED_GREEN_PIN | LED_ORANGE_PIN |
        LED_RED_PIN | LED_BLUE_PIN,
        GPIO_PIN_RESET
    );

    HAL_Delay(200);
}


// Алгоритм 3: Ефект змійка
void Run_Algorithm_3(void)
{
    uint16_t leds_bounce[] = {
        LED_GREEN_PIN,
        LED_ORANGE_PIN,
        LED_RED_PIN,
        LED_BLUE_PIN,
        LED_RED_PIN,
        LED_ORANGE_PIN
    };

    for (int i = 0; i < 6; i++)
    {
        if (HAL_GetTick() - last_mode_switch >= 3000)
            return;

        HAL_GPIO_WritePin(
            LED_PORT,
            leds_bounce[i],
            GPIO_PIN_SET
        );

        HAL_Delay(120);

        HAL_GPIO_WritePin(
            LED_PORT,
            leds_bounce[i],
            GPIO_PIN_RESET
        );
    }
}


// Ініціалізація GPIO
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Увімкнення тактування GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Початковий стан світлодіодів
    HAL_GPIO_WritePin(
        LED_PORT,
        LED_GREEN_PIN | LED_ORANGE_PIN |
        LED_RED_PIN | LED_BLUE_PIN,
        GPIO_PIN_RESET
    );

    // Налаштування PD12-PD15 як виходів
    GPIO_InitStruct.Pin =
        LED_GREEN_PIN |
        LED_ORANGE_PIN |
        LED_RED_PIN |
        LED_BLUE_PIN;

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}


// Налаштування системного годинника
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(
        PWR_REGULATOR_VOLTAGE_SCALE1
    );

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(
        &RCC_ClkInitStruct,
        FLASH_LATENCY_0
    ) != HAL_OK)
    {
        Error_Handler();
    }
}


// Обробник помилок
void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}
