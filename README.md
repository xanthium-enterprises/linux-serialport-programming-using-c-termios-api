# Linux Serial Port Programming Tutorial using C Language and termios API

- In this repo ,You will find code for programming the serial port of your Linux distribution(Ubuntu,Fedora,Arch,Linux Mint) using C language.
- We will also Learn to perform Bi-Directional Serial Communication between a Linux PC and an Arduino UNO
- Here we will be using the native API's provided by the Linux System like the
  - **termios** structure.
  - **read()** system call
  - **write()** system call
-  to configure the serial port of our linux system.
-  Code is written in **Pure C** language and compiled using **GCC**.

 ![Screenshot of serial port programming in linux using C](docs/arduino-ubuntu-serial-communication.jpg)


## Online Tutorial
A detailed writeup of the Linux serial Port Programming tutorial can be found using the below link 
- [Linux Serial Port Programming tutorial for the Absolute Beginner](https://www.xanthium.in/native-serial-port-communication-arduino-micro-linux-unix-bsd-system-c-lang-terminos-api)
- 

  


## Hardware Connections
 ![hardware connections for serial communication between arduino uno board and arch linux laptop using C/C++](docs/linux-arduino-serial-port-communication-in-c.jpg)
 
 
 The above image shows how to connect the Arduino board with the Linux PC for Serial Communication.

 ![connecting microcontroller to linux serial port using c language](docs/linux-arduino-serialport-comm.jpg)
 

 The above image shows how to interface bare microcontrollers like 8051,ATmega328P,MSP430 with linux serial port using a [USB to Serial Converter](https://www.xanthium.in/USB-to-Serial-RS232-RS485-Converter).

## Compiling the Code.

The Code can be compiled using GCC on any modern Linux Systems.

`gcc serial_port_code.c -o serial_port_code`

Code tested on 

- `OS       :Fedora Linux 42 (Workstation Edition) x86_64`
- `Kernel   :Linux 6.14.9-300.fc42.x86_64`
- `Compiler :gcc (GCC) 15.1.1 20250521 (Red Hat 15.1.1-2)`

- `OS       : Ubuntu 24.04.2 LTS x86_64`
- `Kernel   : 6.11.0-26-generic` 
- `Compiler :gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0`

## Screen shots
![reading data from linux serial port using C](docs/arduino-ubuntu-serial-communication.jpg)







