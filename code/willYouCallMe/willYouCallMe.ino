/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
  <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
  Project: Will you call Me?
  Created 2018-11-01
  By [Wu Chuhan]
  Tutored by [Liu Chengyang]

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
  All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
  1.Connection and Diagram can be found here
  <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
  2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "JC_Button.h"          // https://github.com/JChristensen/JC_Button


const byte BUTTON_PIN(7);

Button myBtn(BUTTON_PIN, 50);       // define the button
int voiceNumber;  // 10 voice + 1 ring

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup()
{

  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  myBtn.begin();              // initialize the button object
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(29);  //Set volume value. From 0 to 30
  // myDFPlayer.loop(1); //loop all mp3 files in folder SD:/05.

}

void loop()
{
  myBtn.read();
  
  if (myBtn.wasReleased())
  {
    
    Serial.println("play ring sound");
    static unsigned long timer = millis();

   
      myDFPlayer.loop(1);  //Play next mp3 every 3.3 second.
     // Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
     delay(1000);
   
  }
  if (myBtn.wasPressed())
  {
    Serial.println("play random voice");
     voiceNumber = (int)random(2, 12);
     Serial.println(voiceNumber);
     myDFPlayer.playMp3Folder(voiceNumber);
  }

  //  if (myDFPlayer.available()) {
  // printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  // delay(5000);
  //  int val = digitalRead(buttonPin);  //button input value
  //  if (val == HIGH) {
  //    buttonPressed = true;
  //  //  stateAudio = false;
  //    Serial.println("button is pressed");

  //    // stateAudio = !stateAudio;
  //
  //
  //  }
  //
  //
  //
  //  else {
  //    Serial.println("button is free");
  //    buttonPressed == false;
  //
  //
  //    if (stateAudio == false && buttonPressed == false) {
  //      voiceNumber = random(1, 4);
  //      myDFPlayer.play(voiceNumber);
  //      timer2 = millis();
  //      if(millis() - timer2 > 2090){
  //          stateAudio = true;
  //        }
  //
  //
  //    }
  //    //  stateAudio = !stateAudio;
  //   // stateAudio = false;
  //
  //
  //  }
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));

      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
