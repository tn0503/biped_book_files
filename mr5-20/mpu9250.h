#ifndef MPU9250_H
#define MPU9250_H

#include <Wire.h>

#define MPU9250_ADDRESS 0x68
#define PWR_MGMT_1 0x6B

#define GYRO_CONFIG 0x1B
#define GYRO_FS_SEL_250 0x00
#define GYRO_FS_SEL_500 0x01
#define GYRO_FS_SEL_1000 0x02
#define GYRO_FS_SEL_2000 0x03

#define ACCEL_CONFIG 0x1C
#define ACCEL_FS_SEL_2 0x00
#define ACCEL_FS_SEL_4 0x01
#define ACCEL_FS_SEL_8 0x02
#define ACCEL_FS_SEL_16 0x03

#define INT_PIN_CFG 0x37

extern float acFullScaleRange;
extern float gyFullScaleRange;
extern uint8_t mpuData[14];
extern uint8_t magData[7];
extern int16_t a_rawX, a_rawY,a_rawZ;
extern int16_t g_rawX,g_rawY,g_rawZ;
extern float acX,acY,acZ;
extern float gyX,gyY,gyZ;

void i2c_write(uint8_t address, 
                uint8_t location, 
                volatile uint8_t dat);

void i2c_read(uint8_t address, 
              uint8_t location, 
              uint8_t howmany, 
              volatile uint8_t* buff);

void read_mpu9250();

void init_mpu9250();

#endif
