/*
   Basic Code to Open a Serial port on Linux using C and termios API
   (c) wwww.xanthium.in (2025)

   Please Remember to change Serial Port Name Before  Running the Code.

   Compiler : gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
   OS       : Ubuntu 24.04.2 LTS x86_64 
   Kernel   : 6.11.0-26-generic 

   Compile  : gcc serial_open.c -o serial_open
   
*/

#include <stdio.h>  
#include <fcntl.h>    /* file open flags and open() */
#include <termios.h>
#include <unistd.h>   /* close() */

int main() 
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY); // open a connection to serialport
                                                      // Please use the name of your SerialPort 
                                                      // instead of /dev/ttyACM0
    if (fd == -1) 
    {
        perror("Failed to open serial port"); /*  to print system error messages */
        return 1;                             /* for failure return 1            */
    }
    else
    {
       printf("Connection to Port Opened fd = %d \n",fd);
    }

    close(fd);  /* Close the file descriptor*/ 

    return 0;
}
