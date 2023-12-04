#include "game.h"
#include "graphics.h"
#include "config.h"
#include "movies.h"
#include "search.h"


bool f = true;
bool searchStat = false;
bool findMovies = false;
bool moviesYear = false;
const char* category = " " ;
const char* searchMovie;
const char* searchMoviePhoto;
list<Movies*> onemovie;


void Game::update()
{
	for (auto movies : m_movies) {
			movies->update();
	}

	// mouse state 

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	menu = new Menu();
	movies = new Movies();
	search = new Search();

	if (menu) {
		menu->update();
	}
	
	if (movies) {
		movies->update();
	}

	if (search) {
		search->update();
	}
	
	
	// Hightlight movie border
	for (auto movies : m_movies) {

		if (movies->contains(mx, my)) {
			movies->setHightlight(true);
		}
		else {
			movies->setHightlight(false);
		}
	}
	
}

void Game::draw()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	graphics::Brush br;
	br.fill_color[0] = 0.65f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 1.0f;
	graphics::setWindowBackground(br); 
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush br1;
	br1.fill_color[0] = 0.5f;
	br1.fill_color[1] = 0.1f;
	br1.fill_color[2] = 0.3f;
	graphics::setWindowBackground(br1);
	br1.outline_opacity = 1.1f;
	graphics::drawRect(CANVAS_WIDTH / 16, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 4, CANVAS_HEIGHT +10, br1);

	graphics::Brush br2;
	br2.texture = std::string(ASSETS_PATH) + "sfera.png";
	br2.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 11, 70 , 200, 60, br2);
	
	bool status = false;
	std::list<Movies*> mc_movies;
	std::list<Movies*> my_movies;

	if (menu) {
		menu->draw();
		status = menu->getStat();
		if (status) {
			category = menu->getc();
		
		}
	}

	if (search) {
		
		if (search->changeMovies()) {
			moviesYear = true;
			movies->setOffset2();
			status = false;
			search->setTimeStatus(false);
		}

		for (int i = 0; i < 7; i++) {
			if (mx >= CANVAS_WIDTH / 11 - 70 && mx <= CANVAS_WIDTH / 11 + 70 && my >= CANVAS_HEIGHT - 90 - 72 * i / 1.5 - 15 && my <= CANVAS_HEIGHT - 90 - 72 * i / 1.5 + 15) {
				if (ms.button_left_pressed) {
					moviesYear = false;
				}
			}
		}
	}


	if (!search->getSearchStatus()) {

	
		if (!onemovie.empty()) {
			onemovie.pop_back();
		}

		if (status && category != "ALL" && !moviesYear) { 

			//moviesYear = false;
			int o = 0;

			for (auto mov : m_movies) {
				if (mov->getType1() == category || mov->getType2() == category) {
					mc_movies.push_front(mov);
				}
			}

			// reset the pos in the category section 

			for (auto mov : mc_movies) {
				mov->setPosX((CANVAS_WIDTH - 300) * (o % 4) / 5.0f + 270);
				mov->setPosY((CANVAS_HEIGHT - 100) * (o / 4) / 2.0f + 140);

				o++;
			}

			// draw new category

			movies->drawCategory(category, mc_movies);
			movies->drawSum(mc_movies);

		}
		else {
			if (moviesYear) {
				my_movies.clear();

				int o = 0;

				for (auto movies : m_movies) {
					if (movies->getDate() >= search->getFrom() && movies->getDate() <= search->getTo()) {
						my_movies.push_back(movies);
					}
				}

				if (my_movies.empty()) {
					graphics::Brush br;
					graphics::setFont("OpenSans-Regular.ttf");
					br.fill_color[0] = 0.2f;
					br.fill_color[1] = 0.2f;
					br.fill_color[2] = 0.2f;
					graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 370, 30, "There  is  no  results!", br);
				}
				else {

					//set the position of every movie when its oressed

					for (auto movies : my_movies) {
						movies->setPosX((CANVAS_WIDTH - 300) * (o % 4) / 5.0f + 270);
						movies->setPosY((CANVAS_HEIGHT - 100) * (o / 4) / 2.0f + 140);

						o++;
					}

					movies->drawYear(my_movies, search->getFrom(), search->getTo());
					movies->drawSum(my_movies);
				}
			}
			else {

				int o = 0;
				for (auto mov : m_movies) {

					mov->setPosX((CANVAS_WIDTH - 300) * (o % 4) / 5.0f + 270);
					mov->setPosY((CANVAS_HEIGHT - 100) * (o / 4) / 2.0f + 140);

					o++;
				}

				for (auto movies : m_movies) {

					movies->draw();

					// change possition if there is a dragging

					movies->setPosY(movies->getPosOffset());
				}

				movies->drawSum(m_movies);
			}
		}
	
	}
	else {
		//when there is input to search

		searchMovie = search->getSearch();

		for (auto movies : m_movies) {
			if (((std::string)movies->getName() == (std::string)searchMovie)) {

				searchMoviePhoto = movies->getPhoto();

				if (onemovie.empty()) {
					onemovie.push_back(movies);
				}
				else {
					onemovie.pop_back();
					onemovie.push_back(movies);
				}

			}
		}

		if (!onemovie.empty()) {
			movies->drawSearch(searchMoviePhoto);
			movies->drawSum(onemovie);

		}
		else {
			// the search input doent correspond to any name on the database
			graphics::Brush br;
			graphics::setFont("OpenSans-Regular.ttf");
			br.fill_color[0] = 0.2f;
			br.fill_color[1] = 0.2f;
			br.fill_color[2] = 0.2f;
			graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 370, 30, "There  is  no  results!", br);
		}
	}
	

	if (search) {
		search->draw();
		search->drawTime();

		if (search->getTimeStatus()) {
			search->drawTimeWindow();

		}

	}

}


