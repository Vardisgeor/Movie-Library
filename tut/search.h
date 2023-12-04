#pragma once
#include "widgets.h"
#include "config.h"

class Search : public Widgets
{
	

public:
	void draw() override;
	void update() override;
	void init() override;


	void drawTime();
	void drawTimeWindow();
	void setTimeStatus(bool i);
	bool getTimeStatus();
	bool changeMovies();
	void setSearchStatus(bool b);
	char input();
	int getFrom();
	int getTo();
	const char* getSearch();
	bool getSearchStatus();
};