#include <avr/io.h>

#include "I2C_Master.h"
#include "Serial.h"
#include "Magnetometer_HMC5883L.h"
#include "Accelerometer_ADXL345.h"

int Mag_Raw[3];
//int Acce_Raw[3];
float Mag_Scaled[3];

int main(void){
	Serial_begin(9600);
	i2c_init();
	init_HMC5883L();
	//init_Accelerometer();
	while(1){
		//compass_offset_calibration(3); //1 o 2 o 3(ambos)
		Compass_ReadRawAxis(&Mag_Raw);
		//Compass_Scalled_Reading(&Mag_Scaled);
		//readAccel(&Acce_Raw);
		/*Serial_write("  x: ");	TxBCD(Mag_Raw[0]);
		//Serial_write("  y: ");	TxBCD(Mag_Raw[1]);
		//Serial_write("  z: ");	TxBCD(Mag_Raw[2]);
		Compass_ReadScaledAxis(&Mag_Scaled);
		Serial_write("          x: ");	TxBCD(Mag_Scaled[0]);
		Serial_write("  y: ");	TxBCD(Mag_Scaled[1]);
		Serial_write("  z: ");	TxBCD(Mag_Scaled[2]);
		int headingDegrees = atan2((double)Mag_Scaled[1],(double)Mag_Scaled[0])* 180/PI + 180;
		Serial_write("       heading: ");	TxBCD(headingDegrees);
		Serial_write("\n\r");	*/
		/*Serial_write("  x: ");	TxBCD(Acce_Raw[0]);
		Serial_write("  y: ");	TxBCD(Acce_Raw[1]);
		Serial_write("  z: ");	TxBCD(Acce_Raw[2]);*/
	}
}