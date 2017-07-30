//
//  main.cpp
//  chip8-xcode
//
//  Created by Tony Lukasavage on 7/4/17.
//  Copyright © 2017 Tony Lukasavage. All rights reserved.
//

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Cell.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int PIXEL_SIZE = 2;
const int X_SIZE = SCREEN_WIDTH/PIXEL_SIZE;
const int Y_SIZE = SCREEN_HEIGHT/PIXEL_SIZE;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// cells
std::vector<std::vector<Cell>> cells(X_SIZE, std::vector<Cell>(Y_SIZE));

int main(int argc, const char * argv[]) {
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    //Create window
    window = SDL_CreateWindow( "4D Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    // initialize cells
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            cells[x][y].init(gRenderer, x, y, PIXEL_SIZE, rand() % 100 > 49, &cells);
        }
    }
    
    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;
    
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( gRenderer );
        
        // next generation of cells
        Cell *cell;
        for (int x = 0; x < X_SIZE; x++) {
            for (int y = 0; y < Y_SIZE; y++) {
                cell = &cells[x][y];
                cell->nextGeneration();
                cell->draw();
            }
        }
        
        for (int x = 0; x < X_SIZE; x++) {
            for (int y = 0; y < Y_SIZE; y++) {
                cell = &cells[x][y];
                cell->alive = cell->nextAlive;
            }
        }
        
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( window );
    window = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
    
    return 0;
}
