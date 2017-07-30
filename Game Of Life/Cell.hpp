//
//  Cell.hpp
//  Game Of Life
//
//  Created by Tony Lukasavage on 7/15/17.
//  Copyright © 2017 Tony Lukasavage. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <tuple>

class Cell {
    SDL_Renderer* renderer;
    int x, y, size;
    std::vector<std::pair<int,int>> neighbors;
public:
    Cell ();
    void init(SDL_Renderer* renderer, int x, int y, int size, bool alive, std::vector<std::vector<Cell>> *cells);
    void draw();
    void nextGeneration();
    
    std::vector<std::vector<Cell>> *cells;
    bool alive, nextAlive;
};

#endif /* Cell_hpp */
