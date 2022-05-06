#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "base.h"

using namespace std;

class LTexture {
   public:
    LTexture(SDL_Renderer* _renderer);

    ~LTexture();

    void free();

    bool loadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor);

    bool loadFromFile(string path);

    void render(int x, int y, SDL_Rect* clip = nullptr);

    int getWidth();

    int getHeight();

   private:
    SDL_Texture* mTexture;
    SDL_Renderer* renderer;
    int mWidth;
    int mHeight;
};

#endif  // !LTEXTURE_H_