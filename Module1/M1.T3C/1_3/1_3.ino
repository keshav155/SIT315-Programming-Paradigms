// Code partially taken from https://www.bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/

int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;  
const byte interruptPin = 2;
int distanceThreshold = 0;
int cm = 0;
int inches = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

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
    Serial.println("LED interrupted for 1 second");
}

void loop()
{
  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 
  distanceThreshold = 50;
  cm = 0.01723 * readUltrasonicDistance(7, 6);
// LED will be on if temp is greater than 30 or distance from object is less than 50cm
  
  if(temp>30 || cm < distanceThreshold ){
    digitalWrite(11,HIGH);
  }
  else
  {
    digitalWrite(11,LOW);
  }
}
  
