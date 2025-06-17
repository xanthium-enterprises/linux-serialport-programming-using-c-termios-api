//Skeleton code for reading from serial port in C using termios.
//Full code available in github.

#include <fcntl.h>    /* file open flags and open() */
#include <termios.h>
#include <unistd.h>   /* close() */
#include <stdio.h>
#include <stdlib.h>

int main() 
{

   struct termios serial_port_settings;

   char serial_read_buffer[100] = {}; //Data read from port stored in this array
   

   int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY); //open a connection to serialport
    
    
   sleep(3);  // Delay for 3 seconds,for Arduino to get stabilized,
              // Opening the port resets the Arduino

   
   int status = tcgetattr(fd, &serial_port_settings); // get the serial port settings from the termios structure

   
   /*****************     Configure the Baudrate       *******************/
   cfsetispeed(&serial_port_settings,B9600); //Set input Baudrate 
   cfsetospeed(&serial_port_settings,B9600); //Set output Baudrate 


   /*****************     Configure the termios structure   ************************/

   

   serial_port_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable NON CANONICAL Mode for Serial Port Comm
   serial_port_settings.c_iflag &= ~(IXON | IXOFF | IXANY);         // Turn OFF software based flow control (XON/XOFF).
   serial_port_settings.c_cflag &= ~CRTSCTS;                        // Turn OFF Hardware based flow control RTS/CTS 
   
   serial_port_settings.c_cflag |=  CREAD | CLOCAL;         // Turn ON  the receiver of the serial port (CREAD)
   

    // Set 8N1 (8 bits, no parity, 1 stop bit)
   serial_port_settings.c_cflag &= ~PARENB;      // No parity
   serial_port_settings.c_cflag &= ~CSTOPB;      // One stop bit
   serial_port_settings.c_cflag &= ~CSIZE;       
   serial_port_settings.c_cflag |=  CS8;          // 8 bits

   serial_port_settings.c_oflag &= ~OPOST;/*No Output Processing*/
   
   serial_port_settings.c_cc[VMIN]  = 20; /* Read at least 20 characters */  
   serial_port_settings.c_cc[VTIME] = 10; /* Wait for 10 *100ms = 1 second ,measured in increments of 100ms */



   status = tcsetattr(fd,TCSANOW,&serial_port_settings);  // update new settings to termios structure,
                                                          // TCSANOW tells to make the changes now without waiting

   

   /* Flush both input and output buffers to clear out garbage values */

   if (tcflush(fd, TCIOFLUSH) != 0)
   {
      perror("tcflush");
   }

   int received_bytes = read(fd,serial_read_buffer, sizeof(serial_read_buffer)-1);

   printf("\n\nBytes Received from Serial Port = %d ",received_bytes);
   printf("\n\nData Received from Serial Port  = %s\n",serial_read_buffer );

   close(fd);  /* Close the file descriptor*/ 
}