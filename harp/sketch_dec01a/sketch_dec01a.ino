#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int i = 0;
#define IRSensor 9

#define C4 0
#define D4 1
#define E4 2
#define F4 3
#define G4 4
#define A4 5
#define B4 6

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{

  pinMode(IRSensor, INPUT); // set pinmod for ir sensor to output
  
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

void loop()
{
  int sensorStatus = digitalRead(IRSensor);
  static unsigned long timer = millis();

  switch(sensorStatus) {
    case 0:
      myDFPlayer.play(0);
      break;
    case 1:
      myDFPlayer.play(1);
      break;
    case 2:
      myDFPlayer.play(2);
      break;
    case 3:
      myDFPlayer.play(3);
      break;
    case 4:
      myDFPlayer.play(4);
      break;
    case 5:
      myDFPlayer.play(5);
      break;
    case 6:
      myDFPlayer.play(6);
      break;
    default:
      ;
  }
  
  if (i > 6) i = 0;
  
  if (millis() - timer > 3000) {
    i++;
    timer = millis();
    myDFPlayer.play(i);  //Play next mp3 every 3 second.
  }
}
