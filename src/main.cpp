#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>

#include "Constants.h"
#include "db.h"
#include "Player.h"
#include "Surface.h"


int mainMenu();
void init();
void play();


// Global variables that will be used across multiple functions
Surface screen("Street Fighter Clone", SCREEN_WIDTH, SCREEN_HEIGHT);
Player player1(&screen, "images/RedGuy.png", 64, SCREEN_HEIGHT - 128);
Player player2(&screen, "images/BlueGuy.png", SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128);
sqlite3* DB;


// Game State Constants for Readability
enum gameState {
    PLAY = 1,
    REGISTER_USER = 2,
    SELECT_USER = 3,
    QUIT = 4,
    SHOW_ALL_USERS = 5
};

int main(int argc, char *args[])
{
    
//    Player player1("RedGuy.png", 64, SCREEN_HEIGHT - 128);
//   Player player2("BlueGuy.png", SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128);

    // Simple game loop
    init();
    bool quit = false;
    SDL_Event event;

    while (!quit) {
    
        // Simple game loop
        // TODO: Add UI for the main menu 
        int option = mainMenu();
        std::string playerName;
        switch (option) {
            case gameState::PLAY:
                play();
                quit = true;
                break;
            case gameState::REGISTER_USER:
                registerUser(DB);
                break;
            case gameState::SELECT_USER:
                playerName = selectUser(DB);
                std::cout << playerName << std::endl; // For logging
                break;
            case gameState::QUIT:
                quit = true;
                break;
            case gameState::SHOW_ALL_USERS:
                // For debug
                showAll(DB);
                break;
        }

        /*
        // Clear the screen
        screen.clear();

        // Update objects
        player1.update();
        player2.update();

        // Draw the images
        screen.draw(player1);
        screen.draw(player2);

        // Update the surface            
        screen.update();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_w) {  
                    player1.jump(); 
                }

                if (event.key.keysym.sym == SDLK_a) {
                    player1.move_left();
                } else if (event.key.keysym.sym == SDLK_d) {
                    player1.move_right();
                }


                if (event.key.keysym.sym == SDLK_UP) {
                    player2.jump();
                }

                if (event.key.keysym.sym == SDLK_LEFT) {
                    player2.move_left();
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    player2.move_right();
                }
            }
            if (event.type == SDL_KEYUP)
            {
                // FIXME: Feels clunky right, when you stop you lose all 
                // momentum, would rather it act like jumping and slowly stop
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    player1.stop();
                }

                 if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    player2.stop();
                 } 
            }
            */
    } 
    return 0;
}


int mainMenu()
{
    bool quit = false;
    SDL_Event event;
    while (1) {
        // Clear the screen
        screen.clear();
        screen.update();

        // Loop over every SDL_Event stored this frame
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true; 
            else if (event.type == SDL_KEYDOWN) {
                int key = event.key.keysym.sym;

                if (key == SDLK_p) { return gameState::PLAY; }  // Play the game
                if (key == SDLK_r) { return gameState::REGISTER_USER; }  // Register a profile with the db
                if (key == SDLK_s) { return gameState::SELECT_USER; }  // Select a user
                if (key == SDLK_q) { return gameState::QUIT; }  // Quit
                if (key == SDLK_a) { return gameState::SHOW_ALL_USERS; }  // ShowAllUsers for debug purposes
            }
            
            if (quit) return gameState::QUIT;
        }
        SDL_Delay(FPS_MS);
    }
}


void init()
{
    int exit = 0;
    char* messageError;
    // First make sure file exists:
    std::ifstream file;
    file.open("userbase.db");
    if (!(file)) {
        exit = sqlite3_open("userbase.db", (&DB));
        exit = initDB(DB);
        std::cout << "test";
    } else { 
        exit = sqlite3_open("userbase.db", (&DB));
        std::cout << "test2";
    }
     
}


void play()
{
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Clear the screen
        screen.clear();

        // Update the players
        player1.update();
        player2.update();

        // Collision Checking
        if (player1.punching()) {
            if (player1.fist_rect_.x < player2.right() && 
                player1.fist_rect_.x + player1.fist_rect_.w > player2.left() &&
                player1.fist_rect_.y < player2.bottom() && 
                player1.fist_rect_.y + player1.fist_rect_.h > player2.top()) {
               
                player1.stop_punching();
                player2.hit();
            }
        }

         if (player2.punching()) {
            if (player2.fist_rect_.x < player1.right() && 
                player2.fist_rect_.x + player2.fist_rect_.w > player1.left() &&
                player2.fist_rect_.y < player1.bottom() && 
                player2.fist_rect_.y + player2.fist_rect_.h > player1.top()) {
                
                player2.stop_punching();
                player1.hit();
            }
         }
        
         std::cout << "Player1: " << player1.health() << std::endl;
         std::cout << "Player2: " << player2.health() << std::endl;

         if (player1.health() < 0) {
            std::cout << "Player2 Won" << std::endl;
         }
         if (player2.health() < 0) {
            std::cout << "Player1 Won" << std::endl;
         }

    
        // Draw the characters to the screen
        player1.draw();
        player2.draw();

        // Update the surface
        screen.update();



        // KeyHandling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;

            else if (event.type == SDL_KEYDOWN) { 
                int key = event.key.keysym.sym;
                
                // Player1 Key Handling
                if (key == SDLK_w) { 
                    player1.jump();
                }

                if (key == SDLK_a) { 
                    player1.move_left();
                } else if (key == SDLK_d) {
                    player1.move_right();
                }

                // KEYS FOR PUNCHING ARE SUBJECT TO CHANGE
                if (key == SDLK_f) {
                    player1.punch();
                }

                // Player2 Key Handling 
                if (key == SDLK_UP) {
                    player2.jump();
                }

                if (key == SDLK_LEFT) { 
                    player2.move_left();
                } else if (key == SDLK_RIGHT) {
                    player2.move_right();
                }

                if (key == SDLK_l) {
                    player2.punch();
                }
            }

            else if (event.type == SDL_KEYUP) {
                int key = event.key.keysym.sym;
                // FIXME: Feels clunky when stopping and losing all momentum
                if (key == SDLK_a || key == SDLK_d) {
                    player1.stop();
                }

                if (key == SDLK_LEFT || key == SDLK_RIGHT) {
                    player2.stop();
                }
            }
        }
        SDL_Delay(FPS_MS);
    }
}
