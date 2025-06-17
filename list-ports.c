
// Program to run system commands using c program
// Program will list the serial ports 

#include <stdlib.h>

void main() 
{
	system("ls  /dev/ttyUSB* /dev/ttyACM* 2>/dev/null"); // running ls command to list serial ports
	                                                     //2 refers to file descriptor 2, which is the standard error (stderr) 
														 //2>/dev/null
	                                                     //redirecting errors to /dev/null so they dont appear on the terminal
}