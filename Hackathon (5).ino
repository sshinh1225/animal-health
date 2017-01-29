//Need Arduino Ethernet Sheild in order to get serial data from heart rate.h to the internet
#include "pitches.h"


int analogValue1;
int analogValue2;

// notes in the melody:
int melody[] = {
  NOTE_G3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4
};


int reached = 0;
int counter = 0;

void setup() {
  
  Serial.begin(9600);
}

void loop(){

  analogValue1 = analogRead(A0);
  analogValue2 = analogRead(A1);

  

  int Value = -analogValue2 + analogValue1;
  Serial.println(Value);

  int threshold = 190;
  

  
  if (Value > threshold){
    reached = 1;
    
  }


    if ((reached == 1) && (counter != 1)){
   
      // iterate over the notes of the melody:
      for (int thisNote = 0; thisNote < 14; thisNote++) {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
        counter = 1;
      }

   
  }
    
  delay(200);



}


