//
// Created by zephyhunt on 2022/2/15.
//
#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "rosnode_task.h"

static TaskHandle_t task_create_handle;
static TaskHandle_t bsp_task_handle;
static TaskHandle_t test_task_handle;

static StaticTask_t Task_Create_TCB;

//static StackType_t LED_Task_Stack[128];

void Task_Create(void *);
void Bsp_Task(void * parameter);
void Test_Task(void * parameter);

void TASK_StartTask(void)
{
    BaseType_t xReturn = pdPASS;
    //使用动态内存的方式创建
    xReturn = xTaskCreate(	Task_Create,
                            "Task_Create",
                            128,
                            ( void * ) NULL, /*lint !e961.  The cast is not redundant for all compilers. */
                            3, /* In effect ( tskIDLE_PRIORITY | portPRIVILEGE_BIT ), but tskIDLE_PRIORITY is zero. */
                            &task_create_handle );
    if (pdPASS == xReturn)
    {
        vTaskStartScheduler();
    }
}


void Task_Create(void *)
{
    taskENTER_CRITICAL();
    BaseType_t xReturn = pdPASS;
    xTaskCreate(	Bsp_Task,
                            "Bsp_Task",
                            128,
                            ( void * ) NULL, /*lint !e961.  The cast is not redundant for all compilers. */
                            3,
                            &bsp_task_handle);
    xTaskCreate(	RosNode_Task,
                    "Bsp_Task",
                    1024,
                    ( void * ) NULL, /*lint !e961.  The cast is not redundant for all compilers. */
                    4,
                    &bsp_task_handle);

    xReturn = xTaskCreate(	Test_Task,
                              "test_Task",
                              256,
                              ( void * ) NULL, /*lint !e961.  The cast is not redundant for all compilers. */
                              3,
                              &test_task_handle);
    if (pdPASS == xReturn)
        vTaskDelete(task_create_handle);
    else return;
    taskEXIT_CRITICAL();
}

void Bsp_Task(void * parameter)
{
    while (true)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
        vTaskDelay(1000);
    }
}

uint32_t adc_data;
uint16_t i;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

    //获取值并存储
    adc_data=HAL_ADC_GetValue(hadc);
    i++;
}

void Test_Task(void *pv)
{
    float press, v;
    while(true)
    {
//        HAL_ADC_Stop_IT(&hadc1);
//        adc_data = HAL_ADC_GetValue(&hadc1);
        v = (adc_data / 4096.0f * 3.3);
        press = (v - 0.2) * 40.0f / 2.5; //乘以更少
//        i++;
        usart_printf("v:%d, %d\n", (int32_t )press * 100, i);
        HAL_ADC_Start_IT(&hadc1);

        vTaskDelay(20);
    }
}