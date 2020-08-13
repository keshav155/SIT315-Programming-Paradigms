// Code partially taken from https://www.bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/

int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;  

void setup()
{
  pinMode(4, OUTPUT);
  Serial.begin(9600);                      
}

void loop()
{
  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 
 
  Serial.print("Current Temperature: ");
  Serial.println(temp);
  
  // Blink the LED
  
  if(temp>30){
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
  }
}