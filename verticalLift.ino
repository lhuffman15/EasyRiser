
/*//include libraries
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0, 1); //(Rx, Tx)
*/
//define pins
//inputs
const unsigned int buttonUp = 11; //connect to pull-up resistor: not pressed is HIGH, pressed is LOW
const unsigned int buttonDown = 10; //connect to pull-up resistor: not pressed is HIGH, pressed is LOW
int photoPin = A2;
//oututs
const unsigned int upPlus = 6; //4
const unsigned int downPlus = 5; //2
const unsigned int upMinus = 9; //3
const unsigned int downMinus = 3; //1

//define constants
const unsigned int baud = 9600;
const unsigned int stutterSpeed = 245;
const unsigned int upSpeed = 105;
const unsigned int downSpeed = 70;

//define variables
bool mode = 0; //set to Normal operation first; either Normal(N) or Reversed(R)
int serialIn;
bool buttonUpState = HIGH;
bool buttonDownState = HIGH;
bool stutterState = 0; //0 is calm, 1 is stuttering

//declare funtions
void motorUp();
void motorDown();
void motorStop();
bool checkResistor(int pin);

void setup() {
  //initialize inputs
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);

  //initialize outputs
  pinMode(upPlus, OUTPUT);
  pinMode(downPlus, OUTPUT);

  //initialize Serial comm - this is for bluetooth module
  Serial.begin(baud);
  //Serial.begin(baud); //either Up(U) or Down(D) for motor
  //Serial.println("Welcome.  Enter a command.");
  //Xbee.println("Welcome.  Enter a command.");
}

void loop() {

  if(Serial.available()> 0) {
    serialIn = Serial.read();
    switch (serialIn) {
      case '1': 
        motorUp();
        delay(1100);
        motorStop();
        break;
      case '2':
        motorDown();
        delay(1100);
        motorStop();
        break;
      }
  }

  buttonUpState = digitalRead(buttonUp);
  buttonDownState = digitalRead(buttonDown);
  if(buttonUpState == LOW && mode == 0) {
    motorUp();
    //Serial.println("up pressed");
  }
  else if(buttonUpState == LOW && mode == 1) {
    motorDown();
    //Serial.println("up pressed");
  }
  else if(buttonDownState == LOW && mode == 0) {
    motorDown();
    //Serial.println("down pressed");
  }
  else if(buttonDownState == LOW && mode == 1) {
    motorUp();
    //Serial.println("down pressed");
  }
  else motorStop();

}

//write fucntions
void motorUp() {
  //if(!checkResistor(photoPin)) {
    //motorStop();
 // }
  //else {
    analogWrite(upPlus, upSpeed); 
    analogWrite(upMinus, 255);
  //}
  //Serial.println("going up");
}

void motorDown() {
    bool val = checkResistor(photoPin);
    Serial.println(val);

  if(val == 1) {
    motorStop();
  }
  else {
    analogWrite(downPlus, downSpeed);
    analogWrite(downMinus, 255);
  }
  //Serial.println("going down");
}

void motorStop() {
  digitalWrite(upPlus, LOW);
  //Serial.println("stopped");
  digitalWrite(downPlus, LOW);
  digitalWrite(upMinus, LOW);
  digitalWrite(downMinus, LOW);
}

bool checkResistor(int pin) {
  if (analogRead(pin) > 900) {
    Serial.println(analogRead(pin));
    return 1; 
  }
  else {
    Serial.println(analogRead(pin));
    return 0;
    }
}
