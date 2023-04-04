#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

const int gravity = 1;

class Player
{
public:
    Player(std::string path, int x, int y);
    ~Player();

    SDL_Surface* const surface() const { return player_; }
    SDL_Rect* rect() { return &rect_; }
    int bottom() const { return (rect_.y + rect_.h); }
    
    void update();

    void jump();
    void move_left();
    void move_right();
    void stop();

private:
    SDL_Surface* player_ = nullptr;
    SDL_Rect rect_;
    int dx_, dy_;
    int speed_ = 5;
};

#endif
