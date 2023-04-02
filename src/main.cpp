
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
std::string title = "Street Fighter Clone";
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Surface* player1 = NULL;
SDL_Rect player1_rect = { 64, SCREEN_HEIGHT - 128 ,64, 128};
SDL_Surface* player2 = NULL;
SDL_Rect player2_rect = { SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, 64, 128};


bool init();
bool loadMedia();
void close();

int main(int argc, char *args[])
{
    // Start SDL and create window
    if (!init()) {
        printf("Failed  to initialize!\n");
    } else {
        if (!loadMedia()) { 
            printf("Failed to load media!\n");
        } else { 
        
            // Simple game loop
            bool quit = false;
            SDL_Event event;
            while (!quit) {

                SDL_FillRect(surface, NULL, 
                        SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

                // Add the images
                SDL_BlitSurface(player1, NULL, surface, &player1_rect);
                SDL_BlitSurface(player2, NULL, surface, &player2_rect);

                // Update the surface            
                SDL_UpdateWindowSurface(window);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quit = true;

                    else if (event.type == SDL_KEYDOWN) {
                        int key = event.key.keysym.sym;

                        // Player 1 movements
                        if (key == SDLK_a)
                            player1_rect.x -= 5;

                        else if (key == SDLK_d)
                            if (player1_rect.x + player1_rect.w < SCREEN_WIDTH) {
                                player1_rect.x += 5;
                            }
                        
                        if (key == SDLK_w)
                            player1_rect.y -= 64;

                        // Player 2 movements
                        if (key == SDLK_LEFT)
                            player2_rect.x -= 5;
                        
                        else if (key == SDLK_RIGHT)
                            if (player2_rect.x + player2_rect.w < SCREEN_WIDTH) { 
                                player2_rect.x += 5;
                            }
                        
                        if (key == SDLK_UP)
                            player2_rect.y -= 64;
                    }
                }
                // Gravity
                if (player1_rect.y + player1_rect.h < SCREEN_HEIGHT) {
                    player1_rect.y += 5;
                } else {
                    player1_rect.y = SCREEN_HEIGHT - player1_rect.h;
                }

                if (player2_rect.y + player2_rect.h < SCREEN_HEIGHT) { 
                    player2_rect.y += 5;
                } else {
                    player2_rect.y = SCREEN_HEIGHT - player2_rect.h;
                }
                SDL_Delay(33);
            }
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


bool loadMedia()
{
    // Loadingn flag
    bool success = true;

    // Load images
    player1 = IMG_Load("BlueGuy.png");
    player2 = IMG_Load("RedGuy.png");

    // Add more indepth error logging
    if (player1 == NULL || player2 == NULL) {
        printf("Unable to load an image! SDL_Error: %s\n: ", SDL_GetError());
        success = false;
    }

    return success;
}


void close()
{
    // Deallocate surface
    SDL_FreeSurface(player1);
    SDL_FreeSurface(player2);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
