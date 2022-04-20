//
// Created by zephyhunt on 2022/4/4.
//
#include "rosnodec.h"
#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int64.h>
#include <std_msgs/Empty.h>
#include "control_one.h"

void led_cb(const std_msgs::Int8 &msg)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

static uint32_t count;
void control_cb(const msg_gen::control_one &msg)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    count = msg.press;
}
ros::NodeHandle nh;
std_msgs::Int64 int_msg;
ros::Publisher chatter("stm_chatter", &int_msg);
ros::Subscriber<msg_gen::control_one> control_sub("control", &control_cb);
ros::Subscriber<std_msgs::Int8> led_sub("led_toggle", &led_cb);
char hello[] = "Hello world!";

void RosnodeC::init()
{
    nh.initNode();
    nh.advertise(chatter);
//    nh.subscribe(led_sub);
    nh.subscribe(control_sub);
}

void RosnodeC::controlLoop()
{
    int_msg.data = count;
//    std::stringstream ss;
//    ss << "hello"<< count;
    chatter.publish(&int_msg);
    nh.spinOnce();
}


void setup(void)
{
}

void loop(void)
{
}
