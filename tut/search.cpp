#include "search.h"
#include "movies.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

bool yet = false;
char ch = 0;
std::string s = "";
bool ready = false;
bool pr = false;
bool change = false;
int from = 0;
int to = 0;
const char* readyS;


void Search::draw()
{

	graphics::Brush br;
	br.fill_color[0] = 0.3f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.3f;
	graphics::setWindowBackground(br);
	br.outline_opacity = 0.7f;
	graphics::drawRect(CANVAS_WIDTH / 2 , 5, 1300, 60, br);

	br.fill_color[0] = 0.3f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.4f;
	graphics::setWindowBackground(br);
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 1.3 , 17, 250, 34, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	graphics::Brush br1;
	br1.texture = std::string(ASSETS_PATH) + "search.png";
	br1.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 1.3 - 105, 19, 56, 42, br1);

	if (!yet) {
		graphics::setFont("OpenSans-Light.ttf");
		br1.fill_color[0] = 0.6f;
		br1.fill_color[1] = 0.6f;
		br1.fill_color[2] = 0.6f;
		graphics::drawText(CANVAS_WIDTH / 1.3 - 90, 26, 15, "Search  a  movie", br1);
	}

	if (mx >= CANVAS_WIDTH / 1.3 -125 && mx <= CANVAS_WIDTH / 1.3 + 125 && my >= 4 && my <= 25 ) {
		
		if (ms.button_left_pressed || yet) {
			yet = true;

			br.fill_color[0] = 0.6f;
			br.fill_color[1] = 0.6f;
			br.fill_color[2] = 0.6f;
			graphics::setWindowBackground(br);
			br.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 1.3, 16, 250, 37, br);
		
			ch = input();	

		}
		else {
			yet = false;
			br.fill_color[0] = 0.4f;
			br.fill_color[1] = 0.2f;
			br.fill_color[2] = 0.4f;
			graphics::setWindowBackground(br);
			br.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 1.3, 17, 250, 34, br);
	
			br1.texture = std::string(ASSETS_PATH) + "search.png";
			br1.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 1.3 - 105, 19, 56, 42, br1);
		}

		std::string sym(1, ch);
		const char* ch2 = sym.c_str();


		if (ch == (char)(38)) {
			if (s.length() > 0) {
				s.pop_back();
			}
		}
		else if (ch == (char)(37)) {
			ready = true;
			readyS = s.c_str();
		}
		else if (ch == (char)(36)) {
			s += ' ';
		}
		else {
			s += ch2;
		}
		

		graphics::Brush br2;
		graphics::setFont("opensans-Regular.ttf");
		br2.fill_color[0] = 0.0f;
		br2.fill_color[1] = 0.0f;
		br2.fill_color[2] = 0.0f;
		graphics::drawText(CANVAS_WIDTH / 1.3 - 116, 27, 16, s, br2);
	}
	else {
		s = "";
		yet = false;
	}
	
	for (int i = 0; i < 7; i++) {
		if (mx >= CANVAS_WIDTH / 11 - 70 && mx <= CANVAS_WIDTH / 11 + 70 && my >= CANVAS_HEIGHT - 90 - 72 * i / 1.5 - 15 && my <= CANVAS_HEIGHT - 90 - 72 * i / 1.5 + 15) {
			if (ms.button_left_pressed) {
				setSearchStatus(false);
			}
		}
	}

}

void Search::drawTime(){

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);


	graphics::Brush br;
	
	if (mx >= CANVAS_WIDTH / 11 - 70 && mx <= CANVAS_WIDTH / 11 + 70 && my >= 460 - 15 && my <= 460 + 15) {
		br.fill_color[0] = 0.2f;
		br.fill_color[1] = 0.1f;
		br.fill_color[2] = 0.6f;

		if (ms.button_left_pressed) {
			pr = true;
			from = 0;
			to = 0;
		}
	}
	else {
		br.fill_color[0] = 0.4f;
		br.fill_color[1] = 0.2f;
		br.fill_color[2] = 0.8f;
	}
	graphics::setWindowBackground(br);
	br.outline_opacity = 1.0f;
	graphics::drawRect(CANVAS_WIDTH / 11, 460, 140, 30, br);
	graphics::setFont("OpenSans-Regular.ttf");
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(CANVAS_WIDTH / 15, 464, 16, "Year", br);

	
}

