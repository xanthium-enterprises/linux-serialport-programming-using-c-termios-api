/*
   Code to configure termios structure in Linux using C 
   (c) wwww.xanthium.in (2025)

   Please Remember to change Serial Port Name Before  Running the Code.

   Compiler : gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
   OS       : Ubuntu 24.04.2 LTS x86_64 
   Kernel   : 6.11.0-26-generic 

   Compile  : gcc serialport_config.c -o serialport_config
   Run      : ./serialport_config

*/

#include <stdio.h>  
#include <fcntl.h>    /* file open flags and open()         */
#include <termios.h>  /* POSIX Terminal Control Definitions */
#include <unistd.h>   /* UNIX Standard Definitions          */
#include <errno.h>    /* ERROR Number Definitions           */

int main() 
{
    struct termios serial_port_settings;

    char serial_read_buffer[100] = {};


    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY); //open a connection to serialport

    
    if (fd == -1) 
    {
        perror("Failed to open serial port"); /*  to print system error messages */
        return 1;
    }
    else
    {
       printf("Connection to Port Opened fd = %d \n",fd);
    }

   tcgetattr(fd, &serial_port_settings); // get the serial port settings from the termios structure
   
   cfsetispeed(&serial_port_settings,B9600); //Set input Baudrate 
   cfsetospeed(&serial_port_settings,B9600); //Set output Baudrate 

   

   serial_port_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable NON CANONICAL Mode for Serial Port Comm
   serial_port_settings.c_iflag &= ~(IXON | IXOFF | IXANY);         // Turn OFF software based flow control (XON/XOFF).
   serial_port_settings.c_cflag &= ~CRTSCTS;                        // Turn OFF Hardware based flow control RTS/CTS 
   
   serial_port_settings.c_cflag |=  CREAD | CLOCAL;         // Turn ON  the receiver of the serial port (CREAD)
  

    // Set 8N1 (8 bits, no parity, 1 stop bit)
   serial_port_settings.c_cflag &= ~PARENB;      // No parity
   serial_port_settings.c_cflag &= ~CSTOPB;      // One stop bit
   serial_port_settings.c_cflag &= ~CSIZE;       // Clear the CSIZE so we can set databits later
   serial_port_settings.c_cflag |=  CS8;         // 8 bits




   tcsetattr(fd,TCSANOW,&serial_port_settings);  // update new settings to termios structure,
                                                 // TCSANOW tells to make the changes now without waiting

   //Display Baudrate 
   tcgetattr(fd, &serial_port_settings); // get the serial port settings from the termios structure

   speed_t input_baudrate  = cfgetispeed(&serial_port_settings); //Get input baud rate 
   speed_t output_baudrate = cfgetospeed(&serial_port_settings); //Get output baud rate 

   //use switch to compare and get correct baudrate in int
   switch(input_baudrate)
   {
      case B4800:  printf("input_baudrate = 4800\n");break;
      case B9600:  printf("input_baudrate = 9600\n");break;
      case B19200: printf("input_baudrate = 19200\n");break;   
   }

  
   close(fd);  /* Close the file descriptor*/ 
}