void Game::init()
{	
	const char* movie[24] = { "The Batman", "Midsommar", "Tenet", "Nope", "Salt", "Death On Nile", "The Tourist", "Black Swan",
						"Smile", "Good Will Hunting", "Avatar", "Interstellar", "Now You See Me", "The Godfather", "Everest",
						"Sausage Party","Girl, interrupted", "Bohemian","Apes", "Gravity","Polar Express","Evil Dead","Green Mile","Zodiac"};

	const char* photo[24] = { "batman1.png", "Midsommar.png", "tenet1.png", "nope.png", "salt1.png", "nile1.png", "tourist1.png", "black1.png",
							"smile1.png", "GWH.png", "avatar1.png", "Interstellar.png", "NowYouSeeMe.png", "got1.png", "everest1.png", "sausage.png", 
							"Girl_Int.png", "Bohemian.png", "Apes.png", "Gravity.png","polar.png","evil.png", "green.png","zodiac.png"};



	int date[24] = { 2022,2019,2020,2022,2010,2022,2011,2009,2022,1999,2022,2014,2013,1972,2015,2016,1999,2018,2014,2013,2004,2012,1999,2007};

	const char* dir[24] = { "Matt Reeves","Ari Aster", "Christopher Nolan","Jordan Peele","Phillip Noyce", "Kenneth Branagh" ,"Florian Henckel","Darren Aronofsky",
						"Parker Finn" ,"Gus Van Sant","James Cameron", "Christopher Nolan", "Louis Leterrier", "Francis Ford Coppola", "Baltasar Kormákur", "Greg Tiernan", "James Mangold",
						"Bryan Singer", "Matt Reeves", "Alfonso Cuaron", "Robert Zemeckis", "Fede Alvarez","Frank Darabont","David Fincher"};

	const char* type[24][2] = { {"Action","Crime"},{"Drama","Horror"},{"Action","Sci-fi"},{"Action","Sci-fi"},{"Action","Mystery"},{"Comedy","Horror"},{"Drama",""},{"Drama",""},
								{"Horror",""},{"Drama",""},{"Fantasy","Action"},{"Sci-fi","Drama"},{"Fantasy","Crime"},{"Action","Crime"},{"Horror","Action"},{"Fantasy",""}, 
								{"Horror","Drama"}, {"Drama",""},{"Action", "Fantasy"}, {"Sci-fi", "Drama"},{"Sci-fi", "Fantasy"},{"Horror"," "},{"Crime","Fantasy"},{"Crime","Mystery"} };


	const char* prot[24] = { "Robert Pattinson, Zoe Kravitz", "Florence Pugh, Jack Reynor","John Washington, Robert Pattinson" , "Daniel Kaluuya, Keke Palmer",
							"Angelina Jolie, Liev Schreiber", "Tom Bateman, Annette Bening","Johnny Depp, Angelina Jolie" , "Natalie Portman, Mila Kunis",
							"Sosie Bacon, Jessie T. Usher", "Robin Williams, Matt Damon","Sam Worthington, Zoe Saldana" , "Matthew McConaughey, Anne H.",
							"Jesse Eisenberg, Common", "Marlon Brando, Al Pacino","Jason Clarke, Ang Phula Sherpa" , "Seth Rogen, Kristen Wiig",
							"Angelina Jolie, Winona Ryder", "Rami Malek, Lucy Boynton", "Gary Oldman, Keri Russell", "Sandra Bullock, George Clooney",
							"Tom Hanks, Chris Coppoa","Jane Levy, Shiloh Fernandez","Tom Hanks, Michael Duncan","Jake Gyllenhaal, Mark Ruffalo"};

	const char* summary[24] = { "When a sadistic serial killer begins\nmurdering key political figures in\nGotham, Batman is forced to\ninvestigate the city's hidden\ncorruption and question his family's\ninvolvement.",
		"A couple travels to Northern Europe\n to visit a rural hometown's fabled\nSwedish mid-summer festival.\nWhat begins as an idyllic retreat\nquickly devolves into an increasingly\nviolentand bizarre competition at the\nhands of a pagan cult.",
		"Armed with only one word, Tenet,\n and fighting for the survival of\n the entire world, a Protagonist\n journeys through a twilight world\n of international espionage on a\n mission that will unfold in\n something beyond real time.",
		"The residents of a lonely gulch in\n inland California bear witness to an\n uncanny and chilling discovery.",
		"A CIA agent goes on the run after\n a defector accuses her of being a\n Russian spy.",
		"While on vacation on the Nile,\n Hercule Poirot must investigate\n the murder of a young heiress.",
		"Revolves around Frank, an\n American tourist visiting Italy to\n mend a broken heart. Elise is\n an extraordinary woman who\n deliberately crosses his path.",
		"A committed dancer struggles to\n maintain her sanity after winning\n the lead role in a production\n of Tchaikovsky's 'Swan Lake'.",
		"After witnessing a bizarre,\n traumatic incident involving\n a patient, Dr. Rose Cotter starts\n experiencing frightening\n occurrences that she can't explain.",
		"Will Hunting, a janitor at M.I.T., has\n a gift for mathematics, but needs\n help from a psychologist to find\n direction in his life.",
		"Jake Sully lives with his newfound\n family formed on the extrasolar\n moon Pandora. Once a familiar\n threat returns to finish what was\n previously started, Jake must work\n with Neytiri and the army of the\n Na'vi race to protect their home.",
		"A team of explorers travel through\na wormhole in space in an\nattempt to ensure humanity's\nsurvival.",
		"An F.B.I. Agent and an Interpol\nDetective track a team of illusionists\nwho pull off bank heists during their\nperformances, and reward their\naudiences with the money.",
		"The aging patriarch of an organized\n crime dynasty in postwar New\n York City transfers control of his\n clandestine empire to his reluctant\n youngest son.",
		"The story of New Zealand's Robert\n 'Rob' Edwin Hall, who on May 10,\n 1996, together with Scott Fischer,\n teamed up on a joint expedition to\n ascend Mount Everest.",
		"A sausage strives to discover the\ntruth about his existence.",
		"Based on writer Susanna Kaysen's\n account of her 18-month stay at\n a mental hospital in the late 1960s.",
		"The story of the legendary British\n rock band Queen and lead\n singer Freddie Mercury, leading up\n to their famous performance at\n Live Aid (1985).",
		"The fragile peace between apes\n and humans is threatened as\n mistrust and betrayal threaten to\n plunge both tribes into a war for\n dominance over the Earth.",
		"Two astronauts work together\n to survive after an accident\n leaves them stranded in space." ,
		"On Christmas Eve, a young boy\nembarks on a magical adventure\nto the North Pole on the Polar\nExpress, while learning about\nfriendship, bravery, and the\nspirit of Christmas.",
		"Five friends travel to a cabin\nin the woods, where they\nunknowingly release flesh-\npossessingdemons.",
		"The lives of guards on Death Row\nare affected by one of their \ncharges: a black man accused of\nchild murderand rape, yet who\nhas a mysterious gift.",
		"A San Francisco cartoonist become\nan amateur detective obsessed\nwith tracking down the Zodiac Killer\nan unidentified individual who\nterrorizes Northern California\nwith a killing spree."};

	int k = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			Movies* m = new Movies();
			m->setName(movie[k]);
			m->setDate(date[k]);
			m->setDirector(dir[k]);
			m->setType1(type[k][0]);
			m->setType2(type[k][1]);
			m->setProt(prot[k]);
			m->setSum(summary[k]);
			m->setPhoto(photo[k]);
			k++;

			m_movies.push_front(m);
		}
	}
}

Game::Game()
{
}

Game::~Game()
{
	for (auto m : m_movies) {
		delete m;
	}
	for (auto m : mc_movies) {
		delete m;
	}
	for (auto m : my_movies) {
		delete m;
	}

	m_movies.clear();
	my_movies.clear();
	mc_movies.clear();
}
