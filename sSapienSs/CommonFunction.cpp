#include "CommonFunction.h"

bool detect[200][200][4];

int screen_mov = 0;

int screen_last;

int screen_start_x;

int hero_start_x;

int hero_start_y;

int MYHP;

int hero_jump_condition;
int hero_jump_max;

int screen_status;

Uint32 tick_immortal;

Uint32 last_tick_immortal;

std::vector<int> Weapon;

int SCORE = 0;

std::string NAME;