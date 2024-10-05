#include "stm32c0xx_hal.h"

#define A GPIO_PIN_8
#define B GPIO_PIN_9
#define C GPIO_PIN_7
#define D GPIO_PIN_6
#define E GPIO_PIN_5
#define F GPIO_PIN_3
#define G GPIO_PIN_15

int tab[10][7] = {
    // a  b  c  d  e  f  g
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}  // 9
};

int i = 0;

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* Configure GPIO pins */
    GPIO_InitStruct.Pin = A | B | C | D | E | F | G;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Configure the button pin */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; 
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    while (1)
    {
        // Check if the button is pressed
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)
        {
           
            HAL_GPIO_WritePin(GPIOA, A, tab[i][0]);
            HAL_GPIO_WritePin(GPIOA, B, tab[i][1]);
            HAL_GPIO_WritePin(GPIOA, C, tab[i][2]);
            HAL_GPIO_WritePin(GPIOA, D, tab[i][3]);
            HAL_GPIO_WritePin(GPIOA, E, tab[i][4]);
            HAL_GPIO_WritePin(GPIOA, F, tab[i][5]);
            HAL_GPIO_WritePin(GPIOA, G, tab[i][6]);

            i = (i + 1) % 10; 
            HAL_Delay(200);   
        }

      
    }
}



void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    //RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE; // No PLL for HSI

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}


void Error_Handler(void)
{
    // Handle errors appropriately, e.g., blink an error LED or report the error through a debug interface.
    while (1)
    {
        // Infinite loop to keep the microcontroller in an error state
    }
}
