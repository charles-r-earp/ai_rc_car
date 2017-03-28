
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "unistd.h"

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

    joystick(int num = 0, bool block = true) {
        stringstream ss;
        ss << "/dev/input/js" << num;
        this->file = this->open(ss.str(), block);
    }
    
    int open(std::string path, bool block) {
        open(path.c_str(), block ? O_RDONLY : O_RDONLY | O_NONBLOCK)
    }
    
    event read() {
        
        event next_event;
        
        read(this->file, &next_event, sizeof(next_event)); 
        
        return next_event;
    }
};