#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "Surface.h"


Surface::Surface(std::string title, int width, int height)
    : window_(NULL), surface_(NULL)
{
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        // Throw an error if it could not be initialized for some reason
        printf("SDL could not initialize... SDL_Error: %s\n", SDL_GetError());
        throw InitializationError();
    } 
    else 
    {
        // Create the games window
       window_ = SDL_CreateWindow(title.c_str(), 
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
       if (window_ == NULL) { 
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            throw InitializationError();
       } else {
            // Get the surface we draw on from the window
            surface_ = SDL_GetWindowSurface(window_);
       }
    }
}


Surface::~Surface()
{
    // Cleanup
    // Deallocate the window/surface and quit SDL
    SDL_DestroyWindow(window_);
    SDL_Quit();
}


// Paints black over the entire screen, as if clearing everything that was on it
void Surface::clear()
{
    SDL_FillRect(surface_, NULL,
            SDL_MapRGB(surface_->format, 0x00, 0x00, 0x00));
}


// Draw the surface passed to the main surface at the rect passed
void Surface::draw(SDL_Surface* surface, SDL_Rect rect)
{
    SDL_BlitSurface(surface, NULL, surface_, &rect);
}


// Update the window to show latest changes
void Surface::update() 
{
    SDL_UpdateWindowSurface(window_);
}
