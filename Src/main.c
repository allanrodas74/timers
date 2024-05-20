#include <stdint.h>
//#include "stm32l053xx.h"
#include "stm32l053xx.h"
#include "core_cm0plus.h"
void SystemClock_Config(void);
void GPIO_Init(void);
void TIM2_Init(void);
void TIM3_Init(void);
void TIM21_Init(void);
void TIM6_Int(void);

int main(void)
{
    // Configuración del sistema y perifericos
    SystemClock_Config();
    GPIO_Init();
    TIM2_Init();
    TIM6_Init();
    TIM21_Init();

    // Activar los timers
    TIM2->CR1 |= (1 << 0);
    TIM6->CR1 |= (1 << 0);
    TIM21->CR1 |= (1 << 0);




    while(1)
    {
        // Verificar y limpiar el flag de actualización para TIM2
        if (TIM2->SR & 0x00000001) {
            TIM2->SR &= ~0x00000001; // Limpiar UIF
            GPIOA->ODR ^= (1 << 5);  // Toggle PA5
        }


        // Verificar y limpiar el flag de actualización para TIM6
               if (TIM6->SR & 0x00000001) {
                   TIM6->SR &= ~0x00000001; // Limpiar UIF
                   GPIOA->ODR ^= (1<<6); // Toggle PA6
               }

        // Verificar y limpiar el flag de actualización para TIM21
        if (TIM21->SR & 0x00000001) {
            TIM21->SR &= ~0x00000001; // Limpiar UIF
            GPIOA->ODR ^= (1 << 7);  // Toggle PA7
        }
    }
}

void SystemClock_Config(void)
{
    // Activar HSI (16 MHz) y esperar a que esté listo
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    // Seleccionar HSI como fuente de reloj del sistema
    RCC->CFGR |= RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
}

void GPIO_Init(void)
{
    // Habilitar el reloj para GPIOA
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    // Configurar PA5, PA6 y PA7 como salida
    GPIOA->MODER &= ~(GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
    GPIOA->MODER |= (GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
}

void TIM2_Init(void)
{
    // Habilitar el reloj para TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configurar TIM2: PSC = 1600 - 1, ARR = 9999
    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 9999;
}
void TIM6_Init(void)
{
    // Habilitar el reloj para TIM6
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    // Configurar TIM6: PSC = 1600 - 1, ARR = 4999
    TIM6->PSC = 1600 - 1;
    TIM6->ARR = 4999;
}




void TIM21_Init(void)
{
    // Habilitar el reloj para TIM21
    RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;

    // Configurar TIM21: PSC = 1600 - 1, ARR = 2499
    TIM21->PSC = 1600 - 1;
    TIM21->ARR = 2499;
}
