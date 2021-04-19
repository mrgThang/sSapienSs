#include "CommonFunction.h"
#include "Load.h"

int dem = 0;
int current_weapon = -1;
SDL_Event gEvent;
int bonusHP[12];
bool quit = 0;
bool is_had_weapon[12];
bool key[200];
std::string last_score_text;

const enum
{
	run_menu = 1,
	run_typing_name = 2,
	run_game_over = 3,
	run_score_board = 4,
	run_normal_prehistory = 5,
	run_boss_prehistory = 6,
	run_open_word = 7,
	run_close_word = 8,
	run_mid_word = 9,
	run_continue = 10,
	run_option
};

void Run_Option()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	//Render background
	gBackground.Render(gRenderer, 0, 0);

	//render button
	gEasy.SetRect(7 * 64,  4 * 64);
	gMedium.SetRect(7*64, 6 * 64+32);
	gHard.SetRect(7 * 64, 9 * 64);
	gEasy.HandleEvent(gRenderer, &gEvent);
	gMedium.HandleEvent(gRenderer, &gEvent);
	gHard.HandleEvent(gRenderer, &gEvent);

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gEasy.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		HARD = 3;
		screen_status = run_menu;
		dem = 0;
	}

	if (gMedium.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		HARD = 2;
		screen_status = run_menu;
		dem = 0;
	}

	if (gHard.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		HARD = 1;
		screen_status = run_menu;
		dem = 0;
	}
}

void Run_Open_Word()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	int dw = 0;

	if (dem >= 100)
	{
		//load text;
		SDL_Color textColor = { 255,255,255 };
		std::ifstream ifsw("word/word1.txt");
		std::string s = "  ";
		while (getline(ifsw, s))
		{
			dw++;
			gWord[dw].LoadFromRenderedText(s, textColor, gRenderer);
			gWord[dw].Render(gRenderer, 64, dw * 64);
		}

		//load text;
		std::ifstream ifsw2("word/word2.txt");
		while (getline(ifsw2, s))
		{
			dw++;
			gWord[dw].LoadFromRenderedText(s, textColor, gRenderer);
			gWord[dw].Render(gRenderer, 64, 64 + dw * 64);
		}

		int sang;
		if ((dem / 150) % 2 == 0)sang = dem % 150;
		else sang = 150 - dem % 150;
		SDL_Color textColor3 = { 255,255,255,sang };
		std::ifstream ifsw3("word/word3.txt");
		getline(ifsw3, s);
		gWord[9].LoadFromRenderedText(s, textColor3, gRenderer);
		if(sang != 0)gWord[9].Render(gRenderer, 64, 64 * 10);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			screen_status = run_normal_prehistory;
			dem = 0;
		}
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Run_Mid_Word()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	int dw = 0;

	if (dem >= 100)
	{
		//load text;
		SDL_Color textColor = { 255,255,255 };
		std::ifstream ifsw("word/word4.txt");
		std::string s = "  ";
		while (getline(ifsw, s))
		{
			dw++;
			gWord[dw].LoadFromRenderedText(s, textColor, gRenderer);
			gWord[dw].Render(gRenderer, 64, dw * 64);
		}
	
		int sang;
		if ((dem / 150) % 2 == 0)sang = dem % 150;
		else sang = 150 - dem % 150;
		SDL_Color textColor3 = { 255,255,255,sang };
		std::ifstream ifsw3("word/word3.txt");
		getline(ifsw3, s);
		gWord[9].LoadFromRenderedText(s, textColor3, gRenderer);
		if (sang != 0)gWord[9].Render(gRenderer, 64, 64 * 10);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			screen_status = run_boss_prehistory;
			dem = 0;
		}
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Run_Close_Word()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	int dw = 0;

	if (dem >= 100)
	{
		//load text;
		SDL_Color textColor = { 255,255,255 };
		std::ifstream ifsw("word/word5.txt");
		std::string s = "  ";
		while (getline(ifsw, s))
		{
			dw++;
			gWord[dw].LoadFromRenderedText(s, textColor, gRenderer);
			gWord[dw].Render(gRenderer, 64, dw * 64);
		}

		int sang;
		if ((dem / 150) % 2 == 0)sang = dem % 150;
		else sang = 150 - dem % 150;
		SDL_Color textColor3 = { 255,255,255,sang };
		std::ifstream ifsw3("word/word3.txt");
		getline(ifsw3, s);
		gWord[9].LoadFromRenderedText(s, textColor3, gRenderer);
		if (sang != 0)gWord[9].Render(gRenderer, 64, 64 * 10);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			screen_status = run_continue;
			dem = 0;
		}
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Run_Menu()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	//Render background
	gBackground.Render(gRenderer, 0, 0);

	//render button
	gStartButton.SetRect(16 * 64, 6 * 64);
	gOptionButton.SetRect(16 * 64 - 32, 7 * 64 + 32);
	gExitButton.SetRect(16 * 64, 9*64);
	gStartButton.HandleEvent(gRenderer,&gEvent);
	gOptionButton.HandleEvent(gRenderer, &gEvent);
	gExitButton.HandleEvent(gRenderer, &gEvent);

	//render menu animation
	gMenuManage.HandleEvent(gRenderer);

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gStartButton.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		screen_status = run_typing_name;
		dem = 0;
	}

	if (gOptionButton.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		screen_status = run_option;
		dem = 0;
	}

	if (gExitButton.ReturnPressState() == 1)
	{
		Mix_PlayChannel(-1, gButtonSound, 0);
		quit = 1;
	}
}

