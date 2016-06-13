
#ifndef MAGNETOMETER_HMC5883L_H_
#define MAGNETOMETER_HMC5883L_H_

#include "I2C_Master.h"

#define HMC5883L_WRITE 0x3C // write address
#define HMC5883L_READ 0x3D // read address

#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

float m_Scale = 1;

void Compass_SetScale(float gauss){
	uint8_t regValue = 0x00;
	if(gauss == 0.88){
		regValue = 0x00;
		m_Scale = 0.73;
		}else if(gauss == 1.3){
		regValue = 0x01;
		m_Scale = 0.92;
		}else if(gauss == 1.9){
		regValue = 0x02;
		m_Scale = 1.22;
		}else if(gauss == 2.5){
		regValue = 0x03;
		m_Scale = 1.52;
		}else if(gauss == 4.0){
		regValue = 0x04;
		m_Scale = 2.27;
		}else if(gauss == 4.7){
		regValue = 0x05;
		m_Scale = 2.56;
		}else if(gauss == 5.6){
		regValue = 0x06;
		m_Scale = 3.03;
		}else if(gauss == 8.1){
		regValue = 0x07;
		m_Scale = 4.35;
	}
	regValue = regValue << 5; // Setting is in the top 3 bits of the register.
	Write_Compass(ConfigurationRegisterB, regValue);
}

void init_HMC5883L(void){
	Write_Compass(ConfigurationRegisterA,0x70); //(number of samples averaged = 8) and (Data Output Rate Bits = 15 default)
	Compass_SetScale(4.7); //Gain Configuration Bits. Sensor Field Range=±4.7(Ga), Gain=390(LSb/Gauss), Resolution=2.56(mG/LSb)
	Write_Compass(ModeRegister,Measurement_Continuous);
}

void Write_Compass(uint8_t address, uint8_t data){
	i2c_start(HMC5883L_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
}

void Read_Compass(uint8_t buffer[], uint8_t length){
	i2c_start_wait(HMC5883L_WRITE);
	i2c_write(DataRegisterBegin); //set pointer to X-axis MSB		 #define DataRegisterBegin 0x03
	i2c_stop();
	
	i2c_start(HMC5883L_READ);
	uint8_t i;
	for(i = 0; i<length-1; i++){
		buffer[i] = i2c_readAck();
	}
	buffer[i] = i2c_readNak();
	i2c_stop();
}

void Compass_ReadRawAxis(int * Mag_Raw){
	uint8_t buffer[6];
	Read_Compass(buffer, 6);
	*(Mag_Raw) = (buffer[0] << 8) | buffer[1]; //x
	*(Mag_Raw+1) = (buffer[2] << 8) | buffer[3]; //y
	*(Mag_Raw+2) = (buffer[4] << 8) | buffer[5]; //z
}

void Compass_ReadScaledAxis(float * Mag_Scaled){
	int Mag_Raw[3];
	Compass_ReadRawAxis(&Mag_Raw);
	*(Mag_Scaled) = Mag_Raw[0] * m_Scale; //x
	*(Mag_Scaled+1) = Mag_Raw[1] * m_Scale; //y
	*(Mag_Scaled+2) = Mag_Raw[2] * m_Scale; //z
}




#endif /* MAGNETOMETER_HMC5883L_H_ */