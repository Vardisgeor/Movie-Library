#include "menu.h"
#include "graphics.h"
#include "config.h"

bool pressed = false;
 
const char* c = "";

void Menu::draw()
{
	std::string menuBar[7] = { "Action","Sci-fi","Crime","Drama","Fantasy","Horror","ALL" };

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	for (int i = 0; i < 7; i++) {

		graphics::Brush br1;

		if (mx >= CANVAS_WIDTH / 11 -70 && mx <= CANVAS_WIDTH / 11 + 70 && my >= CANVAS_HEIGHT - 90 - 72 * i / 1.5 -15 && my <= CANVAS_HEIGHT - 90 - 72 * i / 1.5 +15) {
			br1.fill_color[0] = 0.8f;
			br1.fill_color[1] = 0.4f;
			br1.fill_color[2] = 0.3f;
			if (ms.button_left_pressed) {
				pressed = true;
				
				if (i == 0) {
					c = "Action";
				}
				else if (i == 1) {
					c = "Sci-fi";
				}
				else if (i == 2) {
					c = "Crime";
				}
				else if (i == 3) {
					c = "Drama";
				}
				else if (i == 4) {
					c = "Fantasy";
				}
				else if (i == 5) {
					c = "Horror";
				}
				else {
					c = "ALL";
				}
			}

		}
		else {
			br1.fill_color[0] = 0.6f;
			br1.fill_color[1] = 0.4f;
			br1.fill_color[2] = 0.3f;
		}
		
		graphics::setWindowBackground(br1);
		graphics::drawRect(CANVAS_WIDTH/11, CANVAS_HEIGHT -90 - 72*i/1.5, 140, 30, br1);
		graphics::setFont("OpenSans-Regular.ttf");
		br1.fill_color[0] = 0.0f;
		br1.fill_color[1] = 0.0f;
		br1.fill_color[2] = 0.0f;
		graphics::drawText(CANVAS_WIDTH / 15, CANVAS_HEIGHT - 85 - 72 * i / 1.5, 16, menuBar[i], br1);
		graphics::resetPose();
	}

}

bool Menu::getStat() {
	return pressed;
}

void Menu::setStat(bool b){
	pressed = b;
}

const char* Menu::getc() {
	return c;
}


void Menu::update()
{
}

void Menu::init()
{
}
