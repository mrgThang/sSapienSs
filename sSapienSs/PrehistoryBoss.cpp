#include "PrehistoryBoss.h"
#include "CommonFunction.h"

enum {

	warning_motion = 1,
	water2_motion = 2,
	sand_motion = 3,

	boss_go_left = 4,
	boss_go_right = 5,
	water1_motion = 6,
	boss_angry = 7,
	boss_dizzy = 8,
	boss_start = 9,
	warning_start = 10,
	boss_dead = 11
};

enum {
	tree = 1,
	spear = 2
};

//BossHp
HP::HP()
{
	my_hp = 3;
}

HP::~HP()
{
	free();
}

void HP::HandleEvent(SDL_Renderer* screen, int x)
{
	my_hp = x;
	Motion(screen);
}

void HP::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = 64 * 3 * (my_hp - 1);
	clip->y = 0;
	clip->w = 64 * 3;
	clip->h = 64;

	Render(screen, my_rect.x, my_rect.y, clip);
}

//Big Warning action
BigWarning::BigWarning() 
{
	dem = 0;
	so_luot = 0;
	status = 1;
}

BigWarning::~BigWarning()
{
	free();
}

void BigWarning::HandleEvent(SDL_Renderer* screen, int &manage_status)
{
	dem++;
	if (dem >= 40)
	{
		so_luot++;
		dem = 0;
	}
	if (dem > 20)status = 2;
	else status = 1;
	Motion(screen);

	if (so_luot > 4)
	{
		so_luot = 0;
		status = 1;
		dem = 0;
		manage_status = boss_start;
	}
}

void BigWarning::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = 0;
	clip->y = 64*5*(status - 1);
	clip->w = 64 * 14;
	clip->h = 64 * 5;

	Render(screen, 64 * 3, 64 * 3, clip);
}

// warning action
Warning::Warning()
{
	status = 0;
	dem = 0;
	dem_status = 0;
}

Warning::~Warning()
{
	free();
}

void Warning::HandleEvent(SDL_Renderer* screen, int &manage_status)
{
	dem_status++;
	if (dem_status >= 24)
	{
		if(status == 0)status = 1;
		else status = 0;
		dem_status = 0;
		dem++;
	}
	if (dem >= 5)
	{
		dem = 0;
		manage_status = water1_motion;
		status = 0;
	}
	Motion(screen);
}

void Warning::Motion(SDL_Renderer* screen)
{
	SDL_Rect *clip = new SDL_Rect;
	clip->x = (status - 1)*64;
	clip->y = 0;
	clip->w = 64;
	clip->h = 64;
	Render(screen, my_rect.x, my_rect.y, clip);
}

//boss action

Boss::Boss()
{
	status = 0;
	so_luot = 0;
	dem = 0;
	status2 = 0;
}

Boss::~Boss()
{
	free();
}

