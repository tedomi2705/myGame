#include "include/LTexture.h"
using namespace std;
LTexture::LTexture(SDL_Renderer* _renderer) : renderer(_renderer) {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    SDL_DestroyTexture(mTexture);
    free();
}

void LTexture::free() {
    if (mTexture != nullptr) {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromRenderedText(string textureText, TTF_Font* font, SDL_Color textColor) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

bool LTexture::loadFromFile(string path) {
    free();
    mTexture = IMG_LoadTexture(renderer, path.c_str());

    if (mTexture == nullptr) {
        logError("Can not load image.", IMG_ERROR);
    } else {
        SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    }
    return mTexture != nullptr;
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderSpace = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderSpace);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }
