#ifndef AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
#define AI_RC_CAR_CONTROL_PWM_DRIVER_HPP

#include <cstddef> // define NULL
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cassert>
#include <string>
#include <iostream>
#include <cmath>

#include <thread>
#include <chrono> 

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
    
    

    // Adafruit P815
    
    struct pwm_driver : i2c_device {
        
        // Registers/etc:
        int PCA9685_ADDRESS = 0x40;
        int MODE1 = 0x00;
        int MODE2 = 0x01;
        int SUBADR1 = 0x02;
        int SUBADR2 = 0x03;
        int SUBADR3 = 0x04;
        int PRESCALE = 0xFE;
        int LED0_ON_L = 0x06;
        int LED0_ON_H = 0x07;
        int LED0_OFF_L = 0x08;
        int LED0_OFF_H = 0x09;
        int ALL_LED_ON_L = 0xFA;
        int ALL_LED_ON_H = 0xFB;
        int ALL_LED_OFF_L = 0xFC;
        int ALL_LED_OFF_H = 0xFD;
        
        // Bits:
        int RESTART = 0x80;
        int SLEEP = 0x10;
        int ALLCALL = 0x01;
        int INVRT = 0x10;
        int OUTDRV = 0x04;
        
        
        struct servo {
            
            int channel;
            
            servo(int channel = 0) {
            
                this->channel = channel;
            }
            
            mutable int min = 150;
            mutable int max = 600;
        };
        
        
        pwm_driver(const int address = 0x40) : i2c_device(address) {
        
            this->set_all_pwm(0, 0);
            this->write(MODE2, OUTDRV);
            this->write(MODE1, ALLCALL);
            
            std::this_thread::sleep_for (std::chrono::milliseconds(5));
            
            auto mode1 = this->read(MODE1);
            mode1 = mode1 & ~SLEEP;
            this->write(MODE1);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        
        void set_pwm_freq(double freq_hz) {
            
            //"""Set the PWM frequency to the provided value in hertz."""
            double prescaleval = 25000000.0;    // 25MHz
            prescaleval /= 4096.0;     // 12-bit
            prescaleval /= freq_hz;
            prescaleval -= 1.0;
        //logger.debug('Setting PWM frequency to {0} Hz'.format(freq_hz))
            std::cout << "Setting PWM frequency to " << freq_hz <<  " Hz" << std::endl; 
        //logger.debug('Estimated pre-scale: {0}'.format(prescaleval))
            std::cout << "Estimated pre-scale: " << prescaleval << std::endl; 
            int prescale = int(std::floor(prescaleval + 0.5));
            //logger.debug('Final pre-scale: {0}'.format(prescale))
            std::cout << "Final pre-scale: " << prescale << std::endl;
            int oldmode = this->read(MODE1);
            int newmode = (oldmode & 0x7F) | 0x10;    // sleep
            this->write(MODE1, newmode);  // go to sleep
            this->write(PRESCALE, prescale);
            this->write(MODE1, oldmode);
                
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            
            this->write(MODE1, oldmode | 0x80);
        }
        
        void set_pwm(int channel, int on, int off) {
            
            std::cout << "set_pwm(" << channel << ", " << on << ", " << off << ")" << std::endl;
            
            //"""Sets a single PWM channel."""
            this->write(LED0_ON_L+4*channel, on & 0xFF);
            this->write(LED0_ON_H+4*channel, on >> 8);
            this->write(LED0_OFF_L+4*channel, off & 0xFF);
            this->write(LED0_OFF_H+4*channel, off >> 8);
        }

        void set_all_pwm(int on, int off) {
            //"""Sets all PWM channels."""
            this->write(ALL_LED_ON_L, on & 0xFF);
            this->write(ALL_LED_ON_H, on >> 8);
            this->write(ALL_LED_OFF_L, off & 0xFF);
            this->write(ALL_LED_OFF_H, off >> 8);
        }
        

        // Helper function to make setting a servo pulse width simpler.
        void set_servo_pulse(int channel, int pulse) {
            
            double pulse_length = 1000000; //   # 1,000,000 us per second
            pulse_length /= 60;     //  # 60 Hz
            //print('{0}us per period'.format(pulse_length))
            pulse_length /= 4096;  //   # 12 bits of resolution
            //print('{0}us per bit'.format(pulse_length))
            pulse *= 1000;
            pulse /= pulse_length;
            this->set_pwm(channel, 0, pulse);
        }
        
        void set_ratio(const servo& s, double ratio) {
        
            this->set_servo_pulse(s.channel, ratio*(s.max-s.min) + s.min);
        }
        
    };
}



#endif // AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
