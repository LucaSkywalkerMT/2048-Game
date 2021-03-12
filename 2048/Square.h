#pragma once
#include <string>
#include "Type.h"
using namespace std;
class Square
{
private:
	Type type;
	int value;
public:
	Square(Type type = NUL, int value = 0) : type(type), value(value) {}
	Type getType() const { return type; }
	int getValue() { return value; }
	void setValue(int val) { value = val; }
	~Square() {}
};