void Run_Typing_Name()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	//render background
	gBackground.Render(gRenderer, 0, 0);

	//render 
	gTypingManage.HandleEvent(gRenderer,key, &gEvent);

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gTypingManage.ReturnOver() == 1)
	{
		screen_status = run_open_word;
		dem = 0;
	}
    
}

void Run_Score_Board()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	gBackground.Render(gRenderer, 0, 0);

	gScoreBoardManage.HandleEvent(gRenderer);

	if (gScoreBoardManage.ReturnPressESC() == 1)
	{
		screen_status = run_menu;
		dem = 0;
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Run_Game_Over()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	//Render background
	gBackground.Render(gRenderer, 0, 0);

	//Update screen
	SDL_RenderPresent(gRenderer);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_SPACE])
	{
		screen_status = run_score_board;
		dem = 0;
	}
}

void Run_Continue()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	SDL_RenderClear(gRenderer);

	//Render background
	gBackground.Render(gRenderer, 0, 0);

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (dem >= 200)
	{
		screen_status = run_score_board;
		dem = 0;
	}
}

void Run_Normal_Prehistory()
{
	bool pause_status = gControlGameManage.GetStatus();

	if (pause_status == 0)
	{
		//clear screen
		SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gRenderer);

		//render background
		gBackground.Render(gRenderer, 0, 0);

		if (hero_start_y >= 13 * 64)MYHP = 0;

		//hero motion
		if (MYHP == 0)
		{
			screen_status = run_game_over;
			dem = 0;
		}
		gHero.TakeHP(MYHP, 1);
		gHero.HandleEvent(hero_jump_condition, hero_jump_max, max_prehistory_normal_map_move);

		//Render chest and chest motion + weapon in chest
		int status_mov = gGamemap.GetStatusMov();
		for (int i = 0; i < gChest.size(); ++i)
		{
			gChest[i].HandleEvent(gRenderer, status_mov);
			if (gChest[i].Getdk() == 1)
			{
				if (i == 0 && is_had_weapon[tree] == 0)
				{
					Weapon.push_back(tree);
					SDL_Rect chest_pos = gChest[i].GetRect();
					gWeaponInChest[i].SetRect(chest_pos.x, chest_pos.y);
					is_had_weapon[tree] = 1;
					SCORE += 10;
				}
				else if (i == 1 || i == 2 || i == 3)
				{
					if (bonusHP[i] == 0)
					{
						if (MYHP < HARD)MYHP++;
						bonusHP[i] = 1;
						SCORE += 10;
					}
					SDL_Rect chest_pos = gChest[i].GetRect();
					gWeaponInChest[i].SetRect(chest_pos.x, chest_pos.y);
				}
				else if (i == 4 && is_had_weapon[spear] == 0)
				{
					Weapon.push_back(spear);
					SDL_Rect chest_pos = gChest[i].GetRect();
					gWeaponInChest[i].SetRect(chest_pos.x, chest_pos.y);
					is_had_weapon[spear] = 1;
					SCORE += 10;
				}
				gWeaponInChest[i].HandleEvent(gRenderer, status_mov);
			}
		}

		//change weapon
		if (key[118])
		{
			if (Weapon.size() > 0)
			{
				for (int i = 0; i < Weapon.size(); ++i)
				{
					if (current_weapon == Weapon[i])
					{
						if (i == Weapon.size() - 1)
						{
							current_weapon = Weapon[0];
						}
						else current_weapon = Weapon[i + 1];
						break;
					}
				}
				if (current_weapon == -1)
				{
					current_weapon = Weapon[0];
				}
			}
		}

		//render waterfall
		for (int i = 0; i < gWaterFall.size(); ++i)
			gWaterFall[i].HandleEvent(gRenderer, status_mov);

		//render gate
		gGate.HandleEvent(gRenderer, status_mov, &gEvent);

		//map motion
		gGamemap.HandleEvent(125);
		gGamemap.DrawMap(gRenderer);

		//render hero
		gHero.Motion(gRenderer);

		int status2 = gHero.GetStatus2();

		//render sword
		if (tree == current_weapon)gSword.HandleEvent(gRenderer, status2);

		//render spear
		if (spear == current_weapon)gSpear.HandleEvent(gRenderer, status2);

		//Render enemies
		int sword_status = gSword.GetSwordStatus();
		int spear_status = gSpear.GetSpearStatus();
		int sword_status2 = gSword.GetSwordStatus2();
		int spear_status2 = gSpear.GetSpearStatus2();
		status_mov = gGamemap.GetStatusMov();

		//render Rhino
		for (int i = 0; i < gRhino.size(); ++i)
		{
			gRhino[i].HandldeEvent(gRenderer, status_mov, sword_status, sword_status2, spear_status, spear_status2);
		}

		//render kangaru
		for (int i = 0; i < gKangaru.size(); ++i)
		{
			gKangaru[i].HandldeEvent(gRenderer, status_mov, sword_status, sword_status2, spear_status, spear_status2);
		}

		//render spider
		for (int i = 0; i < gSpider.size(); ++i)
		{
			gSpider[i].HandldeEvent(gRenderer, status_mov);
		}

		//renderHP
		gHP.HandleEvent(gRenderer, MYHP);

		//get hero rect to render bullet
		SDL_Rect hero_rect = gHero.GetRect();
		gBullet.HandleEvent(gRenderer, hero_rect);

		//render coins
		gCoins.HandleEvent(gRenderer, 1);

		//render guide
		gControlGameManage.HandleEvent(gRenderer, key[32]);

		//render score
		std::stringstream timeText;

		timeText.str("");

		timeText << NAME << "  Score: " << SCORE;
        
		SDL_Color textColor = { 200, 200, 0, 255 };

		if (last_score_text != timeText.str().c_str())
		{
			gScore.LoadFromRenderedText(timeText.str().c_str(), textColor, gRenderer);
			last_score_text = timeText.str().c_str();
		}

		gScore.HandleEvent(gRenderer);
	}
	else
	{
	    //clear screen
		SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gRenderer);

		//render background
		gBackground.Render(gRenderer, 0, 0);

		//render guide
		gControlGameManage.HandleEvent(gRenderer, key[32]);
    }

	if (dem < 500)
	{
		std::string s;
		SDL_Color textColor3 = { 255,255,255 };
		std::ifstream ifsw3("word/word6.txt");
		getline(ifsw3, s);
		gWord[9].LoadFromRenderedText(s, textColor3, gRenderer);
		gWord[9].Render(gRenderer, 64, 64 * 10);
	}

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gGate.ChangeMap() == 1)
	{
		screen_status = run_mid_word;
		dem = 0;
	}

	if (key[27] == 1 && pause_status == 1)
	{
		screen_status = run_menu;
		dem = 0;
	}
}

void Run_Boss_Prehistory()
{

	bool pause_status = gControlGameManage.GetStatus();

	if (pause_status == 0)
	{
		//clear screen
		SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gRenderer);

		//render background
		gBackground.Render(gRenderer, 0, 0);

		//dieu kien chet
		if (hero_start_y >= 13 * 64)MYHP = 0;

		//hero motion
		if (MYHP == 0)
		{
			screen_status = run_game_over;
			dem = 0;
		}
		gHero.TakeHP(MYHP, 1);
		gHero.HandleEvent(hero_jump_condition, hero_jump_max, max_prehistory_boss_map_move);

		//render map
		gGamemap.HandleEvent(20);
		gGamemap.DrawMap(gRenderer);
		int status_mov = gGamemap.GetStatusMov();

		//render hero
		gHero.Motion(gRenderer);

		//render spear
		int status2 = gHero.GetStatus2();

		//change weapon
		if (key[118])
		{
			if (Weapon.size() > 0)
			{
				for (int i = 0; i < Weapon.size(); ++i)
				{
					if (current_weapon == Weapon[i])
					{
						if (i == Weapon.size() - 1)
						{
							current_weapon = Weapon[0];
						}
						else current_weapon = Weapon[i + 1];
						break;
					}
				}
				if (current_weapon == -1)
				{
					current_weapon = Weapon[0];
				}
			}
		}

		//render sword
		if (tree == current_weapon)gSword.HandleEvent(gRenderer, status2);

		//render spear
		if (spear == current_weapon)gSpear.HandleEvent(gRenderer, status2);

		int sword_status = gSword.GetSwordStatus();
		int spear_status = gSpear.GetSpearStatus();
		int sword_status2 = gSword.GetSwordStatus2();
		int spear_status2 = gSpear.GetSpearStatus2();

		gPrehistoryBossManage.HandleEvent(gRenderer);

		if (gPrehistoryBossManage.GetHP() > 0)
		{
			gPrehistoryBossManage.SetWeaponStatus(spear, spear_status, spear_status2);
			gPrehistoryBossManage.SetWeaponStatus(tree, sword_status, sword_status2);
		}
		else gGate.HandleEvent(gRenderer, status_mov, &gEvent);

		//renderHP
		gHP.HandleEvent(gRenderer, MYHP);

		//render guide
		gControlGameManage.HandleEvent(gRenderer, key[32]);

		//render score
		std::stringstream timeText;

		timeText.str("");

		timeText << NAME << "  Score: " << SCORE;

		SDL_Color textColor = { 200, 200, 0, 255 };

		if (last_score_text != timeText.str().c_str())
		{
			gScore.LoadFromRenderedText(timeText.str().c_str(), textColor, gRenderer);
			last_score_text = timeText.str().c_str();
		}

		gScore.HandleEvent(gRenderer);
	}
	else
	{
		//clear screen
		SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gRenderer);

		//render background
		gBackground.Render(gRenderer, 0, 0);

		//render guide
		gControlGameManage.HandleEvent(gRenderer, key[32]);
	}

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gGate.ChangeMap() == 1)
	{
		screen_status = run_close_word;
		dem = 0;
	}

	if (key[27] == 1 && pause_status == 1)
	{
		screen_status = run_menu;
		dem = 0;
	}
}

