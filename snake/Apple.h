#ifndef APPLE_H
#define APPLE_H

#include "Field.h"


class Apple
{ 
public:
	Apple Generate(const Field& field);
	void UpdateState(Apple& apple, Field& field);

	int x;
	int y;
};

#endif

