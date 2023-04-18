#include <SDL2/SDL_audio.h>
#include <ios>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <sys/cdefs.h>


#include "Constants.h"
#include "Player.h"


Player::Player(Surface* screen, std::string path, int x, int y)
    : screen_(screen), dx_(0), dy_(0), health_(100)
{
    fist_ = IMG_Load("images/Fist.png");
    player_ = IMG_Load(path.c_str());

    if (player_ == nullptr) {
        printf("Unable to load %s image!\n", path.c_str());
    } else {
        rect_ = { x, y, player_->w, player_->h};
    }
}


Player::~Player() { SDL_FreeSurface(player_); }


void Player::update() {

    rect_.x += dx_;
    rect_.y += dy_;

    if (bottom() < SCREEN_HEIGHT) { dy_ += gravity; }
    else {
        dy_ = 0;
        rect_.y = SCREEN_HEIGHT - rect_.h;
    }

    if (attack_frame > 0) { 
        --attack_frame;
        if (facing_right) {
            fist_rect_ = { rect_.x + rect_.w, rect_.y + (rect_.h / 3), fist_->w, fist_->h };
        } else { 
            fist_rect_ = { rect_.x - fist_->w , rect_.y + (rect_.h / 3), fist_->w, fist_->h };
        }
    } else if (attack_frame == 0) {
        punching_ = false;
    }
}


void Player::draw()
{
    if (health_ > 0) 
    {
        screen_->draw(player_, rect_);
        if (attack_frame > 0) {
            if (facing_right) {
                screen_->draw(fist_, fist_rect_);
            } else {
                screen_->draw(fist_, fist_rect_);
            }
        }
    }
}


void Player::jump() {
    dy_ = -(speed_ * 2);
}


void Player::move_left() {
    dx_ = -speed_;
    facing_right = false;
}


void Player::move_right() {
    dx_ = speed_;
    facing_right = true;
}


void Player::stop() {
    dx_ = 0;
}


// FIXME: Lock direction of punch
void Player::punch() {
    if (punching_) return;

    punching_ = true;
    attack_frame = 15;
    if (dx_ >= 0) {
        bool right = true;
    } else {
        bool right = false;
    }
}
