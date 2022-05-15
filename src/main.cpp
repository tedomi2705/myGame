#include "include/LTexture.h"
#include "include/base.h"
#include "include/elements.h"
#include "include/properties.h"

using namespace std;
using namespace mINI;

bool initSDL();
void loadCommonFont();
void quitSDL();
enum Stage { MENU, OPTION_MENU, GAME_MODE, IN_GAME, GAME_OVER, QUIT };
int main(int argc, char* argv[]) {
    if (!initSDL()) {
        cerr << "Error initialize!";
    } else {
        INIFile settingFile("setting.ini");
        INIStructure setting;
        settingFile.read(setting);

        SDL_Event e;
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        Stage stage = MENU;
        while (stage == MENU) {
            /* code */
        }
        while (stage == GAME_MODE) {
            /* code */
        }
        while (stage == OPTION_MENU) {
            /* code */
        }

        while (stage == IN_GAME) {
            SDL_RenderClear(gRenderer);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    stage = QUIT;
                }
            }
            SDL_RenderPresent(gRenderer);
            SDL_Delay(1000.0 / FPS_LIMIT);
        }

        while (stage == GAME_OVER) {
            /* code */
        }
    }

    quitSDL();
    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logError("Failed to init SDL", SDL_ERROR);
        return false;
    } else {
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            logError("Can not create window: ", SDL_ERROR);
            return false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1,
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
    loadCommonFont();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    return true;
}

void loadCommonFont() {
    Arial = TTF_OpenFont("res/font/arial.ttf", 24);
    // more font will be added
}

void quitSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
}