int main(int argc, char* argv[])
{
	//initialize
	if (init() == false)return -1;

	//hard
	HARD = 3;

	//dieu kien quit
	bool is_quit = false;

	//screen status
	screen_status = run_menu;

	const int frame = 60;

	const int frameDelay = 1000 / 60;

	srand(time(NULL));

	//while...
	while (is_quit == false)
	{
		int frame_start = SDL_GetTicks();

		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT || quit == 1)
			{
				is_quit = true;
			}
			if (gEvent.type == SDL_KEYDOWN)
			{
				for (int i = 1; i <= 122; ++i)
				{
					if (gEvent.key.keysym.sym == i)key[i] = 1;
				}
			}
		}

		if (screen_status == run_open_word)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Open_Word())is_quit = true;
			}
			else if (dem >= 5)
			{
				Run_Open_Word();
			}
		}

		if (screen_status == run_mid_word)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Mid_Word())is_quit = true;
			}
			else if (dem >= 5)
			{
				Run_Mid_Word();
			}
		}

		if (screen_status == run_close_word)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Close_Word())is_quit = true;
			}
			else if (dem >= 5)
			{
				Run_Close_Word();
			}
		}

		if (screen_status == run_continue)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Continue())is_quit = true;
				Mix_PlayChannel(-1, gButtonSound, 0);
			}
			else if (dem >= 5)
			{
				Run_Continue();
			}
		}

		if (screen_status == run_menu)
		{
			dem++;
			if (dem  == 1)
			{
				if (!Load_Menu()) is_quit = true;
				Mix_PlayMusic(gMusic, -1);
			}
			else if(dem >= 5)
			{
				dem = 5;
				SCORE = 0;
				Run_Menu();
			}
		}

		if (screen_status == run_option)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Option()) is_quit = true;
			}
			else if (dem >= 5)
			{
				dem = 5;
				SCORE = 0;
				Run_Option();
			}
		}

		if (screen_status == run_typing_name)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Typing_Name())is_quit = true;
			}
			else if (dem >= 5)
			{
				dem = 5;
				Run_Typing_Name();
			}
		}

		if (screen_status == run_score_board)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Score_Board())is_quit = true;
			}
			else if (dem >= 5)
			{
				dem = 5;
				Run_Score_Board();
			}
		}

		if (screen_status == run_game_over)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Game_Over())is_quit = true;
				Mix_PlayMusic(gMusic, -1);
			}
			else if (dem >= 5)
			{
				dem = 5;
				Run_Game_Over();
			}
		}

		if (screen_status == run_normal_prehistory)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_NorMal_Prehistory_Map()) is_quit = true;
				hero_jump_condition = 0;
				MYHP = HARD;
				gHero.TakeHP(MYHP,0);
				memset(detect, 0, sizeof(detect));
				gGate.Start();
				current_weapon = -1;
				memset(is_had_weapon,0,sizeof(is_had_weapon));
				Mix_PlayMusic(gMusic, -1);
			}
			else if (dem >= 5)
			{
				if (dem >= 500)dem = 500;
				Run_Normal_Prehistory();
			}
		}

		if (screen_status == run_boss_prehistory)
		{
			dem++;
			if (dem == 1)
			{
				if (!Load_Boss_Prehistory_Map()) is_quit = true;
				hero_jump_condition = 0;
				gHero.TakeHP(MYHP,0);
				memset(detect, 0, sizeof(detect));
				gGate.Start();
				Mix_PlayMusic(gMusic, -1);
			}
			else if (dem >= 5)
			{
				dem = 5;
				Run_Boss_Prehistory();
			}
		}
		
		for (int i = 1; i <= 122; ++i)
		{
			key[i] = 0;
		}

		if (frameDelay > SDL_GetTicks() - frame_start)
		{
			SDL_Delay(frameDelay - SDL_GetTicks() + frame_start);
		}
	}

	//quit
	free_texture();
	close();

	return 0;
}
