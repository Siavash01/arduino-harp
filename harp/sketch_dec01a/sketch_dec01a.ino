#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define READ 0b0
#define PLAY 0b1

int state;
int sensorStatus[7];

const byte ledPin = 13;
const byte interruptPin = 2;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void checkStatus() {
  for (int i = 0; i < 7; ++i) {
    sensorStatus[i] = digitalRead(i+2);
  }
}

void clearStatus() {
  for (int i = 0; i < 7; ++i) {
    sensorStatus[i] = 0;
  }
}

void playNote() {
  for (int i = 0; i < 7; ++i) {
    switch(sensorStatus[i]) {
      case 0:
        break;
      case 1:
        myDFPlayer.play(i);
        break;
      default:
        ;
    }
  }
}

void interruptFunc() {
  state = PLAY;
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunc, CHANGE);

  Serial.begin(115200); // Init Serial at 115200 Baud Rate.
  Serial.println("Serial Working"); // Test to check if serial is working or not
 
  for (int i = 0; i < 7; ++i) {
    pinMode(i, INPUT); // set pinmod for ir sensor to output
  }

  mySoftwareSerial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("MID SETUP");
    while(true);
  }
  Serial.println("MID SETUP END");

  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(25);  //Set volume value (0~30).
  
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  
  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  Serial.println("end setup");
}

void loop()
{
  switch(state) {
    case READ:
      state = READ;
      break;
    case PLAY:
      checkStatus();
      playNote();
      clearStatus();
      state = READ;
      break;
  }
}
