#include "include/base.h"
#include "include/button.h"
#include "include/character.h"
#include "include/elements.h"
#include "include/properties.h"

using namespace std;
using namespace mINI;

bool initSDL();
void loadCommonFont();
void quitSDL();
enum Stage { MENU, OPTION_MENU, GAME_MODE, IN_GAME, GAME_OVER, QUIT = -1 };
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
        Music BGM;
        // NOTE: Load setting
        bool showGUI = setting["setting"]["ShowGUI"][0] - '0';
        char skillBinding = setting["keybinding"]["skill"][0];
        char flashBinding = setting["keybinding"]["flash"][0];
        int skill = stoi(setting["setting"]["skill"]);
        int difficult = stoi(setting["setting"]["difficult"]);
        while (stage != QUIT) {
            if (stage == MENU) {
                clog << "Menu screen" << endl;
                BGM.loadMusic(setting["path"]["menuBGM"]);
                BGM.playMusic(-1);
                LTexture background(gRenderer, setting["path"]["menu"]);
                LTexture yasuo(gRenderer, setting["path"]["yasuo"]);
                Button start(gRenderer, setting["path"]["startButton"]);
                Button option(gRenderer, setting["path"]["optionButton"]);
                while (stage == MENU) {
                    SDL_RenderClear(gRenderer);
                    background.render({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
                    yasuo.render({417, 88, 592, 462});
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            stage = QUIT;
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            if (start.onHover()) {
                                stage = GAME_MODE;
                            }
                            if (option.onHover()) {
                                stage = OPTION_MENU;
                            }
                        }
                    }
                    if (!start.onHover())
                        start.setRect(START_X, START_Y, 300, 60);
                    else
                        start.setRect(START_X - 20, START_Y, 360, 72);
                    if (!option.onHover())
                        option.setRect(OPTION_X, OPTION_Y, 300, 60);
                    else
                        option.setRect(OPTION_X - 20, OPTION_Y, 360, 72);
                    start.render();
                    option.render();
                    SDL_RenderPresent(gRenderer);
                }
            }
            // TODO: Option menu
            if (stage == OPTION_MENU) {
                /* code */
                clog << "Option screen" << endl;
                LTexture background(gRenderer, setting["path"]["menu"]);
                LTexture text(gRenderer, "CHANGE KEY BINDING: ", Arial, {0xff, 0xff, 0xff});
                LTexture ui(gRenderer, "UI: ", Arial, {0xff, 0xff, 0xff});

                string skillKeyString(1, toupper(skillBinding));
                LTexture skillKey(gRenderer, skillKeyString, Arial, {0xff, 0xff, 0xff});

                string flashKeyString(1, toupper(flashBinding));
                LTexture flashKey(gRenderer, flashKeyString, Arial, {0xff, 0xff, 0xff});

                Button menu(gRenderer, setting["path"]["menuButton"]);
                menu.setRect(51, 29, 277, 71);

                Button skill(gRenderer, setting["path"]["skillBinding"]);
                skill.setRect(210, 255, 132, 132);

                Button flash(gRenderer, setting["path"]["flashBinding"]);
                flash.setRect(456, 255, 132, 132);

                string showGUIBtnPath;
                showGUI ? showGUIBtnPath = "onButton" : showGUIBtnPath = "offButton";
                Button showGUIBtn(gRenderer, setting["path"][showGUIBtnPath]);
                showGUIBtn.setRect(749, 255, 132, 132);

                LTexture settingFrame(gRenderer, setting["path"]["settingFrame"]);
                while (stage == OPTION_MENU) {
                    SDL_RenderClear(gRenderer);
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            stage = QUIT;
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            if (menu.onHover()) {
                                stage = MENU;
                            }
                            if (showGUIBtn.onHover()) {
                                if (showGUI) {
                                    showGUI = false;
                                    showGUIBtn.loadFromFile(setting["path"]["offButton"]);
                                    setting["setting"]["ShowGUI"][0] = '0';
                                    settingFile.write(setting);
                                } else {
                                    showGUI = true;
                                    showGUIBtn.loadFromFile(setting["path"]["onButton"]);
                                    setting["setting"]["ShowGUI"][0] = '1';
                                    settingFile.write(setting);
                                }
                            }
                        }
                        if (e.type == SDL_KEYDOWN) {
                            if (skill.onHover()) {
                                skillBinding = e.key.keysym.sym;
                                skillKeyString[0] = toupper(skillBinding);
                                setting["keybinding"]["skill"][0] = skillBinding;
                                skillKey.loadFromRenderedText(skillKeyString, Arial,
                                                              {0xff, 0xff, 0xff});
                                settingFile.write(setting);
                            }
                            if (flash.onHover()) {
                                flashBinding = e.key.keysym.sym;
                                flashKeyString[0] = toupper(flashBinding);
                                setting["keybinding"]["flash"][0] = flashBinding;
                                flashKey.loadFromRenderedText(flashKeyString, Arial,
                                                              {0xff, 0xff, 0xff});
                                settingFile.write(setting);
                            }
                            if (e.key.keysym.sym == SDLK_ESCAPE) {
                                stage = MENU;
                            };
                        }
                    }
                    background.render({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
                    settingFrame.render({86, 131, 852, 380});
                    showGUIBtn.render();
                    text.render({147, 170, text.getWidth() / 4, text.getHeight() / 4});
                    ui.render({790, 170, ui.getWidth() / 4, ui.getHeight() / 4});
                    menu.render();
                    skill.render();
                    skillKey.render({260, 400, 33, 42});
                    flash.render();
                    flashKey.render({507, 400, 32, 42});
                    SDL_RenderPresent(gRenderer);
                }
            }
            // TODO: Game mode select
            if (stage == GAME_MODE) {
                /* code */
                clog << "Game mode screen" << endl;
                LTexture background(gRenderer, setting["path"]["menu"]);

                Button menu(gRenderer, setting["path"]["menuButton"]);
                menu.setRect(51, 29, 277, 71);

                Button play(gRenderer, setting["path"]["playButton"]);
                play.setRect(360, 29, 277, 71);

                Button skill1(gRenderer, setting["path"]["skill1"]);
                skill1.setRect(149, 127, 185, 185);

                Button skill2(gRenderer, setting["path"]["skill2"]);
                skill2.setRect(334, 127, 185, 185);

                Button skill3(gRenderer, setting["path"]["skill3"]);
                skill3.setRect(149, 312, 185, 185);

                Button skill4(gRenderer, setting["path"]["skill4"]);
                skill4.setRect(334, 312, 185, 185);

                Button easy(gRenderer, setting["path"]["easy"]);
                easy.setRect(763, 134, 161, 73);
                Button medium(gRenderer, setting["path"]["medium"]);
                medium.setRect(763, 252, 161, 73);
                Button hard(gRenderer, setting["path"]["hard"]);
                hard.setRect(763, 370, 161, 73);

                SDL_Rect skillFrameLocation[4] = {{149, 127, 185, 185},
                                                  {334, 127, 185, 185},
                                                  {149, 312, 185, 185},
                                                  {334, 312, 185, 185}};
                LTexture skillFrame(gRenderer, setting["path"]["frame"]);

                SDL_Rect arrowLocation[4] = {{705, 155, 35, 32},
                                             {705, 273, 35, 32},
                                             {705, 391, 35, 32}};
                LTexture arrow(gRenderer, setting["path"]["arrow"]);

                while (stage == GAME_MODE) {
                    SDL_RenderClear(gRenderer);
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            stage = QUIT;
                        }
                        if (e.key.keysym.sym == SDLK_ESCAPE) {
                            stage = MENU;
                        };
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            if (menu.onHover()) {
                                stage = MENU;
                            }
                            if (play.onHover()) {
                                stage = IN_GAME;
                            }
                            if (skill1.onHover()) {
                                skill = 1;
                                setting["setting"]["skill"] = "1";
                                settingFile.write(setting);
                            }
                            if (skill2.onHover()) {
                                skill = 2;
                                setting["setting"]["skill"] = "2";
                                settingFile.write(setting);
                            }
                            if (skill3.onHover()) {
                                skill = 3;
                                setting["setting"]["skill"] = "3";
                                settingFile.write(setting);
                            }
                            if (skill4.onHover()) {
                                skill = 4;
                                setting["setting"]["skill"] = "4";
                                settingFile.write(setting);
                            }
                            if (easy.onHover()) {
                                difficult = 1;
                                setting["setting"]["difficult"] = "1";
                                settingFile.write(setting);
                            }
                            if (medium.onHover()) {
                                difficult = 2;
                                setting["setting"]["difficult"] = "2";
                                settingFile.write(setting);
                            }
                            if (hard.onHover()) {
                                difficult = 3;
                                setting["setting"]["difficult"] = "3";
                                settingFile.write(setting);
                            }
                        }
                    }
                    background.render({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
                    menu.render();
                    play.render();
                    skill1.render();
                    skill2.render();
                    skill3.render();
                    skill4.render();
                    skillFrame.render(skillFrameLocation[skill - 1]);
                    arrow.render(arrowLocation[difficult - 1]);
                    easy.render();
                    medium.render();
                    hard.render();
                    SDL_RenderPresent(gRenderer);
                }
            }
            // TODO: In game
            if (stage == IN_GAME) {
                /* code */
                Character jinx(gRenderer, setting["path"]["sprite"]);
                LTexture background(gRenderer, setting["path"]["background"]);
                BGM.loadMusic(setting["path"]["gameBGM"]);
                BGM.playMusic(-1);
                while (stage == IN_GAME) {
                    SDL_RenderClear(gRenderer);
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            stage = QUIT;
                        }
                        if (e.type == SDL_KEYDOWN) {
                            if (e.key.keysym.sym == SDLK_ESCAPE) {
                                stage = MENU;
                            };
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int x;
                            int y;
                            SDL_GetMouseState(&x, &y);
                            jinx.move(x, y);
                        }
                    }
                    background.render({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
                    jinx.render();
                    SDL_RenderPresent(gRenderer);
                }
            }
            // TODO: Game over screen
            if (stage == GAME_OVER) {
                /* code */
                while (stage == GAME_OVER) {
                    SDL_RenderClear(gRenderer);
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            stage = QUIT;
                        }
                    }
                    SDL_RenderPresent(gRenderer);
                }
            }
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
    Arial = TTF_OpenFont("res/font/arial.ttf", 150);
    // more font will be added
}

void quitSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
}