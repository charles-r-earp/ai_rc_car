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
#include <vector>

namespace control {
    
    struct i2c_device {
        
        int address;
        
        int file; 
        
        i2c_device(const int& address, const std::string device = "/dev/i2c-1") {
            
            file = open(device.c_str(), O_RDWR);
            
            if (file < 0) {
                
                std::cout << "i2c_device() error = " << errno << std::endl;
                
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
        
        void write(const int& value) {
            
            assert(this->check_address());
            
            i2c_smbus_write_byte(this->file, value);
        }
        
        void write(const int& reg, const int& value) {
            
            assert(this->check_address());
            
            i2c_smbus_write_word_data(this->file, reg, value);
        }
        
        int read(const int& reg) {
            
            assert(this->check_address());
            
            return i2c_smbus_read_word_data(file, reg);
        }
        
    };
    
    const static int PCA9685_MODE1 = 0x0;
    const static int PCA9685_PRESCALE = 0xFE;
    const static int PCA9685_SLEEP_BIT = 4;
    const static int LED0_ON_L = 0x6;
    const static int LED0_ON_H = 0x7;
    const static int LED0_OFF_L = 0x8;
    const static int LED0_OFF_H = 0x9;
    const static int SCALE = 4095;
    const static int FREQ_MIN = 24;
    const static int FREQ_MAX = 1526;
    

    // Adafruit P815
    
    struct pwm_driver : i2c_device {
        
        
        
        pwm_driver(const int address = 0x40, const int update_rate = 500) : i2c_device(address) {
        
            this->reset();
            
            
            this->sleep();
            
            this->write(PCA9685_PRESCALE, (25*10^6/(4096*update_rate)) - 1);
            int val = this->read(PCA9685_PRESCALE);
            int rate = (1 + val) * 4096/25000000.0;
            
            std::cout << "pwm update_frequency = " << rate << std::endl;
            
            this->sleep();
        }
        
        void reset() {
            
            this->write(PCA9685_MODE1, 0x0);
        }
        
        void sleep() {
            
            this->write(PCA9685_MODE1 + PCA9685_SLEEP_BIT, 1 );
        }
        
        void set_width(const int& num, const double& sec) {
            
            int x = SCALE/(sec * (FREQ_MAX - FREQ_MIN));
            
            
            this->write(LED0_ON_L+4*num, x);
            this->write(LED0_ON_H+4*num, SCALE);
            this->write(LED0_OFF_L+4*num, SCALE-x);
            this->write(LED0_OFF_H+4*num, 0);
            
        }
        
        void set_duty(const int& num, const double& duty) {
            // duty is fraction on
            
            this->write(LED0_ON_L+4*num, duty*SCALE);
            this->write(LED0_ON_H+4*num, SCALE);
            this->write(LED0_OFF_L+4*num, (1-duty)*SCALE);
            this->write(LED0_OFF_H+4*num, 0);
        }
        
        
    };
}



#endif // AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
