#include "movies.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>


int i = 0;
bool flag = true;
const char* n;
const char* d;
const char* t1;
const char* t2;
int y;
const char* prot;
const char* sum;
const char* cat;
list<Movies*> mtemp;
int j = 0;
float offset = 0;
float offset2 = 0;
float position = 0;
float position2 = 0;


void Movies::draw()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (ms.dragging) {
		if (ms.prev_pos_y > ms.cur_pos_y) {
			if (offset < 550) {
				offset += 5;
			}
		}
		else if(ms.prev_pos_y < ms.cur_pos_y){
			if (offset > 0) {
				offset -= 5;
			}
		}
	}
	
	std::string movie[24] = { "zodiac.png","green.png","evil.png", "polar.png","Gravity.png", "Apes.png", "Bohemian.png", "Girl_Int.png", "sausage.png", "everest1.png", "got1.png", "NowYouSeeMe.png", "Interstellar.png", "avatar1.png", "GWH.png", "smile1.png",
							"black1.png", "tourist1.png", "nile1.png", "salt1.png", "nope.png", "tenet1.png", "Midsommar.png", "batman1.png",};

	float h = 1.0f * m_hightlighted;

	graphics::Brush br;
	br.texture = std::string(ASSETS_PATH) + movie[i];
	br.outline_opacity = 0.5f+h;
	graphics::drawRect(m_pos[0], m_pos[1] - offset, 120, 182, br);
	setPosOffset(m_pos[1] - offset);
	if (i < 23) {
		i++;
	}else {
		i = 0;
	}

}


void Movies::drawCategory(const char* c, list<Movies*> m)
{
	int count = 0;
	float h = 1.0f * m_hightlighted;

	for (auto movies : m) {

		if (movies->getType1()== c || movies->getType2() == c) {

			graphics::Brush br;
			br.texture = std::string(ASSETS_PATH) + movies->getPhoto();
			br.outline_opacity = 0.5f + h;
			graphics::drawRect((CANVAS_WIDTH - 300) * (count%4) / 5.0f + 270, (CANVAS_HEIGHT - 100) * (count/4) / 2.0f + 140, 120, 182, br);

			count++;
		}
	}
	
}

void Movies::drawYear(list<Movies*> m, int a, int b) {

	int count = 0;

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	
	//size of the maximum offset

	int size = 0;

	if (m.size() % 4 == 0) {
		size = (m.size() / 4) * 50;
	}
	else {
		size = (m.size() / 4 + 1) * 170 - 320;
	}
	

	if (ms.dragging) {
		if (ms.prev_pos_y > ms.cur_pos_y) {
			if (offset2 < size) {
				offset2 += 35;
			}
		}
		else if (ms.prev_pos_y < ms.cur_pos_y) {
			if (offset2 > 0) {
				offset2 -= 35;
			}
		}
	}

	for (auto movies : m) {

		graphics::Brush br;
		br.texture = std::string(ASSETS_PATH) + movies->getPhoto();
		br.outline_opacity = 0.5f;
		graphics::drawRect((CANVAS_WIDTH - 300) * (count % 4) / 5.0f + 270, (CANVAS_HEIGHT - 100) * (count / 4) / 2.0f + 140 - offset2 , 120, 182, br);
		setPosOffset((CANVAS_HEIGHT - 100) * (count / 4) / 2.0f + 140 - offset2);
		movies->setPosY(movies->getPosOffset());
		count++;
		
	}
}

void Movies::drawSearch(const char* s) {

	
	graphics::Brush br;
	br.texture = std::string(ASSETS_PATH) + s; 
	br.outline_opacity = 0.5f ;
	graphics::drawRect(270 , 140, 120, 182, br);

}



void Movies::drawSum(list<Movies*> m) {

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (flag || m.size()==1) {
		for (auto movies : m) {

			n = movies->getName();
			d = movies->getDirector();
			t1 = movies->getType1();
			t2 = movies->getType2();
			y = movies->getDate();
			prot = movies->getProt();
			sum = movies->getSum();
		}
	}
	
	if (ms.button_left_pressed) {

		flag = false; // to stay and dont change the name to the previous one.
		for (auto movies : m) {

			if (movies->contains(mx, my)) {
				n = movies->getName();
				d = movies->getDirector();
				t1 = movies->getType1();
				t2 = movies->getType2();
				y = movies->getDate();
				prot = movies->getProt();
				sum = movies->getSum();
				
			}
		}
	}

	graphics::Brush br3;
	br3.fill_color[0] = 0.5f;
	br3.fill_color[1] = 0.1f;
	br3.fill_color[2] = 0.3f;
	graphics::setWindowBackground(br3);
	br3.outline_opacity = 1.0f;
	graphics::drawRect(CANVAS_WIDTH - 120, CANVAS_HEIGHT / 2 +20, 220, 440, br3);
	graphics::setFont("OpenSans-Semibold.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH -220, CANVAS_HEIGHT -  420 , 27, n, br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 217, CANVAS_HEIGHT - 405, 13, t1, br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 175, CANVAS_HEIGHT - 405, 13, "   | ", br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 160, CANVAS_HEIGHT - 405, 13, t2, br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 0.5f;
	br3.fill_color[1] = 0.5f;
	br3.fill_color[2] = 0.5f;
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 350, 15, "YEAR", br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 170, CANVAS_HEIGHT - 350, 15, to_string(y), br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 0.5f;
	br3.fill_color[1] = 0.5f;
	br3.fill_color[2] = 0.5f;
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 320, 15, "DIRECTOR", br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 140, CANVAS_HEIGHT - 320, 15, d, br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 0.5f;
	br3.fill_color[1] = 0.5f;
	br3.fill_color[2] = 0.5f;
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 290, 15, "LEAD ACTORS", br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 275, 14, prot, br3);
	

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 0.5f;
	br3.fill_color[1] = 0.5f;
	br3.fill_color[2] = 0.5f;
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 240, 15, "SUMMARY", br3);

	graphics::setFont("OpenSans-Regular.ttf");
	br3.fill_color[0] = 1.0f;
	br3.fill_color[1] = 1.0f;
	br3.fill_color[2] = 1.0f;

	std::string str = sum;
	std::vector<std::string> tokens = splitString(str);
	int k = 0;
	for (auto const& token : tokens) {
		graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 225+k*15, 14, token, br3);
		k++;
	}

}

std::vector<std::string> Movies::splitString(const std::string& str)
{
	std::vector<std::string> tokens;

	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, '\n')) {
		tokens.push_back(token);
	}

	return tokens;
}

void Movies::setPosOffset(float x) {
	position = x;
}

float Movies::getPosOffset() {
	return position;
}

void Movies::setOffset2() {
	offset2 = 0;
}

bool Movies::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < 60;

}

void Movies::update()
{
}


void Movies::init()
{
}