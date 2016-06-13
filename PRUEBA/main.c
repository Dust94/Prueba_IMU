#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

#include "I2C_Master.h"
//#include "Serial.h"
#include "Magnetometer_HMC5883L.h"
#include "Accelerometer_ADXL345.h"
#include "uart.h"

int Mag_Raw[3];
//int Acce_Raw[3];
float Mag_Scaled[3];
int headingDegrees;

int main(void){
	//Serial_begin(9600);
	uart_init(0);
	i2c_init();
	init_HMC5883L();
	//init_Accelerometer();
	Compass_ReadRawAxis(&Mag_Raw);
	
	/*
	Serial_write("  x: ");	TxBCD(Mag_Raw[0]);
	Serial_write("  y: ");	TxBCD(Mag_Raw[1]);
	Serial_write("  z: ");	TxBCD(Mag_Raw[2]);  Serial_write("\n\r");
	*/
	char xs[10], ys[10], zs[10];
	itoa(Mag_Raw[0], xs,10); itoa(Mag_Raw[1], ys, 10); itoa(Mag_Raw[2], zs, 10);
	
	uart_print(0,"  x: ");	uart_print(0, xs);
	uart_print(0,"  y: ");	uart_print(0, ys);
	uart_print(0,"  z: ");	uart_println(0, zs);

	char bufiiii[10];
	compass_offset_calibration(3); //1, 2 o 3(ambos)
	while(1){
		Compass_Scalled_Reading(&Mag_Scaled);
		//Compass_ReadScaledAxis(&Mag_Scaled);
		//xs[10], ys[10], zs[10];
		itoa(Mag_Scaled[0], xs,10); itoa(Mag_Scaled[1], ys, 10); itoa(Mag_Scaled[2], zs, 10);
		
		uart_print(0,"  x: ");	uart_print(0, xs);
		uart_print(0,"  y: ");	uart_print(0, ys);
		uart_print(0,"  z: ");	uart_print(0, zs);
		//uart_println(0," ");
		headingDegrees = compass_heading();
		//int headingDegrees = atan2(Mag_Scaled[1],Mag_Scaled[0])* 180/PI + 180;
		uart_print(0, "    ");  uart_println(0,itoa(headingDegrees, bufiiii, 10)); 
		/*
		Serial_write("  x: ");	TxBCD(Mag_Scaled[0]);
		Serial_write("  y: ");	TxBCD(Mag_Scaled[1]);
		Serial_write("  z: ");	TxBCD(Mag_Scaled[2]);
		Serial_write("       heading: ");	TxBCD(headingDegrees);
		Serial_write("\n\r");
		*/
		/*Serial_write("  x: ");	TxBCD(Mag_Raw[0]);
		//Serial_write("  y: ");	TxBCD(Mag_Raw[1]);
		//Serial_write("  z: ");	TxBCD(Mag_Raw[2]);
		Compass_ReadScaledAxis(&Mag_Scaled);
		Serial_write("          x: ");	TxBCD(Mag_Scaled[0]);
		Serial_write("  y: ");	TxBCD(Mag_Scaled[1]);
		Serial_write("  z: ");	TxBCD(Mag_Scaled[2]);
		int headingDegrees = atan2((double)Mag_Scaled[1],(double)Mag_Scaled[0])* 180/PI + 180;`
		Serial_write("       heading: ");	TxBCD(headingDegrees);
		Serial_write("\n\r");	*/
		/*Serial_write("  x: ");	TxBCD(Acce_Raw[0]);
		Serial_write("  y: ");	TxBCD(Acce_Raw[1]);
		Serial_write("  z: ");	TxBCD(Acce_Raw[2]);*/
	} // Fin while
}