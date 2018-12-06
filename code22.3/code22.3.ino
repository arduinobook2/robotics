/* WE have done many projects using servo library before. 
 * As a result there will be no comment in code.
 
****** Welcome to the world of problem solving *******/ 

#include <Servo.h>

Servo myservo1; 
Servo myservo2;

int pos = 0;    

void setup()
{
  myservo1.attach(10); 
  myservo2.attach(9);  
   
}

void loop() 
{ 
  for (pos = 60; pos <= 173; pos += 1) 
  {  
    myservo1.write(pos);
    delay(15);                       
  }
  delay(200);

  for (pos = 180; pos >= 90; pos -= 1) 
  { 
    myservo2.write(pos);              
    delay(15);                       
  }
  
  delay(200);
 
  for (pos = 173; pos >= 60; pos -= 3) 
  { 
    myservo1.write(pos);              
    delay(15);                       
  }
  
  delay(500);

 for (pos = 90; pos <= 180; pos += 3)
 { 
    myservo2.write(pos);             
    delay(15);                     
 }
  
  delay(500);
}
