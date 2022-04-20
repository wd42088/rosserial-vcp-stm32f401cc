//
// Created by zephyhunt on 2022/4/4.
//

#include "rosnode_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "rosnodec.h"

void RosNode_Task(void * pv)
{
    RosnodeC rosnode;
    rosnode.init();
    while (true)
    {
        rosnode.controlLoop();
        vTaskDelay(10);
    }
}