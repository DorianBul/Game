#include <config.h>	// all std and allegro includes and defined colors etc..

//using namespace std;

int main()
{
	// INITIAL PART
	if(!al_init()) 				{ return -1; }
	if(!al_install_keyboard()) 	{ return -1; }
	if(!al_init_image_addon()) 	{ return -1; }
	if(!al_init_font_addon()) 	{ return -1; }
	if(!al_init_ttf_addon()) 	{ return -1; }

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);			// 30 FPS
	ALLEGRO_TIMER* timerMenu = al_create_timer(1.0 / 10.0);		// 10 PFS
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
	ALLEGRO_FONT *fontMenu = al_load_font("AmaticSC-Regular.ttf", 80, 0);
	ALLEGRO_FONT *font2 = al_load_font("AmaticSC-Regular.ttf", 30, 0);
	if(!timer || !timerMenu || !queue || !disp || !fontMenu || !font2) { return -1; }
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(timerMenu));
	// BITMAPS
	ALLEGRO_BITMAP * bitmap = al_load_bitmap("img.jpg");
	ALLEGRO_BITMAP * tlo1 = al_load_bitmap("tlo1.png");
	ALLEGRO_BITMAP * tlo2 = al_load_bitmap("tlo2.png");

	if (!bitmap || !tlo1) { return -1; }
	// BITMAPS END
	// INITIAL PART END
	// RUNTIME VARIABLES
	ALLEGRO_EVENT event;
	//ALLEGRO_KEYBOARD_STATE keyState;
	Config conf;
	Player player;

	uint16_t choice = 0;

	bool runGame = true;
	bool menu = true;
	bool play = false;
	bool pause = false;

	// RUNTIME VARIABLES END
	// TIMERS INIT
	//al_start_timer(timer);
	al_start_timer(timerMenu);
	// TIMERS INIT END
	// MAIN LOOP
	while(runGame)
	{
		choice = 0;
		// MENU LOOP
		while(menu)
		{

			al_wait_for_event(queue, &event);
			if(event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(event.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE: runGame = false; menu = false; break;
				case ALLEGRO_KEY_UP: (choice)? choice-- : choice = 4; break;
				case ALLEGRO_KEY_DOWN: (choice!=4)? choice++ : choice = 0; break;
				case ALLEGRO_KEY_ENTER:
					if(choice==0)
					{
						menu = false;
						play = true;
						al_start_timer(timer);
						al_stop_timer(timerMenu);
					}
					else if(choice==1)
					{
						// TODO extras
					}
					else if(choice==2)
					{
						// TODO options
					}
					else if(choice==3)
					{
						bool wait = true;
						while(wait)
						{
							al_wait_for_event(queue, &event);
							if(event.type == ALLEGRO_EVENT_KEY_DOWN)
							{
								wait = false;
								break;
							}
							else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
							{
								runGame = false; menu = false; wait = false; break;
							}
							else if(event.type == ALLEGRO_EVENT_TIMER && event.timer.source == timerMenu)
							{
								al_clear_to_color(conf.getRGB(Color::black));
								al_draw_text(font2, conf.getRGB(Color::purple), conf.menuHorizontal, conf.creditsPos(2), 0, "Autorzy:");
								al_draw_text(font2, conf.getRGB(Color::orange), conf.menuHorizontal, conf.creditsPos(3), 0, "Dorian Bul");
								al_draw_text(font2, conf.getRGB(Color::pink), conf.menuHorizontal, conf.creditsPos(4), 0, "Mariusz Włodarczyk");
								al_draw_text(font2, conf.getRGB(Color::purple), conf.menuHorizontal, conf.creditsPos(5), 0, "Projekt:");
								al_draw_text(font2, conf.getRGB(Color::purple), conf.menuHorizontal, conf.creditsPos(6), 0, "C++ i Allegro5");
								al_flip_display();
							}
						}

					}
					else if(choice==4) { runGame = false; menu = false; }
					break;
				default:
					break;

				}
			}
			else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				runGame = false; menu = false; break;
			}
			else if(event.type == ALLEGRO_EVENT_TIMER && event.timer.source == timerMenu)
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(tlo1, 0, 0, 0);
				al_draw_text(fontMenu, conf.getRGB(Color::orange), conf.menuHorizontal+20, conf.menuPos(1), 0, (choice==0)?">  Play  <":"  Play");
				al_draw_text(fontMenu, conf.getRGB(Color::orange), conf.menuHorizontal, conf.menuPos(2), 0, (choice==1)?">  Highscores  <":"  Highscores");
				al_draw_text(fontMenu, conf.getRGB(Color::orange), conf.menuHorizontal+15, conf.menuPos(3), 0, (choice==2)?">  Options  <":"  Options");
				al_draw_text(fontMenu, conf.getRGB(Color::orange), conf.menuHorizontal+15, conf.menuPos(4), 0, (choice==3)?">  Credits  <":"  Credits");
				al_draw_text(fontMenu, conf.getRGB(Color::orange), conf.menuHorizontal+20, conf.menuPos(5), 0, (choice==4)?">  Exit  <":"  Exit");
				al_flip_display();
			}
		}
		// MENU LOOP END
		// GAME LOOP
		while(play)
		{

			al_wait_for_event(queue, &event);

			if(event.type == ALLEGRO_EVENT_TIMER)
			{
				if(pause)
				{
					al_draw_bitmap(tlo1, 0, 0, 0);
					al_draw_text(fontMenu, conf.getRGB(Color::purple), 320, conf.menuPos(1), 0, "PAUSE");
					al_draw_text(fontMenu, conf.getRGB(Color::purple), 120, conf.menuPos(3), 0, "Press any button to continue ");
					al_draw_text(fontMenu, conf.getRGB(Color::purple), 240, conf.menuPos(4), 0, "Press Esc to Exit");
					al_flip_display();
				}
				else
				{
					al_draw_bitmap(tlo2, 0, 0, 0);
					al_flip_display();
				}

			}
			else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if(pause)
				{
					switch(event.keyboard.keycode)
					{
					case ALLEGRO_KEY_ESCAPE:
						menu = true;
						play = false;
						pause = false;
						al_start_timer(timerMenu);
						al_stop_timer(timer);
						break;
					default:
						pause = false;
						break;
					}
				}
				else
				{
					switch(event.keyboard.keycode)
					{
					case ALLEGRO_KEY_ESCAPE:
						pause = true;
						break;
					default:
						break;
					}

				}
			}
			else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				runGame = false;
				break;
			}

		}
		// GAME LOOP END
		if(!menu && !play) runGame = false;

	}
	// MAIN  LOOP END
	// CLEARING

	al_destroy_font(fontMenu);
	al_destroy_font(font2);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_timer(timerMenu);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(tlo1);
	// CLEARING END
	return 0;
}
