#ifndef MUSIC_H
#define MUSIC_H
#include "base.h"

using namespace std;

class Music {
   private:
    Mix_Music* music = nullptr;

   public:
    Music(/* args */);
    Music(string path);
    bool playMusic(int loopTimes);
    bool loadMusic(string path);
    ~Music();
};

#endif
