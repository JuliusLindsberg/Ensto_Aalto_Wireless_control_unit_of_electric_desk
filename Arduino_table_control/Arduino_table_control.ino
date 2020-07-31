/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int signalUp = 2; // Gate1
const int signalDown = 8; // Gate2
const int BdownRead = 6; //button read1
const int BupRead = 4; //button read2
const int encoderPin = A0;

//bool up = 1;
//bool down = 1;
//bool BTup = 1;
//bool BTdown = 1;

// This variable is something from 0 to 1023 based on the voltage in encoderPin.
short encoderData = 0;

// This variable is 0, 1 or 2 based on analyzeSignalLevel() return
// and is explained there.
int signalLevel = 0;

// Temporary variables
// targetHeight is given by the user by bluetooth.
// tableHeight will be stored in flash memory.
// xyz is a variable that helps to execute BTdrive only once.
short targetHeight = 100;
short tableHeight = 0;
int xyz = 1;

// Encoder steps are counted based on encoder signal crossing these
//thresholds in analyzeSignalLevel.
#define THRESHOLD_LOW 910
#define THRESHOLD_HIGH 995



// levelAnalyser checks where the sample is in the expected signal.
// 0 is the valley, 1 is middle and 2 the peak.
// we only need positions 0 and 1 but position 2 is still here if we want
// to know the direction from the signal at some later time.
int analyzeSignalLevel(short sample){
  if (sample >= THRESHOLD_LOW){
    if (sample >= THRESHOLD_HIGH){
      return 2;
    }
    else {
      return 1;
    }
  }
  else {
    return 0;
  }
}

// analyzeTableHeight changes the variable for table height and will
// have to store it in flash memory in the future.
int analyzeTableHeight(short sample, bool up, bool down) {
  if (up && !down){
    if ((signalLevel != 2) && (analyzeSignalLevel(sample) == 2)) {
      tableHeight--;
    }
  }
  else if (down && !up){
    if ((signalLevel == 2) && (analyzeSignalLevel(sample) != 2)) {
      tableHeight++;
    }
  }
  signalLevel = analyzeSignalLevel(sample);
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);

  pinMode(BdownRead, INPUT);
  pinMode(BupRead, INPUT);

  digitalWrite(signalUp, LOW);
  digitalWrite(signalDown, LOW);
  
}

// This function is to be executed only when bluetooth signal is received
// and does same things as main loop except with bluetooth variables (BTup, BTdown).
// BTdrive breaks, when button is pressed or desired height is reached.
void BTdrive(short targetHeight) {
  bool BTup = 1;
  bool BTdown = 1;
  bool Bup = 1;
  bool Bdown = 1;
  
  if (targetHeight > tableHeight) {
    BTup = 0;
  }
  else if (targetHeight < tableHeight) {
    BTdown = 0;
  }
  else {
    return;
  }
  
  while(!(targetHeight == tableHeight) && Bup && Bdown){
    encoderData = analogRead(A0);
    analyzeTableHeight(encoderData, BTup, BTdown);
    
    Bup = digitalRead(BupRead);
    Bdown = digitalRead(BdownRead);

    digitalWrite(signalUp, !BTup);
    digitalWrite(signalDown, !BTdown);

    Serial.print(THRESHOLD_LOW);
    Serial.print(",");
    Serial.print(THRESHOLD_HIGH);
    Serial.print(",");
    Serial.print("encoderDtata:");
    Serial.print(encoderData);
    Serial.print(",");
    Serial.print("targetHeight:");
    Serial.print(targetHeight);
    Serial.print(",");
    Serial.print("tableHeight:");
    Serial.println(tableHeight);
  }
}


void loop() {

  bool up = 1;
  bool down = 1;
  
  up = digitalRead(BupRead);
  down = digitalRead(BdownRead);
  
  digitalWrite(signalUp, !up);
  digitalWrite(signalDown, !down);

  encoderData = analogRead(A0);

// BAD CODE
  if(xyz){
    BTdrive(targetHeight);
  }
  xyz = 0;
// DO BETTER

  analyzeTableHeight(encoderData, up, down);
  
  Serial.print(THRESHOLD_LOW);
  Serial.print(",");
  Serial.print(THRESHOLD_HIGH);
  Serial.print(",");
  Serial.print("encoderDtata:");
  Serial.print(encoderData);
  Serial.print(",");
  Serial.print("targetHeight:");
  Serial.print(targetHeight);
  Serial.print(",");
  Serial.print("tableHeight:");
  Serial.println(tableHeight);
  //Serial.print(up);
  //Serial.println(",");
  //Serial.print(down);
  //Serial.println(",");

  delay(3);
}
