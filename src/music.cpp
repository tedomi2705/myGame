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
    if (Mix_PlayMusic(music, loopTimes) == -1) {
        logError("Error playing music", MIX_ERROR);
        return false;
    }
    return true;
}

bool Music::isPlaying() {
    if (!Mix_PlayingMusic()) return false;
    return true;
}

bool Music::isPaused() {
    if (Mix_PausedMusic()) return true;
    return false;
}
void Music::pause() { Mix_PauseMusic(); }

void Music::resume() { Mix_ResumeMusic(); }

void Music::stop() { Mix_HaltMusic(); }

Music::~Music() { Mix_FreeMusic(music); }
