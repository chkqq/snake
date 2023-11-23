#ifndef APPLE_H
#define APPLE_H

#include "Field.h"


class Apple
{ 
public:
	void Generate(const Field& field);
	void UpdateState(Field& field);

	int x;
	int y;
};

#endif


