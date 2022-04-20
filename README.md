# ROSSrial-基于stm32 vcp(虚拟串口)配置过程

## 1.背景

通常习惯于用stm32作为底层控制，当加入图像或复杂算法时,需要上位机的加入， 通常走的是ros通信,  stm32/ros提供rosserial是比较不错的选择，不用自己去解析协议。  github上搜索rosseial stm32关键词有基于串口dma的例程, 这儿修改为虚拟串口。

## 2. 配置

### 2.1 cubemx配置

参考文章https://blog.csdn.net/yuleitao/article/details/103970358

时钟![image-20220404104339060](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404104339060.png)

sys![image-20220404104422030](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404104422030.png)

Connectivity-USB_OTG_FS（参数默认）![image-20220404104513631](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404104513631.png)

Middleware USB_DEVICE （参数默认）![image-20220404104618074](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404104618074.png)

我这儿把FreeRTOS也打开了![image-20220404105202155](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404105202155.png)

配置一个灯![image-20220404105220693](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404105220693.png)

时钟配置（需要根据自己板子和芯片型号）![image-20220404104915987](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404104915987.png)

代码生成配置，这儿走clion，因为配置了操作系统，堆栈配置高一点，不然会有警告![image-20220404105802137](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404105802137.png)

### 2.2 Clion配置

进入clion首先编译，报错，未使能浮点数计算![image-20220404110209019](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404110209019.png)

CMakeLists取消注释这一段![image-20220404110246857](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404110246857.png)

重新编译，报错解决

![image-20220404110430379](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404110430379.png)

拷贝roslib到工程目录(roslib可以直接在rossrial-stm32 github链接上生成，有教程)

![image-20220404110648064](/home/zephyhunt/CLionProjects/rosserial-vcp-stm32f401cc/IMAGE/image-20220404110648064.png)

将roslib添加到cmake工程中，（见CMake用法，或者其他IDE的添加方式也行）

修改STM32Hardware.h默认是串口2的DMA通信