void Search::drawTimeWindow() {
	
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	graphics::Brush br;
	br.fill_color[0] = 0.1f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.1f;
	graphics::setWindowBackground(br);
	br.outline_opacity = 0.5f;
	br.fill_opacity = 0.9;
	graphics::drawRect(CANVAS_WIDTH / 2 - 20, CANVAS_HEIGHT / 2, 301, 230, br);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 0.0f;
	graphics::setWindowBackground(br);
	br.outline_opacity = 0.4f;
	graphics::setFont("OpenSans-Semibold.ttf");
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 42, CANVAS_HEIGHT / 2 - 83, 25, "Year", br);
	graphics::setFont("OpenSans-Regular.ttf");
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 157, CANVAS_HEIGHT / 2 -45, 20, "FROM: ", br);

	if (from != 0) {
		graphics::setFont("OpenSans-Regular.ttf");
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH / 2 - 90, CANVAS_HEIGHT / 2 - 45, 17, to_string(from), br);
	}

	graphics::setFont("OpenSans-Regular.ttf");
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH / 2 + 10, CANVAS_HEIGHT / 2 - 45, 20, "TO: ", br);

	if (to != 0) {
		graphics::setFont("OpenSans-Regular.ttf");
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH / 2 + 50, CANVAS_HEIGHT / 2 - 45, 17, to_string(to), br);
	}

	int year = 1997;
	int w;
	int h;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			w = CANVAS_WIDTH / 2 - 135 + 58 * j;
			h = CANVAS_HEIGHT / 2 - 18 + 28 * i;
			br.fill_color[0] = 0.2f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.2f;
			graphics::setWindowBackground(br);
			br.outline_opacity = 0.5f;
			graphics::drawRect(w,h, 44, 20, br);
			graphics::setFont("OpenSans-Regular.ttf");
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 1.0f;
			graphics::drawText(CANVAS_WIDTH / 2 - 150 + 58 * j, CANVAS_HEIGHT / 2 - 14 + 28 * i, 14, to_string(year), br);

			if (mx >= w - 21 && mx <= w + 21 && my >= h - 10 && my <= h + 10) {
				br.fill_color[0] = 0.7f;
				br.fill_color[1] = 0.7f;
				br.fill_color[2] = 0.7f;
				br.outline_opacity = 1.0f;
				graphics::drawRect(w, h, 44, 20, br);
				graphics::resetPose();

				if (ms.button_left_pressed) {
					change = false;
					if (from != 0 && to != 0) {
						from = year;
						to = 0;
					}
					else if (from != 0 && to == 0) {
						to = year;
						change = true;
					}
					else {
						from = year;
					}
				}

			}

			year++;
		}
	}


}

bool Search::getTimeStatus() {
	return pr;
	
}

bool Search::changeMovies() {
	return change;
}

void Search::setTimeStatus(bool i) {
	pr = i;
	change = i;
}

int Search::getFrom(){
	return from;
}

int Search::getTo() {
	return to;
}

char Search::input() {



	static float delay = 0.0f;
	delay += graphics::getDeltaTime();
	static int j = 0;
	char ascii = 0;

	for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; i++) {
		if (graphics::getKeyState((graphics::scancode_t)i)) {
			if (j == i && delay < 200.0f) {
				continue;
			}
			else {
				j = i;
				delay = 0.0f;
			}

			ascii = (char)(i + 93);

			if (graphics::getKeyState(graphics::SCANCODE_RSHIFT) || graphics::getKeyState(graphics::SCANCODE_LSHIFT)) {
				ascii -= 32;
			}

			
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		ascii = (char)(37);
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
			ascii = (char)(38);
	}

	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		ascii = (char)(36);
	}
	return ascii;

}

// functions to help for the print of the movie if there is an input to search

bool Search::getSearchStatus() {
	return ready;
}

const char* Search::getSearch() {
	return readyS;
}

void Search::setSearchStatus(bool b) {
	ready = b;
}


void Search::update()
{
}

void Search::init()
{
}
