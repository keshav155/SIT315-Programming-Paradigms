// Code partially taken from https://www.bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/
// Tutorial used in addition:- https://www.youtube.com/playlist?list=PLKL6KBeCnI3X7cb1sznYuyScUesOxS-kL

int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;  
const byte interruptPin = 2;
int distanceThreshold = 0;
int cm = 0;
int inches = 0;
int sensorState = 0;

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
  pinMode(11, INPUT);
  // For timer interrupt
  pinMode(7, OUTPUT);
  TCCR1A = 0b00000000; // set WGM bits to CTC
  TCCR1B = 0b00001101; // set CS bits to prescaler 1024
  OCR1A = 15624; // Set output compare register to interrupt every 1 second
  TIMSK1 = 0b0000010; //enable output compare match
  // For nomrla operations
  pinMode(8, OUTPUT);
  Serial.begin(9600);  
  PORTD = 0b11100000; // enable internal pullup on pin2
  PCICR = 0b00000100; // enable pin change interrupt 2 
  PCMSK2 = 0b01100000; // enable pin change interrupt 22 on pin 5 and 6 
  sei(); // enable interrupt globally
}

// Turn off led for a brief period of time
ISR(PCINT2_vect){
	digitalWrite(8,LOW);  
    delay(1000);
}


// Toggle LED on pin 7 (Timer interrupt)
ISR(TIMER1_COMPA_vect){
  PORTD ^= 0b10000000;
}

void loop()
{
  
  sensorState = digitalRead(11);
  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 
  distanceThreshold = 50;
  cm = 0.01723 * readUltrasonicDistance(13, 12);
// LED will be on if temp is greater than 30 or distance from object is less than 50cm
  
  if(temp>30 || cm < distanceThreshold || sensorState == HIGH  ){
    digitalWrite(8,HIGH);
  }
  else
  {
    digitalWrite(8,LOW);                     
  }
}