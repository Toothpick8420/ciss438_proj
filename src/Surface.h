#ifndef SURFACE_H
#define SURFACE_H

#include <string>
#include <SDL2/SDL.h>

#include "Constants.h"

class InitializationError{};

class Surface
{
public:
    Surface(std::string title="Window", 
            int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);

    ~Surface();

    void clear();
    void draw(SDL_Surface*, SDL_Rect);
    void update();

private:
    SDL_Window* window_;
    SDL_Surface* surface_;
};

#endif
