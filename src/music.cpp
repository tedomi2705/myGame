#include "include/music.h"
Music::Music(/* args */) {}

Music::Music(string path) : music(Mix_LoadMUS(path.c_str())) {
    if (music == nullptr) logError("Failed to load background music", MIX_ERROR);
}

bool Music::loadMusic(string path) {
    music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        logError("Failed to load music", MIX_ERROR);
        return false;
    }
    return true;
}

bool Music::playMusic(int loopTimes = 0) {
    if (Mix_PlayMusic(music, loopTimes)==-1) {
        logError("Error playing music", MIX_ERROR);
        return false;
    }
    return true;
}

Music::~Music() { Mix_FreeMusic(music); }
