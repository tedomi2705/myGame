#include "include/character.h"

const int SPRITE_SIZE = 640;

Character::Character(/* args */) {}

Character::Character(SDL_Renderer* _renderer, const string& path) : LTexture(_renderer, path) {
    int spriteWidth;
    int spriteHeight;
    SDL_QueryTexture(mTexture, NULL, NULL, &spriteWidth, &spriteHeight);
    int spriteWNum = spriteWidth / SPRITE_SIZE;
    int spriteHNum = spriteHeight / SPRITE_SIZE;
    // vector<vector<SDL_Rect>> spriteNum(spriteWNum, vector<SDL_Rect>(spriteHNum));

    clog << spriteWNum << " " << spriteHNum;
    for (int j = 0; j < spriteHNum; j++) {
        spriteNum.push_back(vector<SDL_Rect>());
        for (int i = 0; i < spriteWNum; i++) {
            spriteNum[j].push_back({SPRITE_SIZE * i, SPRITE_SIZE * j, SPRITE_SIZE, SPRITE_SIZE});
        }
    }
}

void Character::initSprite() {}

void Character::render() {
    SDL_Rect dst = {x - w / 2, y - w / 2, w, h};
    SDL_RenderCopy(renderer, mTexture, &spriteNum[0][0], &dst);
}
void Character::move(int x, int y) {
    this->x = x;
    this->y = y;
}
int Character::getX() { return x; }
int Character::getY() { return y; }
int Character::getW() { return w; }
int Character::getH() { return h; }

Character::~Character() {}
