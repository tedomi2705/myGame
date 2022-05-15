#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "base.h"

using namespace std;

enum textureType { IMAGE, FONT };

class LTexture {
   public:
    LTexture();
    LTexture(SDL_Renderer* _renderer);
    LTexture(SDL_Renderer* _renderer, const string& path);
    LTexture(SDL_Renderer* _renderer, const string& text, TTF_Font* font, SDL_Color textColor);
    LTexture(const string& path);
    LTexture(const string& text, TTF_Font* font, SDL_Color textColor);

    ~LTexture();

    void free();

    bool loadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor);

    bool loadFromFile(const string& path);

    bool setRenderer(SDL_Renderer* _renderer);

    void render(const SDL_Rect& dst);
    void render(const SDL_Rect& src, const SDL_Rect& dst);

    int getWidth();

    int getHeight();

   private:
    SDL_Texture* mTexture;
    SDL_Renderer* renderer;
    int textureWidth;
    int textureHeight;
};

#endif  // !LTEXTURE_H_