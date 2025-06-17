void setup() 
{
  Serial.begin(9600); // Start serial communication at 9600 baud
 
  while (!Serial) { ; } // Wait for serial port to connect (for Leonardo/Micro/Zero)
}

void loop() 
{
  Serial.println("Hello from Arduino!"); // Send message to PC
  delay(1000); // Wait for 1 second
}