#include "include/LTexture.h"
using namespace std;
/**
 * @brief Construct a new LTexture::LTexture object
 */
LTexture::LTexture() {
    mTexture = nullptr;
    textureWidth = 0;
    textureHeight = 0;
}
/**
 * @brief Construct a new LTexture::LTexture object
 *
 * @param _renderer renderer using
 */
LTexture::LTexture(SDL_Renderer* _renderer) : renderer(_renderer) {
    mTexture = nullptr;
    textureWidth = 0;
    textureHeight = 0;
}
/**
 * @brief Construct a new LTexture::LTexture object that load an image
 *
 * @param _renderer renderer using
 * @param path path to image
 */
LTexture::LTexture(SDL_Renderer* _renderer, const string& path) : renderer(_renderer) {
    if (!loadFromFile(path)) {
        logError("Error loading image: ", IMG_ERROR);
    }
}
/**
 * @brief Construct a new LTexture::LTexture object that load an image
 *
 * @param path path to image
 */
LTexture::LTexture(const string& path) {
    if (!loadFromFile(path)) {
        logError("Error loading image: ", IMG_ERROR);
    }
}
/**
 * @brief Construct a new LTexture::LTexture object that load text
 *
 * @param _renderer renderer using
 * @param text The text rendered
 * @param font TTF_Font used
 * @param textColor SDL_Color used
 */
LTexture::LTexture(SDL_Renderer* _renderer, const string& text, TTF_Font* font, SDL_Color textColor)
    : renderer(_renderer) {
    if (!loadFromRenderedText(text, font, textColor)) {
        cerr << "Error constructing text";
    }
}
/**
 * @brief Construct a new LTexture::LTexture object that load text
 *
 * @param text The text rendered
 * @param font TTF_Font used
 * @param textColor SDL_Color used
 */
LTexture::LTexture(const string& text, TTF_Font* font, SDL_Color textColor) {
    if (!loadFromRenderedText(text, font, textColor)) {
        cerr << "Error constructing text";
    }
}

LTexture::~LTexture() {
    SDL_DestroyTexture(mTexture);
    free();
}

void LTexture::free() {
    if (mTexture != nullptr) {
        mTexture = nullptr;
        textureWidth = 0;
        textureHeight = 0;
    }
}
/**
 * @brief Load text will be rendered
 *
 * @param textureText The text rendered
 * @param font TTF_Font used
 * @param textColor SDL_Color used
 * @return load result
 */
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
            textureWidth = textSurface->w;
            textureHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

/**
 * @brief load an image
 *
 * @param path Path to image
 * @return Load result
 *
 */
bool LTexture::loadFromFile(const string& path) {
    free();
    mTexture = IMG_LoadTexture(renderer, path.c_str());

    if (mTexture == nullptr) {
        logError("Can not load image.", IMG_ERROR);
    } else {
        SDL_QueryTexture(mTexture, NULL, NULL, &textureWidth, &textureHeight);
    }
    return mTexture != nullptr;
}

void LTexture::render(const SDL_Rect& dst) {
    SDL_Rect src = {0, 0, textureWidth, textureHeight};
    SDL_RenderCopy(renderer, mTexture, &src, &dst);
}
void LTexture::render(const SDL_Rect& src, const SDL_Rect& dst) {
    SDL_RenderCopy(renderer, mTexture, &src, &dst);
}

int LTexture::getWidth() { return textureWidth; }

int LTexture::getHeight() { return textureHeight; }

bool LTexture::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
    if (!renderer) {
        cerr << "Unable to set SDL_Renderer";
        return false;
    } else
        return true;
}
