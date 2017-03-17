#ifndef AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
#define AI_RC_CAR_CONTROL_PWM_DRIVER_HPP

namespace control {
    
    struct i2c_device {
        
        int address;
        
        int file; 
        
        i2c_device(const int& address, const std::string device = "/dev/i2c-1") {
            
            file = open(this->device, O_RWR);
            
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
            
            assert(this->check_adress());
            
            i2c_smbus_write_word_data(this->file, reg, value);
        }
        
        int read(const int& reg) {
            
            assert(this->check_adress());
            
            return i2c_smbus_read_word_data(file, reg);
        }
    }

    // Adafruit P815
    
    struct pwm_driver : i2c_device {
        
        const static int PCA9685_MODE1 0x0;
        
        pwm_driver(int address = 0x40) : i2c_device(address) {
        
            this->reset();
        }
        
        void reset() {
            
            this->write(PCA9685_MODE1, 0x0);
        }
        
        
    };
}



#endif // AI_RC_CAR_CONTROL_PWM_DRIVER_HPP
