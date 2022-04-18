#include "include/base.h"
#include "include/properties.h"
using namespace std;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initSDL();

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        cerr << "Error initialize!";
    }

    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logError("Failed to init SDL", SDL_ERROR);
        return false;
    } else {
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                   WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            logError("Can not create window: ", SDL_ERROR);
            return false;
        } else {
            gRenderer = SDL_CreateRenderer(
                gWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                logError("Can not create renderer: ", SDL_ERROR);
                return false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                if (!IMG_Init(IMG_INIT_PNG)) {
                    logError("Can not initialize SDL_image: ", IMG_ERROR);
                    return false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    logError("Can not initialize audio: ", MIX_ERROR);
                    return false;
                }

                if (TTF_Init() < 0) {
                    logError("Can not initialize font: ", TTF_ERROR);
                }
            }
        }
    }
    return true;
}