#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

#include "I2C_Master.h"
//#include "Serial.h"
#include "Magnetometer_HMC5883L.h"
#include "Accelerometer_ADXL345.h"
#include "uart.h"

int Mag_Raw[3];
float Mag_Scaled[3];
int Acce_Raw[3];

int main(void){
	//Serial_begin(9600);
	uart_init(0);
	i2c_init();
	init_HMC5883L();
	//init_Accelerometer();
	char xs[10], ys[10], zs[10], hedi[10];
	//compass_offset_calibration(3); //1, 2 o 3(ambos)
	while(1){
		Compass_ReadScaledAxis(&Mag_Scaled);
		itoa((int)Mag_Scaled[0], xs,10); itoa((int)Mag_Scaled[1], ys, 10); itoa((int)Mag_Scaled[2], zs, 10);	
		uart_print(0,"x: ");	uart_print(0, xs);
		uart_print(0,"mG  y: ");	uart_print(0, ys);
		uart_print(0,"mG  z: ");	uart_print(0, zs);
		float heading = atan2(Mag_Scaled[1],Mag_Scaled[0]) + PI;
		int headingDegrees = heading*(180/PI);		
		uart_print(0, "mG   heading: ");  uart_println(0,itoa(headingDegrees, hedi, 10)); 

	} // Fin while
}