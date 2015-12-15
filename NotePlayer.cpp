#include "NotePlayer.h"
#include <string.h>

NotePlayer::NotePlayer(): currentTone(-1) {

}

void NotePlayer::init(int pin) {
  speakerPin = pin;
  pinMode(speakerPin, OUTPUT);
}

void NotePlayer::startPlaying(const char *note) {
  for(int i=0; i<MAX_NOTES; i++){
    if (strcmp(note, scale[i]) == 0) {
      /* found the right note */
      setTone(timings[i]);
      break;
    }
  }
}

void NotePlayer::stopPlaying() {
  setTone(-1);
}

void NotePlayer::setTone(int tone) {
  currentTone = tone;
}

/**
 * This object's time slice to do stuff.
 * Attempt to play a note for <duration> milliseconds and then yield.
 */
void NotePlayer::play(unsigned long duration) {
  if (currentTone > -1) {
    playTone(currentTone, duration);
  }
}

const char * (NotePlayer::scale[MAX_NOTES]) = {
  "A", "C#", "D#", "E", "E#", "G", "G#", "A2", "A#", "Bb", "B#", "C#2"
};

int (NotePlayer::timings[MAX_NOTES]) = {
  2408, 1804, 1607, 1607, 1519, 1275, 1204, 1204, 2145, 1073, 1014, 956
};  // all of these are sharp except for G

void NotePlayer::toneDelay(unsigned long microseconds) {
  unsigned long startTime = micros();
  while (micros() - startTime < microseconds) {}
}

void NotePlayer::toneDelayLong(unsigned long milliseconds) {
  unsigned long startTime = millis();
  while (millis() - startTime < milliseconds) {}
}

void NotePlayer::playTone(int tone, int duration) {
  unsigned long startTime;
  //for (long i = 0; i < duration * 1000L; i += tone * 2) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    toneDelay(tone);
    digitalWrite(speakerPin, LOW);
    toneDelay(tone);
  }
}

//void NotePlayer::playNote(int scale_length, char *scale, int *timings, char note, int duration) {
//  // play the tone corresponding to the note name
//  for (int i = 0; i < scale_length; i++) {
//    if (scale[i] == note) {
//      Serial.print(scale[i]);
//      playTone(timings[i], duration);
//    }
//  }
//}
