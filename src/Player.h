#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

#include "Surface.h"

const int gravity = 1;

class Player
{
public:
    Player(Surface * screen, std::string path, int x, int y);
    ~Player();

    SDL_Surface* const surface() const { return player_; }
    SDL_Rect* rect() { return &rect_; }
    
    int top() const { return (rect_.y); }
    int bottom() const { return (rect_.y + rect_.h); }
    int left() const { return (rect_.x); }
    int right() const { return (rect_.x + rect_.w); }
    int health() { return health_; }

    void stop_punching() {
        punching_ = false;
    }
    bool punching() const { return punching_; }
    void hit() { health_ -= 5; }
    
    void update();
    void draw();

    void jump();
    void move_left();
    void move_right();
    void stop();
    void punch();

    SDL_Rect fist_rect_;
private:
    Surface * screen_ = nullptr;
    SDL_Surface* player_ = nullptr;
    SDL_Surface* fist_ = nullptr;
    bool punching_ = false;
    bool facing_right = false;
    int attack_frame = 0;
    SDL_Rect rect_;
    int dx_, dy_;
    int speed_ = 5;
    int health_;
};

#endif
