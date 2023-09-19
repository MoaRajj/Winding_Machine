#include <ezButton.h>

const int ledPin =  11;
const int ledPin1 =  13;
const int ledPin2 =  12;
const int ledPin3 =  2;

const int Dir_x  = 8;
const int Pul_x  = 9;
   
int buttonState = LOW ;
ezButton buttonPin(7); 

int buttonState1 = LOW ; 
ezButton buttonPin1(6);

int buttonState2 = LOW ; 
ezButton buttonPin2(5);

int buttonState3 = LOW ;
ezButton buttonPin3(4);

int buttonState4 = LOW ;
ezButton limitswitch1(3);

int buttonState5 = LOW ;
ezButton limitswitch2(10);

long motor_rev=0;
long decrease_ = 1;
long previousMillis = 0;
int delay_speed;
int delay_x = 20;
int max_speed; 
int direction_ = HIGH;

int get_speed(int d1, int d2, int d3)
{
  if(d1 == HIGH && d2 == HIGH && d3 == HIGH){
  max_speed = 150 ;
  }
  else if(d1 == HIGH && d2 == HIGH && d3 == LOW){
  max_speed = 200 ; 
  }
  else if(d1 == HIGH && d2 == LOW && d3 == LOW){
  max_speed = 250 ; 
  }
  else{
    max_speed = 370 ; 
    }
  return max_speed;
}

int get_delay(int d1, int d2, int d3)
{
  if(d1 == HIGH && d2 == HIGH && d3 == HIGH){
  delay_speed = 200 ;
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  }
  else if(d1 == HIGH && d2 == HIGH && d3 == LOW){
  delay_speed = 250 ; 
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, LOW);
  }
  else if(d1 == HIGH && d2 == LOW && d3 == LOW){
  delay_speed = 300 ;
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  }
  else{
    delay_speed = 380 ; 
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    }
  return delay_speed;
}
 


  
void setup(){

  buttonPin.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonPin1.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonPin2.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonPin3.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitswitch1.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitswitch2.setDebounceTime(50); // set debounce time to 50 milliseconds

  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(Pul_x , OUTPUT);
  pinMode(Dir_x , OUTPUT);

  delay(100);
  Serial.begin(9600);
  }

void loop() {
  
  buttonPin.loop();
  buttonState = buttonPin.getState();

  buttonPin1.loop();
  buttonPin2.loop();
  buttonPin3.loop();
  buttonState1 = buttonPin1.getState();
  buttonState2 = buttonPin2.getState();
  buttonState3 = buttonPin3.getState();
  
  if (buttonState == HIGH)
  { 
      digitalWrite(ledPin, HIGH);
      // High --> Right // Low --> Left

      
      max_speed = get_speed(buttonState1,buttonState2,buttonState3) ; 
      //Serial.println("..");
      delay_speed = get_delay(buttonState1,buttonState2,buttonState3) ; 
      //motor_rev = 0;
      previousMillis = 0;
      digitalWrite(Dir_x, direction_);
      while(1)
      {
        motor_rev= motor_rev+1 ;
        unsigned long currentMillis = millis();
        digitalWrite(Pul_x, HIGH);
        delayMicroseconds(delay_speed);
        digitalWrite(Pul_x, LOW);
        delayMicroseconds(delay_speed);

        buttonPin1.loop();
        buttonPin2.loop();
        buttonPin3.loop();
        buttonPin.loop();
        buttonState = buttonPin.getState();
        limitswitch1.loop();
        limitswitch2.loop();
        
        if ( currentMillis  - previousMillis > delay_x )
        {
          previousMillis = currentMillis ;
          if ( delay_speed > max_speed)
          {
            delay_speed = delay_speed - decrease_ ;
          }
          else{delay_speed = max_speed ;}
        }
        if (buttonState == LOW)
        {
          break;
        }
        if (buttonPin1.isPressed())
        {
          break;
        }
        if (buttonPin1.isReleased())
        {
          break;
        }
        if (buttonPin2.isPressed())
        {
          break;
        }
        if (buttonPin2.isReleased())
        {
          break;
        }
        if (buttonPin3.isPressed())
        {
          break;
        }
        if (buttonPin3.isReleased())
        {
          break;
        }
        if (limitswitch1.isPressed())
        {
          direction_ = HIGH;
          motor_rev= 0;
          break;
        }
        if (limitswitch2.isPressed())
        {
          direction_ = LOW;
          motor_rev= 0;
          break;
        }
        if ( motor_rev > 27000)
        {
            break;
        }       
      }
      delay(100);
  }
  else{
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
    }
  
}
