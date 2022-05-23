#include "include/character.h"

#include <cmath>
const int SPRITE_SIZE = 640;

Character::Character(/* args */) {}

Character::Character(SDL_Renderer* _renderer, const string& path) : LTexture(_renderer, path) {
    int spriteWidth;
    int spriteHeight;
    SDL_QueryTexture(mTexture, NULL, NULL, &spriteWidth, &spriteHeight);
    int spriteWNum = spriteWidth / SPRITE_SIZE;
    int spriteHNum = spriteHeight / SPRITE_SIZE;
    // vector<vector<SDL_Rect>> spriteNum(spriteWNum, vector<SDL_Rect>(spriteHNum));

    for (int j = 0; j < spriteHNum; j++) {
        spriteNum.push_back(vector<SDL_Rect>());
        for (int i = 0; i < spriteWNum; i++) {
            spriteNum[j].push_back({SPRITE_SIZE * i, SPRITE_SIZE * j, SPRITE_SIZE, SPRITE_SIZE});
        }
    }
    hitbox.x = x - w / 2;
    hitbox.y = y - w / 2;
    hitbox.r = w / 3;
}

void Character::initSprite() {}

void Character::render() {
    SDL_Rect dst = {int(x - w / 2), int(y - w / 2), int(w), int(h)};
    SDL_RenderCopy(renderer, mTexture, &spriteNum[i][(int)j], &dst);
}
void Character::setDestination(int x, int y) {
    destX = x;
    destY = y;
}

void Character::setSpeed(int n) { speed = n; }

void Character::move() {
    int distance = sqrt((x - destX) * (x - destX) + (y - destY) * (y - destY));
    if (distance > 2) {
        this->x -= (x - destX) * speed / distance;
        this->y -= (y - destY) * speed / distance;
        j > 22 ? j = 0 : j += 0.5;  // Animation
    }
    // Choose sprite:
    double cosx = -(x - destX) / sqrt((x - destX) * (x - destX) + (y - destY) * (y - destY));
    if (cosx > cos(M_PI / 8))
        i = 4;
    else if (cosx > cos(3 * M_PI / 8))
        if ((y - destY) > 0)
            i = 2;
        else
            i = 7;
    else if (cosx > cos(5 * M_PI / 8))
        if ((y - destY) > 0)
            i = 1;
        else
            i = 6;
    else if (cosx > cos(7 * M_PI / 8))
        if ((y - destY) > 0)
            i = 0;
        else
            i = 5;
    else
        i = 3;
    hitbox.x = this->x;
    hitbox.y = this->y;
}
void Character::flash(int x, int y) {
    int distance = sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y));
    int distanceToDest =
        sqrt((this->x - destX) * (this->x - destX) + (this->y - destY) * (this->y - destY));
    const int disLimit = 175;
    if (distance > disLimit) {
        this->x -= (this->x - x) * disLimit / distance;
        this->y -= (this->y - y) * disLimit / distance;
    } else {
        this->x = x;
        this->y = y;
        destX = this->x;
        destY = this->y;
    }
    if (distanceToDest <= 3) {
        destX = this->x;
        destY = this->y;
    }
}
int Character::getX() { return x; }
int Character::getY() { return y; }
int Character::getW() { return w; }
int Character::getH() { return h; }

Character::~Character() {}
