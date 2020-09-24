#include "mpu9250.h"

float acFullScaleRange;
float gyFullScaleRange;
uint8_t mpuData[14];
uint8_t magData[7];
int16_t a_rawX, a_rawY,a_rawZ;
int16_t g_rawX,g_rawY,g_rawZ;
float acX,acY,acZ;
float gyX,gyY,gyZ;

void i2c_write(uint8_t address, uint8_t location, volatile uint8_t dat){
  Wire.beginTransmission(address);
  Wire.write(location);
  Wire.write(dat);
  Wire.endTransmission();
}

void i2c_read(uint8_t address, uint8_t location, uint8_t howmany, volatile uint8_t* buff){
  Wire.beginTransmission(address);
  Wire.write(location);
  Wire.endTransmission();
  
  Wire.requestFrom(address, howmany);
  uint8_t i=0;
  while(Wire.available()){
    buff[i++] = Wire.read();
  }
}

void read_mpu9250(){
  i2c_read(MPU9250_ADDRESS, 0x3B, 14, mpuData);
  
  a_rawX = (mpuData[0] << 8) | mpuData[1];
  a_rawY = (mpuData[2] << 8) | mpuData[3];
  a_rawZ = (mpuData[4] << 8) | mpuData[5];
  g_rawX = (mpuData[8] << 8) | mpuData[9];
  g_rawY = (mpuData[10] << 8) | mpuData[11];
  g_rawZ = (mpuData[12] << 8) | mpuData[13];
  
  acX = a_rawX * acFullScaleRange / 32768.0f;
  acY = a_rawY * acFullScaleRange / 32768.0f;
  acZ = a_rawZ * acFullScaleRange / 32768.0f;
  gyX = g_rawX * gyFullScaleRange / 32768.0f;
  gyY = g_rawY * gyFullScaleRange / 32768.0f;
  gyZ = g_rawZ * gyFullScaleRange / 32768.0f;
}

void init_mpu9250(){
  Wire.begin();
  i2c_write(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
  i2c_write(MPU9250_ADDRESS, GYRO_CONFIG, (GYRO_FS_SEL_2000)<<3);
  gyFullScaleRange = 2000.0;
  i2c_write(MPU9250_ADDRESS, ACCEL_CONFIG, (ACCEL_FS_SEL_16)<<3);
  acFullScaleRange = 16.0;
  i2c_write(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);
}
