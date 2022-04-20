//
// Created by zephyhunt on 2022/4/4.
//

#ifndef ROSSERIAL_VCP_STM32F401CC_ROSNODEC_H
#define ROSSERIAL_VCP_STM32F401CC_ROSNODEC_H


class RosnodeC {
public:
    RosnodeC() = default;

    void init();
    void controlLoop();


};


#endif //ROSSERIAL_VCP_STM32F401CC_ROSNODEC_H
