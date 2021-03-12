#pragma once
#include "Square.h"
class Number :
    public Square
{
private:
public:
    Number(int value) : Square(NUMBER, value) {}
    ~Number() {}
};