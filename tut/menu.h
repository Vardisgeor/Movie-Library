#pragma once
#include "widgets.h"
#include "config.h"

class Menu : public Widgets
{
	const char* cat;

public:
	void draw() override;
	void update() override;
	void init() override;
	bool getStat();
	const char* getc();
	void setStat(bool b);

	const char* getCatType() { return cat; }

};
 
