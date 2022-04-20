/* 
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2018, Kenta Yonekura (a.k.a. yoneken)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROS_STM32_HARDWARE_H_
#define ROS_STM32_HARDWARE_H_

#define STM32F4xx  // Change for your device
#define USB

#ifdef STM32F3xx
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_uart.h"
#endif /* STM32F3xx */
#ifdef STM32F4xx
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#endif /* STM32F4xx */

#ifdef STM32F7xx
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#endif /* STM32F7xx */


#ifdef USB

// Change "CDC_Transmit_FS" and "CDC_Receive_FS" Function
// in '../USB_DEVICE/App/usbd_cdc_if.c'
#include "usbd_cdc_if.h"
#include "usb_device.h"

extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern uint32_t rx_head;   // From usbd_cdc_if.h

class STM32Hardware {
 private:
	uint32_t rx_tail;

 public:
  STM32Hardware(){}

  // Any initialization code necessary to use the serial port:
  void init() {
	  rx_head = rx_tail = 0u;
  }

  // Read a byte from the serial port. -1 = failure:
  int read() {
	  // Quit if no new character:
	  if (rx_head == rx_tail){
		  memset(UserRxBufferFS, 0, sizeof(UserRxBufferFS));
		  rx_head = rx_tail = 0u;
		  return -1;
	  }
	  // Get next char in buffer:
	  return static_cast<int>(UserRxBufferFS[rx_tail++]);
  }

  // Write data to the connection to ROS:
  void write(uint8_t* data, int length) {
	  while(CDC_Transmit_FS((uint8_t *)data, length) != USBD_OK);//确保发完再发
  }

  // Returns milliseconds since start of program:
  unsigned long time() { return HAL_GetTick(); };
};

#endif /* USB */
#endif
