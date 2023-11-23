#ifndef FIELD_H
#define FIELD_H
#include <vector>


const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 10;

class Field
{
public:
	void Generate();
	void UpdateState();
	void DrawMap();

	std::vector<std::vector<wchar_t>> layout;
};

#endif
