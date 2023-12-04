#pragma once
#include "widgets.h"
#include "config.h"
#include <list>

#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

class Movies : public Widgets
{
	float m_pos[2];
	float m_color[3];
	int date;
	const char* name;
	const char* director;
	const char* protagonists;
	const char* type1;
	const char* type2;
	const char* summary ;
	const char* c;
	const char* photo;
	list<Movies*> m_m;
	list<Movies*> m;
	bool m_hightlighted = false;

public:
	void draw() override;
	void update() override;
	void init() override;

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	const char* getName() { return name; }
	const char* getPhoto() { return photo; }
	int getDate() { return date; }
	const char* getDirector() { return director; }
	const char* getProt() { return protagonists; }
	const char* getType1() { return type1; }
	const char* getType2() { return type2; }
	const char* getSum() { return summary; }
	float getPosOffset();


	void setOffset2();
	void setPosOffset(float x);
	void setSum(const char* s) { summary = s; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setHightlight(bool l) { m_hightlighted = l; }
	bool contains(float x, float y);
	vector<string> splitString(const string& str);
	void drawSum(list<Movies*> m);
	void drawCategory(const char* c, list<Movies*> m);
	void drawYear(list<Movies*> m, int a, int b);
	void drawSearch(const char* s);
	void setName(const char* n) { name = n; }
	void setPhoto(const char* p) { photo = p; }
	void setDate(int d) { date = d; }
	void setDirector(const char* d) { director = d; }
	void setProt(const char* p) { protagonists = p; }
	void setFlag(bool b);
	void setType1(const char* a) {
		type1 = a;
	}
	void setType2(const char* a) {
		type2 = a;
	}


};