void Boss::HandleEvent(SDL_Renderer* screen, int& manage_status, int & last_attack)
{
	if (manage_status == boss_start)
	{
		if (my_rect.x > 64 * 8)
		{
			my_rect.x -= 4;
			status2 = 2;
			dem++;
			if (dem >= 16)
			{
				status++;
				if (status > 2 || status < 1)status = 1;
				dem = 0;
			}
		}
		else
		{
			manage_status = boss_angry;
			dem = 0;
		}
	}
	
	else if (manage_status == boss_go_left)
	{
		if (my_rect.x > 64 * 2)
		{
			my_rect.x -= 4;
			status2 = 2;
			dem++;
			if (dem >= 16)
			{
				status++;
				if (status > 2 || status < 1)status = 1;
				dem = 0;
			}
		}
		else
		{
			manage_status = water2_motion;
			dem = 0;
		}
	}
	else if (manage_status == boss_go_right)
	{
		if (my_rect.x < 64 * 14)
		{
			my_rect.x += 4;
			status2 = 5;
			dem++;
			if (dem >= 16)
			{
				status++;
				if (status > 2 || status < 1)status = 1;
				dem = 0;
			}
		}
		else
		{
			manage_status = boss_angry;
			my_rect.x = 64 * 8;
			dem = 0;
		}
	}
	else if(manage_status == boss_angry)
	{
		if (so_luot < 12)
		{
			status2 = 3;
			dem++;
			if (dem >= 16)
			{
				status++;
				so_luot++;
				if (status > 2 || status < 1)status = 1;
				dem = 0;
			}
		}
		else
		{
			manage_status = rand() % 3 + 1;
			while (manage_status == last_attack || (last_attack == water1_motion && manage_status == warning_motion))manage_status = rand() % 3 + 1;			
			so_luot = 0;
			dem = 0;
		}
	}
	else if (manage_status == warning_motion || manage_status == water1_motion)
	{
		status2 = 1;
		dem++;
		if (dem >= 16)
		{
			status++;
			if (status > 4 || status < 3)status = 3;
			dem = 0;
		}
	}
	else if (manage_status == water2_motion)
	{
		if (my_rect.x > 64 * 2)manage_status = boss_go_left;
		else
		{
			status2 = 2;
			dem++;
			if (dem >= 16)
			{
				status++;
				if (status > 4 || status < 3)status = 3;
				dem = 0;
			}
		}
	}
	else if (manage_status == sand_motion)
	{
		status2 = 3;
		dem++;
		if (dem >= 16)
		{
			status++;
			if (status > 4 || status < 3)status = 3;
			dem = 0;
		}
	}
	else if (manage_status == boss_dizzy)
	{
		if (so_luot < 15)
		{
			status2 = 4;
			dem++;
			if (dem >= 16)
			{
				status++;
				so_luot++;
				if (status < 1 || status > 3)status = 1;
				dem = 0;
			}
		}
		else
		{
			so_luot = 0;
			dem = 0;
			manage_status = boss_angry;
		}
	}

	Motion(screen);
}

void Boss::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = (status - 1) * 64 * 6 * 2;
	clip->y = (status2 - 1) * 64 * 6;
	clip->w = 64 * 6 * 2;
	clip->h = 64 * 6;
	Render(screen, my_rect.x, my_rect.y, clip);
}

//water1 action

Water1::Water1()
{
	status = 1;
	dem_status = 0;
	dem = 0;
}

Water1::~Water1() 
{
	free();
}

void Water1::HandleEvent(SDL_Renderer* screen, int& manage_status)
{
	dem_status++;
	if (dem_status >= 12 )
	{
		dem_status = 0;
		status++;
		if (status >= 5)status = 1;
		dem++;
	}
	if (dem >= 6)
	{
		dem = 0;
		status = 1;
		manage_status = warning_motion;
	}
	Motion(screen);

}

void Water1::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = 0;
	clip->y = 64 * (status - 1);
	clip->w = 64 * 20;
	clip->h = 64;
	
	if (my_rect.y <= hero_start_y && hero_start_y < my_rect.y + 64 - 16)
	{
		tick_immortal = SDL_GetTicks();
		if (tick_immortal > last_tick_immortal + 5000)
		{
			MYHP--;
			SCORE -= 10;
			last_tick_immortal = tick_immortal;
		}
	}

	Render(screen, my_rect.x, my_rect.y, clip);
}

//water2 action

Water2::Water2()
{
	
}

Water2::~Water2() 
{
	free();
}

void Water2::HandleEvent(SDL_Renderer* screen, int& manage_status)
{
    my_rect.y += 8;
	if(my_rect.y < 13*64)Motion(screen);
}

