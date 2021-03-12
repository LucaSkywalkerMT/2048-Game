#pragma once
#include "Square.h"
class Blank :
    public Square
{
public:

    Blank() : Square(BLANK) {}
    ~Blank() {}
};