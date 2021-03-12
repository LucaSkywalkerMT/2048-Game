#pragma once
#include "Square.h"
class Bomb :
    public Square
{
public:
    Bomb() : Square(BOMB) {}
    ~Bomb() {}
};

