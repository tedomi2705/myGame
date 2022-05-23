#ifndef FIREBALL_H
#define FIREBALL_H

#include "LTexture.h"
#include "circle.h"
class Fireball : public LTexture {
   private:
    double x, y;
    double destX, destY;
    int w, h;
    double angle;
    double speed;
    double velocityX;
    double velocityY;

   public:
    Fireball(/* args */);
    Fireball(SDL_Renderer*, std::string path, double x, double y, double _x, double _y,double speed);
    Circle hitbox;
    void move();
    void render();
    int getX();
    int getY();
    ~Fireball();
};

#endif