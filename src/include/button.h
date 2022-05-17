#ifndef BUTTON
#define BUTTON
#include "base.h"
class Button {
   private:
    LTexture texture;

   public:
    Button(/* args */);
    int x, y, w, h;
    bool setRenderer(SDL_Renderer* renderer);
    bool onHover();
    void setPosition(int x, int y);
    void setSize(int w, int h);
    void render();
    ~Button();
};


#endif