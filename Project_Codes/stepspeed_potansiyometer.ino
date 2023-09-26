#include <ezButton.h>

const int Dir_1  = 9;
const int Pul_1  = 8;
const int Dir_2  = 11;
const int Pul_2  = 10;
   
int buttonState = LOW ;
ezButton buttonPin(12);

int delay_;
  
void setup(){

  buttonPin.setDebounceTime(50); // set debounce time to 50 milliseconds

  pinMode(Pul_1 , OUTPUT);
  pinMode(Dir_1 , OUTPUT);
  pinMode(Pul_2 , OUTPUT);
  pinMode(Dir_2 , OUTPUT);

  delay(100);
  Serial.begin(9600);
  }

void loop() {
  
  buttonPin.loop();
  buttonState = buttonPin.getState();
  
  if (buttonState == HIGH)
  { 
      digitalWrite(Dir_1, HIGH);
      digitalWrite(Dir_2, LOW);
      while(1)
      {
        int val = analogRead(A0);
        delay_ = map(val, 0, 1023, 1, 600);
        //Serial.println(delay_);
        digitalWrite(Pul_1, HIGH);
        delayMicroseconds(delay_);
        digitalWrite(Pul_1, LOW);
        delayMicroseconds(delay_);
        digitalWrite(Pul_2, HIGH);
        delayMicroseconds(delay_);
        digitalWrite(Pul_2, LOW);
        delayMicroseconds(delay_);

        buttonPin.loop();
        buttonState = buttonPin.getState();
        
        if (buttonState == LOW)
        {
          break;
        }
      }
      delay(100);
  }
}
