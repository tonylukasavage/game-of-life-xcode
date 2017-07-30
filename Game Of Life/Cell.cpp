//
//  Cell.cpp
//  Game Of Life
//
//  Created by Tony Lukasavage on 7/15/17.
//  Copyright © 2017 Tony Lukasavage. All rights reserved.
//

#include "Cell.hpp"
#include <SDL2/SDL.h>

Cell::Cell () {}

void Cell::init(SDL_Renderer* renderer, int x, int y, int size, bool alive, std::vector<std::vector<Cell>> *cells) {
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->size = size;
    this->alive = alive;
    this->nextAlive = alive;
    this->cells = cells;
    
    // with edge wrapping
    unsigned long maxX = cells->size() - 1,
    maxY = (*cells)[0].size() - 1,
    left = x - 1 < 0 ? maxX : x - 1,
    top = y - 1 < 0 ? maxY : y - 1,
    right = x + 1 > maxX ? 0 : x + 1,
    bottom = y + 1 > maxY ? 0 : y + 1;
    
    this->neighbors.push_back(std::make_pair(left, top));
    this->neighbors.push_back(std::make_pair(this->x, top));
    this->neighbors.push_back(std::make_pair(right, top));
    this->neighbors.push_back(std::make_pair(right, this->y));
    this->neighbors.push_back(std::make_pair(right, bottom));
    this->neighbors.push_back(std::make_pair(this->x, bottom));
    this->neighbors.push_back(std::make_pair(left, bottom));
    this->neighbors.push_back(std::make_pair(left, this->y));
}

void Cell::draw() {
    int color = this->nextAlive ? 0xFF : 0x00;
    SDL_Rect fillRect = { x * size, y * size, size, size };
    SDL_SetRenderDrawColor( renderer, color, color, color, 0xFF );
    SDL_RenderFillRect( renderer, &fillRect );
}

void Cell::nextGeneration() {
    int nX, nY, count = 0;
    for (std::pair<int,int> coords : neighbors) {
        std::tie(nX, nY) = coords;
        if ((*(this->cells))[nX][nY].alive) { count++; }
    }
    
    if (this->alive) {
        if (count < 2 || count > 3) {
            this->nextAlive = false;
        }
    } else if (count == 3) {
        this->nextAlive = true;
    } else {
        this->nextAlive = this->alive;
    }
}
