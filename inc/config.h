#pragma once

#include <memory>
#include <cstdint>
#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

enum class Color
{
	black, white, orange, gray, pink, yellow, purple
};

struct Config
{
	// const variables
	static constexpr uint16_t menuHorizontal = 285;
	static constexpr uint16_t menuPos(uint16_t x){ return x* 80; }
	static constexpr uint16_t creditsPos(uint16_t x){ return x* 50; }


	// STRINGS
	static constexpr char tab[] = "asd";

	// COLORS
	static const ALLEGRO_COLOR getRGB(Color color)
	{
		if(color == Color::black) { return al_map_rgb(0,0,0); }
		else if(color == Color::white) { return al_map_rgb(255,255,255); }
		else if(color == Color::orange) { return al_map_rgb(255, 128, 0); }
		else if(color == Color::gray) { return al_map_rgb(128, 128, 128); }
		else if(color == Color::pink) { return al_map_rgb(255, 0, 127); }
		else if(color == Color::yellow) { return al_map_rgb(255, 255, 0); }
		else if(color == Color::purple) { return al_map_rgb(128, 64, 255); }
		else { return al_map_rgb(0,0,0); }
	}



};

struct Player
{
	bool moveLEFT = false;
	bool moveRIGHT = false;
	bool moveJUMP = false;
	bool moveCROUCH = false;
};
