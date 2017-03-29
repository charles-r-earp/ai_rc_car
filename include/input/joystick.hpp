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
    
    std::thread setup_thread;
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
    
    

    joystick(int num = 0, bool block = true) {
        
        this->setup_thread = std::thread([this, num, block](){
            do {
                std::stringstream ss;
                ss << "/dev/input/js" << num;
                std::string path = ss.str();
                this->file = open(path.c_str(), block ? O_RDONLY : O_RDONLY | O_NONBLOCK);
                //std::cout << "joystick waiting...";
                std::cout << "waiting for " << path << " file: " << file << " errorno: " << errno << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(10));
            } while (this->file <= 0);
            std::cout << "joystick ready" << std::endl;
        });
        
    }
    
    std::vector<event> get_events() {
        
        std::vector<event> events;
        
        js_event next;
        while (read(this->file, &next, sizeof(next)) > 0) {
            events.push_back(event(next));
        }
        
        return events;
    }
    
    ~joystick() {
        close(this->file);
    }
};

#endif // AI_RC_CAR_JOYSTICK_INPUT_HPP