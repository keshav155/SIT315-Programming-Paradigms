// Code partially taken from https://www.bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/

int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;  
const byte interruptPin = 2;


void setup()
{
  pinMode(11, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), turnOffLED, CHANGE);
  Serial.begin(9600);                      
}

// Turn off led for a brief period of time

void turnOffLED(){
	digitalWrite(11,LOW);
    delay(1000);
}

void loop()
{
  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 
  
// LED will be on if temp is greater than 30
  
  if(temp>30){
    digitalWrite(11,HIGH);
  }
  else
  {
    digitalWrite(11,LOW);
  }
}
  