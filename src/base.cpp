#include "include/base.h"




using namespace std;


void logError(string msg, int errorCode) {
    if (errorCode == SDL_ERROR) {
        cerr << msg << SDL_GetError() << endl;
    }
    if (errorCode == IMG_ERROR) {
        cerr << msg << IMG_GetError() << endl;
    }
    if (errorCode == MIX_ERROR) {
        cerr << msg << Mix_GetError() << endl;
    }
    if (errorCode == TTF_ERROR) {
        cerr << msg << TTF_GetError() << endl;
    }
}