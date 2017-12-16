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

//#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

struct joystick {
    
    int num;
    bool block;
    int file = -1;
    
    struct js_event {
      unsigned int time;     /* event timestamp in milliseconds */
      short value; /* value */
      unsigned char type;      /* event type */
      unsigned char number;    /* axis/button number */
    };
    
    struct event {
        
        const static int min_axis_value = -32768, max_axis_value = 32767;
        
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
    
    

    joystick(int num = 0, bool block = true) : num(num), block(block) {
        /*this->setup_thread = std::thread([this, num, block](){
            while(true) {
                std::stringstream ss;
                ss << "/dev/input/js" << num;
                std::string path = ss.str();
                this->file = open(path.c_str(), block ? O_RDONLY : O_RDONLY | O_NONBLOCK);
                //std::cout << "joystick waiting...";
                std::cout << "waiting for " << path << " file: " << file << " errorno: " << errno << std::endl;
                if (this->file > 0) break;
                std::this_thread::sleep_for (std::chrono::seconds(10));
            }
            std::cout << "joystick ready file: " << this->file << std::endl;
        });*/
        
    }
    
    bool ready() {
        //std::cout << "ready() file: " << this->file << " => ready? = " << (this->file > 0) << std::endl;
        return this->file > 0;
    }
    
    std::vector<event> get_events() {
      std::vector<event> events;
      if(this->ready()) {  
        js_event next;
        int nevents = 0;
        while ((nevents = read(this->file, &next, sizeof(next))) and events.size() < nevents) {
            std::cout << "nevents: " << read(this->file, &next, sizeof(next)) << std::endl;
            events.push_back(event(next));
        }
        if(errno != 0) this->file = -1;
      }
      else {
         std::stringstream ss;
         ss << "/dev/input/js" << this->num;
         std::string path = ss.str();
         this->file = open(path.c_str(), this->block ? O_RDONLY : O_RDONLY | O_NONBLOCK);
         //std::cout << "joystick waiting...";
         std::cout << "waiting for " << path << " file: " << file << " errorno: " << errno << std::endl;
         if(this->file > 0) 
           std::cout << "joystick ready file: " << this->file << std::endl;
      }
      return events;
    }
    
    ~joystick() {
        close(this->file);
    }
};

#endif // AI_RC_CAR_JOYSTICK_INPUT_HPP
