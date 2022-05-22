#ifndef CHAR_H
#define CHAR_H

#include "base.h"

class Character : public LTexture {
   private:
    int x = 512;
    int y = 288;
    int w = 128;
    int h = 128;
    int destX=x;
    int destY=y;
    vector<vector<SDL_Rect>> spriteNum;
   public:
    Character(/* args */);
    Character(SDL_Renderer* _renderer, const string& path);
    void render();
    void initSprite();
    void move(int x, int y);
    int getX();
    int getY();
    int getW();
    int getH();
    ~Character();
};

#endif