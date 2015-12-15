#ifndef NOTE_PLAYER_H
#define NOTE_PLAYER_H
#define MAX_NOTES 20

#include "Arduino.h"

class NotePlayer {
  public:
    NotePlayer();
    void init(int);
    void startPlaying(const char *);
    void play(unsigned long);
    void stopPlaying();

  private:
    int speakerPin;
    int currentTone;
    static const char * scale[MAX_NOTES];
    static int timings[MAX_NOTES];
    void toneDelay(unsigned long);
    void toneDelayLong(unsigned long);
    void playTone(int, int);
    void setTone(int);
};
#endif // NOTE_PLAYER_H
