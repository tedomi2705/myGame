#ifndef CHAR_H
#define CHAR_H

#include "base.h"
#include "circle.h"

class Character : public LTexture {
   private:
    double x = 512;
    double y = 288;
    int w = 128;
    int h = 128;
    int i = 0;
    double j = 0;
    double destX = x;
    double destY = y;
    double speed = 3.4;
    vector<vector<SDL_Rect>> spriteNum;
   public:
    Circle hitbox;
    Character(/* args */);
    Character(SDL_Renderer* _renderer, const string& path);
    void render();
    void initSprite();
    void flash(int x, int y);
    void setDestination(int x, int y);
    void setSpeed(int n);
    void move();
    int getX();
    int getY();
    int getW();
    int getH();
    Circle getHitbox();
    ~Character();
};

#endif