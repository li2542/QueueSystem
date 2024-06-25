#include "exti.h"
#include "led.h"



//控制红外传感器flag
uint8_t ia_flag;

void exti_init(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable,开启时钟 */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins  */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;  
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    //led_off();
}

void exti_PA4_init(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable,开启时钟 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins  */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;  
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    //led_off();
}



void exti_PB4_init(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable,开启时钟 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins  */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; //下降延触发
  GPIO_InitStruct.Pull = GPIO_PULLUP;    //上拉
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    //led_off();
}


void EXTI4_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    //__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
}


void EXTI0_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    //__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    //HAL_Delay(5);
    if(GPIO_Pin == GPIO_PIN_0){
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET){
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
        }
            
    }
    
    if(GPIO_Pin == GPIO_PIN_4){
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) == GPIO_PIN_RESET){
            ia_flag = TRUE;
        }
            
    }
}

uint8_t ia_flag_get(void){
    uint8_t temp = ia_flag;
    ia_flag = FALSE;
    return temp;
}

void ia_flag_set(uint8_t value){
    ia_flag = value;
}



