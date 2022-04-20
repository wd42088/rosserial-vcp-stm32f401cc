#ifndef _ROS_msg_gen_control_one_h
#define _ROS_msg_gen_control_one_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace msg_gen
{

    class control_one : public ros::Msg
    {
    public:
        typedef uint8_t _isOpen_type;
        _isOpen_type isOpen;
        typedef uint8_t _isOff_type;
        _isOff_type isOff;
        typedef int32_t _press_type;
        _press_type press;

        control_one():
                isOpen(0),
                isOff(0),
                press(0)
        {
        }

        virtual int serialize(unsigned char *outbuffer) const
        {
            int offset = 0;
            *(outbuffer + offset + 0) = (this->isOpen >> (8 * 0)) & 0xFF;
            offset += sizeof(this->isOpen);
            *(outbuffer + offset + 0) = (this->isOff >> (8 * 0)) & 0xFF;
            offset += sizeof(this->isOff);
            union {
                int32_t real;
                uint32_t base;
            } u_press;
            u_press.real = this->press;
            *(outbuffer + offset + 0) = (u_press.base >> (8 * 0)) & 0xFF;
            *(outbuffer + offset + 1) = (u_press.base >> (8 * 1)) & 0xFF;
            *(outbuffer + offset + 2) = (u_press.base >> (8 * 2)) & 0xFF;
            *(outbuffer + offset + 3) = (u_press.base >> (8 * 3)) & 0xFF;
            offset += sizeof(this->press);
            return offset;
        }

        virtual int deserialize(unsigned char *inbuffer)
        {
            int offset = 0;
            this->isOpen =  ((uint8_t) (*(inbuffer + offset)));
            offset += sizeof(this->isOpen);
            this->isOff =  ((uint8_t) (*(inbuffer + offset)));
            offset += sizeof(this->isOff);
            union {
                int32_t real;
                uint32_t base;
            } u_press;
            u_press.base = 0;
            u_press.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
            u_press.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
            u_press.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
            u_press.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
            this->press = u_press.real;
            offset += sizeof(this->press);
            return offset;
        }

        const char * getType(){ return "msg_gen/control_one"; };
        const char * getMD5(){ return "98b058d37cd7cd714950b244b36218f9"; };

    };

}
#endif