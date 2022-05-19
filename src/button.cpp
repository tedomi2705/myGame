#include "include/button.h"

using namespace std;

Button::Button() : LTexture() {}
Button::Button(SDL_Renderer* _renderer) : LTexture(_renderer) {}
Button::Button(SDL_Renderer* _renderer, const string& path) : LTexture(_renderer, path) {
    w = getWidth();
    h = getHeight();
}
Button::Button(SDL_Renderer* _renderer, const string& text, TTF_Font* font, SDL_Color textColor)
    : LTexture(_renderer, text, font, textColor) {}
Button::Button(const string& path) : LTexture(path) {
    w = getWidth();
    h = getHeight();
}
Button::Button(const string& text, TTF_Font* font, SDL_Color textColor)
    : LTexture(text, font, textColor) {}

void Button::render() {
    SDL_Rect mask = {0, 0, textureWidth, textureHeight};
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(renderer, mTexture, &mask, &dst);
}
bool Button::onHover() {
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX < x) return false;
    if (mouseY < y) return false;
    if (mouseX > x + w) return false;
    if (mouseY > y + h) return false;

    return true;
}

void Button::setRect(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}