#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_mixer.h>
#include <vector>
#include "sstream"


//global variables
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

//screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 704;
const int SCREEN_BPP = 32;

//color
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

//render draw color
const int RENDER_DRAW_COLOR = 255;

//distant
const int FOOT_DISTANT = 8;
const int ATK_DISTANT = 320;

//map variables
#define TILE_SIZE 64
#define HERO_SIZE_X 64
#define HERO_SIZE_Y 64

typedef struct Map
{
	int start_x;
	int start_y;

	int tile[20][200];
	const char* file_name;
};

//max screen moving
const int max_prehistory_normal_map_move = TILE_SIZE * 125 - SCREEN_WIDTH;

const int max_prehistory_boss_map_move = TILE_SIZE * 20 - SCREEN_WIDTH;

//variable global

extern bool detect[200][200][4];

extern int screen_mov;

extern int screen_last;

extern int screen_start_x;

extern int hero_start_x;

extern int hero_start_y;

extern int MYHP;

extern int hero_jump_condition;
extern int hero_jump_max;

extern int screen_status;

extern Uint32 tick_immortal;

extern Uint32 last_tick_immortal;

extern std::vector<int> Weapon;

extern int SCORE;

extern std::string NAME;

#endif