#ifndef AI_RC_CAR_JOYSTICK_INPUT_HPP
#define AI_RC_CAR_JOYSTICK_INPUT_HPP


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#include <errno.h>

struct joystick {
    
    int file;
    
    struct event {
        
        enum Type {
            Button = 0x01,
            Axis = 0x02
        };
        
        short value;
        unsigned char type, number;
        
        Type get_type() {
            return Type(this->type);
        }
    };

    bool init(int num = 0, bool block = true) {
        std::stringstream ss;
        ss << "/dev/input/js" << num;
        std::string path = ss.str();
        this->file = open(path.c_str(), block ? O_RDONLY : O_RDONLY | O_NONBLOCK);
        std::cout << "joystick() file = " << this->file << std::endl;
        printf ("Error no is : %d\n", errno);
        
        return this->file >= 0;
    }
    
    event get() {
        
        event next_event;
        
        read(this->file, &next_event, sizeof(next_event)); 
        
        std::cout << "joystick.get() event.type = " << next_event.type << std::endl;
        
        return next_event;
    }
    
    ~joystick() {
        close(this->file);
    }
};

#endif // AI_RC_CAR_JOYSTICK_INPUT_HPP