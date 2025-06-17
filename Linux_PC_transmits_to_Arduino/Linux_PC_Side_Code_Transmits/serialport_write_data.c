/*
   Basic Code to Send data to Arduino from Linux using a Serial port in C and termios API
   Send a charcter to Arduino
   (c) wwww.xanthium.in

*/

#include <fcntl.h>    /* file open flags and open() */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{

   struct termios serial_port_settings;

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

   sleep(3);  // Delay for 3 seconds,for Arduino to get stabilized,
              // Opening the port resets the Arduino

   tcgetattr(fd, &serial_port_settings); // get the serial port settings from the termios structure


   /*****************     Configure the Baudrate       *******************/
   cfsetispeed(&serial_port_settings,B9600); //Set input Baudrate 
   cfsetospeed(&serial_port_settings,B9600); //Set output Baudrate 


   /*****************     Configure the termios structure   ************************/

   
   serial_port_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable NON CANONICAL Mode for Serial Port Comm
   serial_port_settings.c_iflag &= ~(IXON | IXOFF | IXANY);         // Turn OFF software based flow control (XON/XOFF).
   
   serial_port_settings.c_cflag |=  CREAD | CLOCAL;         // Turn ON  the receiver of the serial port (CREAD)
   serial_port_settings.c_cflag &= ~CRTSCTS;                // Turn OFF Hardware based flow control RTS/CTS 

    // Set 8N1 (8 bits, no parity, 1 stop bit)
   serial_port_settings.c_cflag &= ~PARENB;      // No parity
   serial_port_settings.c_cflag &= ~CSTOPB;      // One stop bit
   serial_port_settings.c_cflag &= ~CSIZE;       
   serial_port_settings.c_cflag |=  CS8;          // 8 bits




   tcsetattr(fd,TCSANOW,&serial_port_settings);  // update new settings to termios structure,
                                                // TCSANOW tells to make the changes now without waiting

   /**/

   /* Flush both input and output buffers to clear out garbage values */

   if (tcflush(fd, TCIOFLUSH) != 0)
   {
      perror("tcflush");
   }

   char value_to_send = 'A'; /* single quotes,stores the ASCII value of A (65)*/

   int bytes_written = write(fd,&value_to_send,sizeof(value_to_send));

   printf(" %d" ,bytes_written);




   close(fd);  /* Close the file descriptor*/ 
}