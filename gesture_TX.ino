int xPin=0;//Connect x pin of adxl335 to pin A0
int yPin=1;//Connect y pin of adxl335 to pin A1


int ledPin=13;//led on pin 13 is ON except when transmitter is parallel to the ground


#include <VirtualWire.h>


void setup() 
{
  vw_setup(2000);//Bits per second
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);//Initialise the serial connection debugging
}

void loop() 
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  
  Serial.print("xval=");
  Serial.println(xval);
  
  Serial.print("yval=");
  Serial.println(yval); 
  
  delay(1000); //used to display values after 1s delay
  
  Serial.print("\n");
  
  if ((xval>330 && xval<340) && (yval>340 && yval<350)) //stationary or stop(transmitter parallel to ground)
  {
    digitalWrite(ledPin,LOW);
    send("s");
  } 
  else 
  { 
    if ((xval>375 && xval<385) && (yval>335 && yval<345)) //forward(transmitter tilted forward)
    {
      digitalWrite(ledPin,HIGH);
      send("f");
      
    }
    if ((xval>300 && xval<310) && (yval>350 && yval<360)) //backward(transmitter tilted backward)
    {
      digitalWrite(ledPin,HIGH);
      send("a");
      
    }
    if ((xval>290 && xval<300) && (yval>275 && yval<285)) //left(transmitter tilted to left)
    {
      digitalWrite(ledPin,HIGH);
      send("l");
     }
     if ((xval>315 && xval<325) && (yval>385 && yval<395))//right(transmitter tilted to right)
    {
      digitalWrite(ledPin,HIGH);
      send("r");
      
    }
  }
  delay(1000);
  
}


void send(char *message)//send function definition
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
