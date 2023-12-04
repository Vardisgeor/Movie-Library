#pragma once
#include "menu.h"
#include "movies.h"
#include "search.h"

class Game 
{
	Menu* menu = nullptr;
	Movies* movies = nullptr;
	Search* search = nullptr;

	std::list<Movies*> m_movies;
	std::list<Movies*> mc_movies;
	std::list<Movies*> my_movies;

	Movies* s_movie = nullptr;
	
public:
	void draw();
	void update();
	void init();
	Game();
	~Game();

	list<Movies*> mov() {
		return m_movies;
	}
};
