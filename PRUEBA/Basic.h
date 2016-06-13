
#ifndef BASIC_H_
#define BASIC_H_

#define F_CPU 16000000L // Frecuencia de Reloj del Arduino 1 y Mega 2560
#define PI 3.14159265

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define TRUE 0x1
#define FALSE 0x0
typedef uint8_t BYTE;
typedef uint8_t BOOL;

#define _BV(bit) (1 << bit)
#define cbi(port,bit) (port) &= ~(1 << (bit))
#define sbi(port,bit) (port) |= (1 << (bit))


#endif /* BASIC_H_ */