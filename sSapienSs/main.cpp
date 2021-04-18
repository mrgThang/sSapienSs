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
	openword = 7,
	closeword = 8
};

void Run_Open_Word()
{

}

void Run_Close_Word()
{

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
		screen_status = run_normal_prehistory;
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
						if (MYHP < 3)MYHP++;
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

	//Update screen
	SDL_RenderPresent(gRenderer);

	if (gGate.ChangeMap() == 1)
	{
		screen_status = run_boss_prehistory;
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
		screen_status = run_score_board;
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
				MYHP = 3;
				gHero.TakeHP(MYHP,0);
				memset(detect, 0, sizeof(detect));
				gGate.Start();
				current_weapon = -1;
				memset(is_had_weapon,0,sizeof(is_had_weapon));
				Mix_PlayMusic(gMusic, -1);
			}
			else if (dem >= 5)
			{
				dem = 5;
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
