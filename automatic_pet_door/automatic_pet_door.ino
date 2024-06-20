#include <Servo.h>

Servo servo;

const int lowerSensorTrigPin = 12;
const int lowerSensorEchoPin = 14;

const int upperSensorTrigPin = 15;
const int upperSensorEchoPin = 13;


int lowerSensorTriggerCount = 0;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(lowerSensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(lowerSensorEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(upperSensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(upperSensorEchoPin, INPUT); // Sets the echoPin as an Input
  servo.attach(5);
  servo.write(0);
  
}

int readLowerSensor(){
// Clears the trigPin
  digitalWrite(lowerSensorTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(lowerSensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(lowerSensorTrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(lowerSensorEchoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  

  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  return distanceCm;
}
int readUpperSensor(){
// Clears the trigPin
  digitalWrite(upperSensorTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(upperSensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(upperSensorTrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(upperSensorEchoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  

  
  // Prints the distance on the Serial Monitor
  Serial.print("Upper Sensor Distance (cm): ");
  Serial.println(distanceCm);
  return distanceCm;
}
void openDoor (){
  servo.write(150);
  while (readLowerSensor() < 40) {
   if( readLowerSensor() > 40) {
     break;
   }
  delay(100);
  }
  delay(5000);
  servo.write(0); // Return servo to 0 degrees
}

void loop() {
  if( readUpperSensor() > 90){
    if (readLowerSensor() < 40){
      lowerSensorTriggerCount++;
    } else {
      lowerSensorTriggerCount = 0;
    }
    if (readLowerSensor() < 40 && lowerSensorTriggerCount >= 4) {
      openDoor ();
      lowerSensorTriggerCount = 0;
    }
  }
  readUpperSensor();
  readLowerSensor();
  delay(250);
}