void Water2::Motion(SDL_Renderer* screen)
{
	for (int i = 0; i <= 2; ++i)
	{
		if (my_rect.x + 128 * 4 * i <= hero_start_x && hero_start_x < my_rect.x + 128 * 4 * i + 128 - 16)
		{
			if (my_rect.y <= hero_start_y && hero_start_y < my_rect.y + 128 - 64)
			{
				tick_immortal = SDL_GetTicks();
				if (tick_immortal > last_tick_immortal + 5000)
				{
					MYHP--;
					SCORE -= 10;
					last_tick_immortal = tick_immortal;
				}
			}
		}

		Render(screen, my_rect.x + 128 * 4 * i, my_rect.y);
	}
}

//sand action

Sand::Sand()
{

}

Sand::~Sand() 
{
	free();
}

void Sand::HandleEvent(SDL_Renderer *screen, int& manage_status, int& so_luot_manage)
{
	if(my_rect.x < -64*3)
	{
		my_rect.x = 64*20;
		so_luot_manage++;
		SetRect(64 * 20, hero_start_y - 64 * 3);
	}
	else 
	{
		my_rect.x -= 8;
	}
	Motion(screen);
}

void Sand::Motion(SDL_Renderer *screen)
{
	if (my_rect.x <= hero_start_x && hero_start_x <= my_rect.x + 384 - 64)
	{
		if (my_rect.y <= hero_start_y && hero_start_y <= my_rect.y + 384 - 64)
		{
			tick_immortal = SDL_GetTicks();
			if (tick_immortal > last_tick_immortal + 5000)
			{
				MYHP--;
				SCORE -= 10;
				last_tick_immortal = tick_immortal;
			}
		}
	}
	Render(screen,my_rect.x, my_rect.y);
}

// function

PrehistoryBossManage::PrehistoryBossManage()
{
	dem = 0;
	manage_status = warning_start;
	last_manage_status = 0;
	so_luot = 0;
	last_attack = 0;
	luot_angry = 0;
	my_hp = 3;
	is_attacked = 0;
}

PrehistoryBossManage::~PrehistoryBossManage()
{
	mBoss.free();
	mSand.free();
	mBigWarning.free();
	mHP.free();
	for (int i = 0; i < 10; ++i)
	{
		mWarning[i].free();
		mWater1[i].free();
	}
	for (int i = 0; i < 20; ++i)
	{
		mWater2[i].free();
	} 
}

bool PrehistoryBossManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	//load HP
	success = min(success, mHP.LoadFromFile("heartpoint/myHP.png", screen));

	//load bigwarning
	success = min(success, mBigWarning.LoadFromFile("BossPrehistory/BigWarning.png", screen));

	//load boss
	success = min(success, mBoss.LoadFromFile("BossPrehistory/mammouth.png", screen));
	mBoss.SetRect(64 * 20, 64 * 4);

	//load water1
	for (int i = 0; i < 10; ++i)
	{
		success = min(success, mWater1[i].LoadFromFile("BossPrehistory/water1.png", screen));
		mWater1[i].SetRect(0, 64*i);
	}

	//load water2
	for (int i = 0; i < 40; ++i)
	{
		success = min(success, mWater2[i].LoadFromFile("BossPrehistory/water2.png", screen));
	}

	//load warning
	for (int i = 0; i < 10; ++i)
	{
		success = min(success, mWarning[i].LoadFromFile("BossPrehistory/warning.png", screen));
		mWarning[i].SetRect(64*19,64*i);
	}

	//load sand
	success = min(success, mSand.LoadFromFile("BossPrehistory/sand.png", screen));

	return success;
}

void PrehistoryBossManage::SetWeaponStatus(int loaivukhi, int status, int status2)
{
	SDL_Rect clip = mBoss.GetRect();
	if (clip.x + 64 * 5 <= hero_start_x && hero_start_x <= clip.x + 64 * 11 && manage_status == boss_dizzy)
	{
		if (clip.y <= hero_start_y && hero_start_y <= clip.y + 64 * 6)
		{
			if (loaivukhi == spear)
			{
				if (status2 == 1 && status == 4)
				{
					is_attacked = 1;
				}
				else if (status == 2 && status == 2)
				{
					is_attacked = 1;
				}
			}
			else if (loaivukhi == tree)
			{
				if (status2 == 1)
				{
					if (status >= 3 && status <= 7)is_attacked = 1;
				}
				else if (status2 == 2)
				{
					if (status >= 6 && status <= 9)is_attacked = 1;
				}
			}
		}
	}
}

