#include "include/fireball.h"

#include <cmath>
Fireball::Fireball(/* args */) {}

Fireball::Fireball(SDL_Renderer* renderer, std::string path, double x, double y, double destX,
                   double destY, double _speed)
    : LTexture(renderer, path), speed(_speed) {
    w = getWidth();
    h = getHeight();
    this->x = x;
    this->destX = destX;
    this->y = y;
    this->destY = destY;
    int distance = sqrt((x - destX) * (x - destX) + (y - destY) * (y - destY));
    velocityX = -(x - destX) * speed / distance;
    velocityY = -(y - destY) * speed / distance;
    double cosx = -(x - destX) / sqrt((x - destX) * (x - destX) + (y - destY) * (y - destY));
    double rad = acos(cosx);
    angle = rad * 180 / M_PI;
    if (destY - y < 0) angle = -angle;
    hitbox.x = x-w/2;
    hitbox.y = y-w/2;
    hitbox.r = w / 18;
}
void Fireball::render() {
    SDL_Rect mask = {0, 0, textureWidth, textureHeight};
    SDL_Rect dst = {int(x - w / 2), int(y - h / 2), int(w / 1.5), int(h / 1.5)};
    SDL_RenderCopyEx(renderer, mTexture, &mask, &dst, angle, NULL, SDL_FLIP_NONE);
}
void Fireball::move() {
    this->x += velocityX;
    this->y += velocityY;
    hitbox.x = this->x-w/3.5;
    hitbox.y = this->y-w/3.5;
}
int Fireball::getX() { return int(x); }
int Fireball::getY() { return int(y); }
Fireball::~Fireball() {}