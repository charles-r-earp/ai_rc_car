#ifndef AI_RC_CAR_JOYSTICK_INPUT_HPP
#define AI_RC_CAR_JOYSTICK_INPUT_HPP


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>

#include <errno.h>

struct joystick {
    
    int file;
    
    struct js_event {
		__u32 time;     /* event timestamp in milliseconds */
		__s16 value;    /* value */
		__u8 type;      /* event type */
		__u8 number;    /* axis/button number */
	};
    
    struct event {
        
        enum Type {
            Init = 0x00,
            Button = 0x01,
            Axis = 0x02
        };
        
        event(const js_event& js_ev) {
            
            this->time_ms = js_ev.time;
            this->value = js_ev.value;
            this->type = Type(js_ev.type);
            this->number = js_ev.number;
        } 
        
        int time_ms, value;
        Type type;
        int number;
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
    
    std::vector<event> get_events() {
        
        std::vector<event> events;
        
        int error;
        js_event next;
        while (true) {
            error = read(this->file, &next, sizeof(event)); 
            if (error > 0) { 
                std::cout << "joystick.get_events() js_event.type = " << next.type << std::endl;
                events.push_back(event(next));
            }
            else break;
        }
        
        return events;
    }
    
    ~joystick() {
        close(this->file);
    }
};

#endif // AI_RC_CAR_JOYSTICK_INPUT_HPP