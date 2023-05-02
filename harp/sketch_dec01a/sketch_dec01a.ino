#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int cnt = 0;
#define IRSensorC4 0
#define IRSensorD4 1
#define IRSensorE4 2
#define IRSensorF4 3
#define IRSensorG4 4
#define IRSensorA4 5
#define IRSensorB4 6

#define C4 0
#define D4 1
#define E4 2
#define F4 3
#define G4 4
#define A4 5
#define B4 6

int sensorStatus[7];

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  for (int i = 0; i < 7; ++i) {
    pinMode(i, INPUT); // set pinmod for ir sensor to output
  }
  mySoftwareSerial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }

  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(25);  //Set volume value (0~30).
  
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  
  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void checkStatus() {
  for (int i = 0; i < 7; ++i) {
    sensorStatus[i] = digitalRead(i);
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

void loop()
{
  checkStatus();
  playNote();
  clearStatus();
}
