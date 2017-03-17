#ifndef AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
#define AI_RC_CAR_CONTROL_PWM_DRIVER_HPP

/*#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>*/
#include <cstddef> // define NULL
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cassert>
#include <string>
#include <iostream>

namespace control {
    
    
    
    struct i2c_device {
        
        int address;
        
        int file; 
        
        i2c_device(const int& address, const std::string device = "/dev/i2c-1") {
            
            file = open(device.c_str(), O_RDWR);
            
            if (file < 0) {
                
                std::cout << "i2c_device() error = " << file << std::endl;
                
                abort();
            }
            
            this->address = address;
        }
        
        bool check_address() {
            
            if (ioctl(this->file, I2C_SLAVE, this->address) < 0) {
                
                std::cout << "i2c_device.check_address address = " << address << " error = " << file << std::endl;
                
                return false;
            }
            else {
                
                return true;
            }
            
        }
        
        void write(const int& reg, const int& value) {
            
            assert(this->check_address());
            
            i2c_smbus_write_word_data(this->file, reg, value);
        }
        
        /*int read(const int& reg) {
            
            assert(this->check_address());
            
            return i2c_smbus_read_word_data(file, reg);*/
        
    };

    // Adafruit P815
    
    struct pwm_driver : i2c_device {
        
        const static int PCA9685_MODE1 = 0x0;
        
        pwm_driver(const int address = 0x40) : i2c_device(address) {
        
            this->reset();
        }
        
        void reset() {
            
            //this->write(PCA9685_MODE1, 0x0);
        }
        
        
    };
}



#endif // AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
