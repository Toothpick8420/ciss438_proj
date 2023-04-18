#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL_rect.h>


class Rect
{
public:
    Rect(int x, int y, int w, int h)
        : x_(x), y_(y), w_(w), h_(h)
    {}

    Rect(const SDL_Rect & r)
        : x_(r.x), y_(r.y), w_(r.w), h_(r.h)
    {}
    

    int x_, y_, w_, h_;
};

#endif
