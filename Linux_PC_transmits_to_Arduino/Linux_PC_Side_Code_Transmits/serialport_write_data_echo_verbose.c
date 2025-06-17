/*
   Bi Directional Serial Communication between Arduino and Linux PC using C language
   Verbose Mode 

   Linux PC sends a character 'A' to Arduino using serial port
   Arduino Receives character and echoes back a reply "Character A Received OK" 

   Please Remember to change Serial Port Name Before  Running the Code.

   (c) wwww.xanthium.in (2025)

*/


#include <fcntl.h>    /* file open flags and open() */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{

   struct termios serial_port_settings;
   char serial_port_name[20]    = {}; // Array to store serial port name 

   /****************** List Available Ports *****************/

   printf("\n+--------------------------------------------------+");
   printf("\n| Linux Serial Port Programming in C (termios API) |  ");
   printf("\n| (c) www.xanthium.in (2025)                       |  ");
   printf("\n+--------------------------------------------------+");
   printf("\n[Bi-Directional Communication with Arduino (Read/Write)]");

   printf("\n\n listing available serial ports \n");
   printf("+------------------------------------+\n");

    system("ls  /dev/ttyUSB* /dev/ttyACM* 2>/dev/null"); // running ls command to list serial ports

    printf("+------------------------------------+\n");

    printf("\nEnter the serial port device (e.g., /dev/ttyUSB0)-> ");

    fgets(serial_port_name,sizeof(serial_port_name),stdin); // read data from command line(stdin) to array
                                                            // eg /dev/ttyACM0\n due to pressing enter 
    int location_n = strcspn(serial_port_name, "\n");       // get the location of \n 

    serial_port_name[location_n] = '\0';                    //replace \n with \0 

   int fd = open(serial_port_name, O_RDWR | O_NOCTTY); //open a connection to serialport
    
      if (fd == -1) 
      {
         perror("\nFailed to open serial port"); /*  to print system error messages */
         return 1;
      }
      else
      {
         printf("\nConnection to Port %s Opened fd = %d \n",serial_port_name,fd);
      }

   printf("\nDelay for 3 seconds,for Arduino to get stabilized\n");
   sleep(3);  // Delay for 3 seconds,for Arduino to get stabilized,
              // Opening the port resets the Arduino

   int status = tcgetattr(fd, &serial_port_settings); // get the serial port settings from the termios structure

   if(status == -1)
   {
      perror("\nFailed to get termios structure"); /*  to print system error messages */
      close(fd);
      exit(1);
   }
   else
   {
      printf("\nSuccessfully retrieved current termios settings");
   }


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

   serial_port_settings.c_oflag &= ~OPOST;/*No Output Processing*/
   
   serial_port_settings.c_cc[VMIN]  = 25; /* Read at least 25 characters */  
   serial_port_settings.c_cc[VTIME] = 10; /* Wait for 10 *100ms = 1 second ,measured in increments of 100ms */


   status = tcsetattr(fd,TCSANOW,&serial_port_settings);  // update new settings to termios structure,
                                                // TCSANOW tells to make the changes now without waiting
   if(status == -1)
   {
      perror("\nFailed to update termios structure"); /*  to print system error messages */
      close(fd);
      exit(1);
   }
   else
   {
      printf("\nSuccessfully updated termios settings");
   }

   /**/

   /* Flush both input and output buffers to clear out garbage values */

   if (tcflush(fd, TCIOFLUSH) != 0)
   {
      perror("tcflush");
   }

   /*********  Write characters to the Serial Port using write()***************/

   char value_to_send = 'A'; /* single quotes,stores the ASCII value of A (65)*/

   int bytes_written = write(fd,&value_to_send,sizeof(value_to_send)); //Write data to Serial port 

   printf("\n\nCharacter Send       = %c" ,value_to_send);
   printf("\nNumber of Bytes Send = %d" ,bytes_written);


   /********* Read characters from Serial Port send by Arduino using read() ************/

   char serial_read_buffer[100] = {}; //Data read from port stored in this array
  
   int received_bytes = read(fd,serial_read_buffer, sizeof(serial_read_buffer)-1); //read data from the port

   printf("\n\nBytes Received from Serial Port = %d ",received_bytes);
   printf("\n\nData Received from Serial Port  = %s\n",serial_read_buffer );


   close(fd);  /* Close the file descriptor*/ 
}