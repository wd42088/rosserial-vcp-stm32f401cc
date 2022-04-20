#include "main.h"
#include "gpio.h"
#include "usb_device.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "dma.h"
#include "FreeRTOSConfig.h"
#include "start_task.h"
#include "adc.h"

int main()
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USB_DEVICE_Init(); //需要先初始化USB，不然无法识别到
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  HAL_ADC_Start_IT(&hadc1);

  TASK_StartTask();

//  osKernelStart();

  while (1)
  {
      HAL_Delay(100);
  }
  /* USER CODE END 3 */
}