void PrehistoryBossManage::HandleEvent(SDL_Renderer* screen)
{
	if (my_hp <= 0)
	{
		manage_status = boss_dead;
	}
	if (manage_status == boss_dead)
	{

	}
	else if (manage_status == warning_start)
	{
		mBigWarning.HandleEvent(screen, manage_status);
	}
	else
	{
		mBoss.HandleEvent(screen, manage_status, last_attack);

		if (manage_status == boss_angry)
		{
			if (manage_status != last_manage_status)
			{
				if (luot_angry < 3)luot_angry++;
				else
				{
					luot_angry = 0;
					manage_status = boss_dizzy;
				}
			}
			last_manage_status = manage_status;
		}

		//render warning
		if (manage_status == warning_motion)
		{
			//generate random numbers;
			if (last_manage_status != manage_status)
			{

				last_manage_status = manage_status;
				so_luot++;
				if (so_luot >= 6)
				{
					manage_status = boss_angry;
					so_luot = 0;
				}
				water1_pos1 = 2 * (rand() % 4) + 1;
				water1_pos2 = 2 * (rand() % 4) + 1;
				while (water1_pos1 == water1_pos2)
				{
					water1_pos2 = 2 * (rand() % 4) + 1;
				}
			}

			//render
			else
			{
				for (int i = 0; i < 10; ++i)
				{
					if (i != water1_pos1 && i != water1_pos2)
					{
						mWarning[i].HandleEvent(screen, manage_status);
					}
				}
			}

			last_attack = warning_motion;

		}

		// attack with water1
		else if (manage_status == water1_motion)
		{
			last_manage_status = water1_motion;
			for (int i = 0; i < 10; ++i)
			{
				if (i != water1_pos1 && i != water1_pos2)
				{
					mWater1[i].HandleEvent(screen, manage_status);
				}
			}
			last_attack = warning_motion;
		}

		//attack with water2
		else if (manage_status == water2_motion)
		{
			if (last_manage_status != manage_status)
			{
				for (int i = 0; i < 40; ++i)
				{
					int x = rand() % 4;
					mWater2[i].SetRect(x * 128, 0 - i * 128);
				}
				last_manage_status = manage_status;
			}
			else
			{
				for (int i = 0; i < 40; ++i)
				{
					mWater2[i].HandleEvent(screen, manage_status);
				}
				SDL_Rect x = mWater2[39].GetRect();
				if (x.y > 13 * 64)
				{
					manage_status = boss_go_right;
					so_luot = 0;
				}
			}
			last_attack = water2_motion;
		}

		//attack with sand
		else if (manage_status == sand_motion)
		{
			if (last_manage_status != manage_status)
			{
				last_manage_status = manage_status;
				mSand.SetRect(64 * 20, hero_start_y - 64 * 3);
			}
			else
			{
				mSand.HandleEvent(screen, manage_status, so_luot);
				if (so_luot > 4)
				{
					manage_status = boss_angry;
					so_luot = 0;
				}
			}
			last_attack = sand_motion;
		}

		//render HP
		else if (manage_status == boss_dizzy)
		{
			SDL_Rect rect = mBoss.GetRect();
			mHP.SetRect(rect.x + 64 * 7, rect.y - 64);
			mHP.HandleEvent(screen, my_hp - is_attacked);
		}
	}

	if (manage_status != boss_dizzy)
	{
		my_hp -= is_attacked;
		is_attacked = 0;
	}
}