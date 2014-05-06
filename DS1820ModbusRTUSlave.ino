#include "ModbusSlave.h"
// for some misterious reason it has to be defined in the main file as well
#include <OneWire.h> 
#include <string.h>


/* Modbus RTU common parameters, the Master MUST use the same parameters */
enum {
        MB_SLAVE = 0x02,	/* modbus slave id */
};
/* slave registers example */
enum {        
        MB_REG0,
        MB_REG1,
        MB_REGS	 	/* total number of registers on slave */
};

int regs[MB_REGS];	/* this is the slave's modbus data map */

ModbusSlave  mb(Serial);

//
// MAIN SETUP
//

/* 
 * configure(slave, baud, parity, txenpin)
 *
 * sets the communication parameters for of the serial line.
 *
 * slave: identification number of the slave in the Modbus network (1 to 127)
 * baud: baudrate in bps (typical values 9600, 19200... 115200)
 * parity: a single character sets the parity mode (character frame format): 
 *         'n' no parity (8N1); 'e' even parity (8E1), 'o' for odd parity (8O1).
 * txenpin: arduino pin number that controls transmision/reception
 *        of an external half-duplex device (e.g. a RS485 interface chip).
 *        0 or 1 disables this function (for a two-device network)
 *        >2 for point-to-multipoint topology (e.g. several arduinos)
 *
 *   void configure(unsigned char slave, long baud, char parity, char txenpin);
 */

void setup(void) {
  mb.configure(DEFAULT_TX_PIN, DEFAULT_SLAVE_ADDR, 9600L, SERIAL_8N1);
  
  regs[MB_REG0] = 1234;
  regs[MB_REG1] = 5678;
}

void loop(void) {
   /* This is all for the Modbus slave */
   mb.update(regs, MB_REGS);
}

