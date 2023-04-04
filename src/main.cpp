
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>

#include "Constants.h"
#include "Player.h"


std::string title = "Street Fighter Clone";
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;


bool init();
void close();

int main(int argc, char *args[])
{
    // Start SDL and create window
    if (!init()) {
        printf("Failed  to initialize!\n");
    } else {
        
        Player player1("RedGuy.png", 64, SCREEN_HEIGHT - 128);
        Player player2("BlueGuy.png", SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128);

        // Simple game loop
        bool quit = false;
        SDL_Event event;
        while (!quit) {

            // Clear the screen
            SDL_FillRect(surface, NULL, 
                    SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

            // Update objects
            player1.update();
            player2.update();

            // Add the images
            SDL_BlitSurface(player1.surface(), NULL, surface, player1.rect());
            SDL_BlitSurface(player2.surface(), NULL, surface, player2.rect());

            // Update the surface            
            SDL_UpdateWindowSurface(window);

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
            }

            SDL_Delay(33); // 30fps
        }
    }
    
    close();
    return 0;
}


bool init()
{
    // Flag to decide if everything was initialized right
    bool success = true;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
         printf("SDL could not initialize...SDL_Error: %s\n", SDL_GetError());       
         success = false;
    }
    else {
        // Create window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get surface
            surface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}


void close()
{
    // Deallocate surface
    SDL_DestroyWindow(window);
    SDL_Quit();
}
