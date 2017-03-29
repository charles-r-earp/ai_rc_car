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

#include <thread>
#include <chrono>
#include <vector>

struct joystick {
    
    int file;
    
    struct js_event {
		unsigned int time;     /* event timestamp in milliseconds */
        short value; /* value */
		unsigned char type;      /* event type */
		unsigned char number;    /* axis/button number */
	};
    
    struct event {
        
        enum Type {
            Button = 0x01,
            Axis = 0x02,
            Init = 0x80
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
        
        int bytes;
        js_event* next;
        while (true) {
            bytes = read(this->file, next, sizeof(*next)); 
            if (bytes > 0) { 
                std::cout << "joystick.get_events() js_event.type = " << int(next->type) << std::endl;
                //events.push_back(event(next));
            }
            else break;
            std::this_thread::sleep_for (std::chrono::milliseconds(1));
        }
        
        return events;
    }
    
    ~joystick() {
        close(this->file);
    }
};

#endif // AI_RC_CAR_JOYSTICK_INPUT_HPP