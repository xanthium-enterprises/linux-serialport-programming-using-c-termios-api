
void setup() 
{
  Serial.begin(9600); // Start serial communication at 9600 baud
 
  while (!Serial) { ; } // Wait for serial port to connect (for Leonardo/Micro/Zero)

}

void loop() 
{
   if (Serial.available() > 0) 
   {
    
    char ReceivedChar = Serial.read();//Read data in the Buffer

    switch(ReceivedChar)
    {
      case 'A' : Serial.println("Character A  Received OK");break;
      case 'B' : Serial.println("Character B  Received OK");break;
      case 'C' : Serial.println("Character C  Received OK");break;
      default  : Serial.println("Invalid Character Received");
      
    }
    delay(500);
    
   }
}
