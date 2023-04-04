#include <iostream>
#include <SDL2/SDL_image.h>


#include "Constants.h"
#include "Player.h"


Player::Player(std::string path, int x, int y)
    : dx_(0), dy_(0)
{
    player_ = IMG_Load(path.c_str());
    rect_ = { x, y, player_->w, player_->h};

    if (player_ == nullptr) {
        printf("Unable to load %s image!\n", path.c_str());
    }
}


Player::~Player() { SDL_FreeSurface(player_); }


void Player::update() 
{
    rect_.x += dx_;
    rect_.y += dy_;

    if (bottom() < SCREEN_HEIGHT) { dy_ += gravity; std::cout << dy_ << std::endl; }
    else {
        dy_ = 0;
        rect_.y = SCREEN_HEIGHT - rect_.h;
    }
}


void Player::jump()
{
    dy_ = -(speed_ * 2);
}


void Player::move_left() 
{
    dx_ = -speed_;
}


void Player::move_right()
{
    dx_ = speed_;
}


void Player::stop() 
{
    dx_ = 0;
}
