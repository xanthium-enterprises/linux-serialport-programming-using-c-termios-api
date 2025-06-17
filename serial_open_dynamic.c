/*
   Basic Code to Open a Serial port on Linux using C and termios API
   Verbose mode with ability to get serial port name.

   (c) www.xanthium.in (2025)

   Please Remember to change Serial Port Name Before  Running the Code.

   Compiler : gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
   OS       : Ubuntu 24.04.2 LTS x86_64 
   Kernel   : 6.11.0-26-generic 

   Compile  : gcc serial_open_dynamic.c -o serial_open_dynamic
   Run      : ./serial_open_dynamic
   
*/


#include <stdlib.h>   /* system() */
#include <stdio.h>  
#include <fcntl.h>    /* file open flags and open() */
#include <termios.h>
#include <unistd.h>   /* close() */
#include <string.h>

int main() 
{
    
    char serial_port_name[20] = {};

    printf("\n listing available serial ports \n");
    printf("+------------------------------+\n");

    system("ls  /dev/ttyUSB* /dev/ttyACM* 2>/dev/null"); // running ls command to list serial ports

    
    printf("\nEnter the serial port device (e.g., /dev/ttyUSB0): ");

    fgets(serial_port_name,sizeof(serial_port_name),stdin); // read data from command line(stdin) to array
                                                            // eg /dev/ttyACM0\n due to pressing enter 
    int location_n = strcspn(serial_port_name, "\n");       // get the location of \n 

    serial_port_name[location_n] = '\0';                    //replace \n with \0 




    int fd = open(serial_port_name, O_RDWR | O_NOCTTY); // open a connection to serialport
                                                      // Please use the name of your SerialPort 
                                                      // instead of /dev/ttyACM0
    if (fd == -1) 
    {
        perror("Failed to open serial port\n\n"); /*  to print system error messages */
        return 1;                                 /* for failure return 1            */
    }
    else
    {
       printf("Connection to Port %s Opened fd = %d \n\n",serial_port_name,fd);
    }

    close(fd);  /* Close the file descriptor*/ 

    return 0;
}