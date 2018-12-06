//Libraries

#include <Servo.h> 
#include "Ultrasonic.h"

//Constants
const int button = 2;  

//motor A positive (+) pin to pin 6 (PWM) (from L298 module!)    
const int motorA1 = 6;  
   
//motor A negative (-) pin to pin 9 (PWM) 
const int motorA2= 9;  

//motor B positive (+) pin to pin 10 (PWM)       
const int motorB1=10; 

//motor B negative (-) pin to pin 11 (PWM)    
const int motorB2=11;     

//Create Ultrsonic object ultrasonic(trig pin,echo pin)
Ultrasonic ultrasonic(A4 ,A5); 

//Create Servo object to control a servo
Servo myservo;          

/*    variables
***************************/

//Variable to store distance from an object
int distance;        

int checkRight;
int checkLeft;
int function = 0;  

//Variable to store the state of the button. By default '0'       
int buttonState=0; 

//Variable to store the servo position. By default 90 degrees. sensor will 'look' forward           
int pos=90;       

//Useful flag to keep the button state when button is released       
int flag=0;           


void setup()
{
  myservo.attach(5);      
  myservo.write(pos);        
  pinMode(button, INPUT_PULLUP);
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  
}

void loop()
{
  //Check button state
  buttonState = digitalRead(button);
  unsigned long currentMillis = millis(); //counting...

    //Change main function (stoped/running) when button is pressed
   
    if (buttonState == LOW)  //If button is pressed once...
    {                         
      delay(500);
      
      if ( flag == 0)
      {
          function = 1;
          flag=1;             //change flag variable
      }
      else if ( flag == 1)    //If button is pressed twice
      {                       
        function = 0;
        flag=0;               //change flag variable again 
      }    
    }
    
  if (function == 0)  //If button is unpressed or pressed twice then:
  {                 
    //set servo 90 degress - sensor will look forward
    myservo.write(90);    
    stop();         //robot remain stoped
        
  }
  else if (function == 1)  //If button is pressed then:
  {
    //Read distance...
    distance = ultrasonic.Ranging(CM); //Tip: Use 'CM' for centimeters 
                                       //or 'INC' for inches
    
    //Check for objects...
    if (distance > 10)
      forward();
       
    else if (distance <=10)
    {
      stop(); //Object detected! Stop the robot and check left and right
              //for the better way out!
      
      //Start scanning... 
      for(pos = 0; pos < 180; pos += 1)
      {   
          //tell servo to go to position in variable 'pos' 
          myservo.write(pos); 
          
          //waits 10ms for the servo to reach the position             
          delay(10);                      
      } 
    
          
    checkLeft = ultrasonic.Ranging(CM);   
    for(pos = 180; pos>=0; pos-=1)
    {                               
          myservo.write(pos);             
          delay(10);                      
     }
            
     checkRight= ultrasonic.Ranging(CM);
            
     myservo.write(90);              
            
     //Finally, take the right decision, turn left or right?
     if (checkLeft < checkRight)
     {
        left();
        delay(400);
     }
     else if (checkLeft > checkRight)
     {
         right();
         delay(400); 
     }
     else if (checkLeft <=10 && checkRight <=10)  //The road is closed... go back and then left ;)
     {
              backward(); 
              left();
     }
    }
  }
}


void forward()
{
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void backward()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left()
{
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void stop()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
