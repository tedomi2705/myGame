#ifndef BUTTON
#define BUTTON
#include "base.h"
class Button : public LTexture {
   public:
    using LTexture::render;
    Button();
    Button(SDL_Renderer* _renderer);
    Button(SDL_Renderer* _renderer, const string& path);
    Button(SDL_Renderer* _renderer, const string& text, TTF_Font* font, SDL_Color textColor);
    Button(const string& path);
    Button(const string& text, TTF_Font* font, SDL_Color textColor);

    int x, y, w, h;
    bool useEvent(SDL_Event*);
    void setRect(int, int, int, int);
    bool onHover();
    void render();

   private:
    SDL_Event e;
};

#endif