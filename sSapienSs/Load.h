#ifndef LOAD_H_
#define LOAD_H_

#include "CommonFunction.h"
#include "TileMap.h"
#include "Hero.h"
#include "bullet.h"
#include "Test.h"
#include "NormalEnemies.h"
#include "Sword.h"
#include "spear.h"
#include "MyHP.h"
#include "chest.h"
#include "WaterFall.h"
#include "Spider.h"
#include "rhino.h"
#include "kangaru.h"
#include "Button.h"
#include "PrehistoryBoss.h"
#include "gate.h"
#include "Menu.h"
#include "ControlGame.h"
#include "Coins.h"

enum
{
	tree = 1,
	spear = 2
};

BaseTexture gBackground;
Hero gHero;
Bullet gBullet;
Sword gSword;
MyHP gHP;
Spear gSpear;
Gate gGate;
GameMap gGamemap;
std::vector<WeaponInChest> gWeaponInChest;
std::vector<Chest> gChest;
std::vector<WaterFall> gWaterFall;
std::vector<Spider> gSpider;
std::vector<Rhino> gRhino;
std::vector<Kangaru> gKangaru;
Button gStartButton;
Button gOptionButton;
Button gExitButton;
PrehistoryBossManage gPrehistoryBossManage;
MenuManage gMenuManage;
ControlGameManage gControlGameManage;
Coins gCoins;
Score gScore;

bool init()
{
	//initialization flag
	bool success = true;

	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "failed to initialize SDL\n SDL Error:" << SDL_GetError();
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//create window
	gWindow = SDL_CreateWindow("Sapiens",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "failed to create window \n SDL Error:" << SDL_GetError();
		success = false;
	}
	else
	{
		//create vsynced renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL)
		{
			std::cout << "failed to create renderer \n SDL Error:" << SDL_GetError();
		}
		else
		{
			SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}

			//Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}
	return success;
}

void free_texture()
{
	//Destroy texture
    gHero.free();
	gBullet.free();
	gSword.free();
	gSpear.free();
	gGate.free();
	gHP.free();
	gBackground.free();
    gStartButton.free();
    gExitButton.free();
    gOptionButton.free();
	gGamemap.~GameMap();
	for (int i = 0; i < gChest.size(); ++i)gChest[i].free();
	for (int i = 0; i < gWeaponInChest.size(); ++i)gWeaponInChest[i].free();
	for (int i = 0; i < gSpider.size(); ++i)gSpider[i].free();
	for (int i = 0; i < gWaterFall.size(); ++i)gWaterFall[i].free();
	for (int i = 0; i < gRhino.size(); ++i)gRhino[i].free();
	for (int i = 0; i < gKangaru.size(); ++i)gKangaru[i].free();
	gPrehistoryBossManage.~PrehistoryBossManage();
	gMenuManage.~MenuManage();
	gControlGameManage.~ControlGameManage();
	gCoins.free();
	gScore.free();
}

void close()
{

	//destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL System
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

bool Load_NorMal_Prehistory_Map()
{
	bool success = 1;
    
    //load background
    success = min(success,gBackground.LoadFromFile("background/PrehistoryBackground.png", gRenderer));

    //load Gamemap
	gGamemap.StartAgain();
    gGamemap.LoadMap("tile/tile.txt",125,11);
	gGamemap.LoadTileTexture(gRenderer,"tile/PrehistoricTile/",11);

	//load hero
    success = min(success,gHero.LoadFromFile("hero/hero.png", gRenderer));
	gHero.SetRect(0, 0);

    //load bullet
    success = min(success, gBullet.LoadFromFile("bullet/bullet.jpg", gRenderer));

    //load tree sword
    success = min(success, gSword.LoadFromFile("sword/sword3.png", gRenderer));
    
    //load HP
    success = min(success,gHP.LoadFromFile("heartpoint/myHP.png", gRenderer)); 
    gHP.SetRect(SCREEN_WIDTH - 3 * 64, 0);

    //load spear
    success = min(success,gSpear.LoadFromFile("sword/spear.png", gRenderer));

    //load gate
	std::ifstream ifsgate("gate/normal_prehistory.txt");
	int xgate, ygate;
	ifsgate >> xgate >> ygate;
    success = min(success, gGate.LoadFromFile("gate/voidgate.png",gRenderer));
    gGate.GetPosition(xgate * 64, ygate * 64);

    //load chest and weapon in chest
	while (gChest.size())gChest.pop_back();
	while (gWeaponInChest.size())gWeaponInChest.pop_back();
    std::ifstream ifschest("chest/position.txt");
	std::vector<int> chest_pos_x;
	std::vector<int> chest_pos_y;
	int chest_x, chest_y;
	while (ifschest >> chest_x, ifschest >> chest_y)
	{
		Chest neww;
		gChest.push_back(neww);
		chest_pos_x.push_back(chest_x);
		chest_pos_y.push_back(chest_y);
		WeaponInChest new_weapon;
		gWeaponInChest.push_back(new_weapon);
	}
	for (int i = 0; i < gChest.size(); ++i)
	{
		success = min(success, gChest[i].LoadFromFile("chest/chest.png", gRenderer));
		gChest[i].GetPosition(chest_pos_x[i] * TILE_SIZE, chest_pos_y[i] * TILE_SIZE);
	}
	for (int i = 0; i < gWeaponInChest.size(); ++i)
	{
		char x = char(i + '0');
		std::string ss;
		ss = ss + "Chest/" + x + (std::string)".png";
		success = min(success, gWeaponInChest[i].LoadFromFile(ss, gRenderer));
	}

	//load waterfall
	while (gWaterFall.size())gWaterFall.pop_back();
    std::ifstream ifswaterfall("background/WaterFallPos.txt");
	std::vector<int> waterfall_pos_x;
	std::vector<int> waterfall_pos_y;
	int dem = 0;
	int waterfall_x, waterfall_y;
	while (ifswaterfall >> waterfall_x, ifswaterfall >> waterfall_y)
	{
		WaterFall neww;
		gWaterFall.push_back(neww);
		waterfall_pos_x.push_back(waterfall_x);
		waterfall_pos_y.push_back(waterfall_y);
	}
	for (int i = 0; i < gWaterFall.size(); ++i)
	{
		success = min(success, gWaterFall[i].LoadFromFile("background/WaterFall.png", gRenderer));
		gWaterFall[i].GetPosition(waterfall_pos_x[i] * TILE_SIZE, waterfall_pos_y[i] * TILE_SIZE);
	}

	//load spider
	while (gSpider.size())gSpider.pop_back();
    std::ifstream ifsspider("enemies/position/spider.txt");
	std::vector<int>spider_pos_x;
	std::vector<int>spider_pos_y;
	std::vector<int>spider_speed;
	int spider_x, spider_y, spider_z;
	while (ifsspider >> spider_x, ifsspider >> spider_y, ifsspider >> spider_z)
	{
		spider_pos_x.push_back(spider_x);
		spider_pos_y.push_back(spider_y);
		spider_speed.push_back(spider_z);
		Spider neww;
		gSpider.push_back(neww);
		neww.free();
	}
	for (int i = 0; i < gSpider.size(); ++i)
	{
		success = min(success, gSpider[i].LoadFromFile("enemies/spider.png", gRenderer));
		success = min(success, gSpider[i].LoadToothFromFile("enemies/spidertooth.png", gRenderer));
		gSpider[i].SetPosition(spider_pos_x[i] * TILE_SIZE, spider_pos_y[i] * TILE_SIZE);
		gSpider[i].SetSpeed(spider_speed[i]);
	}

	//load Rhino
	while (gRhino.size())gRhino.pop_back();
	std::ifstream ifsrhino("enemies/position/Rhino.txt");
	std::vector<int>rhino_pos_x;
	std::vector<int>rhino_pos_y;
	int rhino_x, rhino_y;
	while (ifsrhino >> rhino_x, ifsrhino >> rhino_y)
	{
		rhino_pos_x.push_back(rhino_x);
		rhino_pos_y.push_back(rhino_y);
		Rhino neww;
		gRhino.push_back(neww);
		neww.free();
	}
	for (int i = 0; i < gRhino.size(); ++i)
	{
		success = min(success, gRhino[i].LoadFromFile("enemies/rhino.png", gRenderer));
		success = min(success, gRhino[i].LoadHPFromFile("heartpoint/HeartPointEnemies.png", gRenderer));
		gRhino[i].SetPosition(rhino_pos_x[i] * TILE_SIZE, rhino_pos_y[i] * TILE_SIZE);
	}

	//load kangaru
	while (gKangaru.size())gKangaru.pop_back();
	std::ifstream kangaru_ifs("enemies/position/Kangaru.txt");
	std::vector<int>kangaru_pos_x;
	std::vector<int>kangaru_pos_y;
	int kangaru_x, kangaru_y;
	while (kangaru_ifs >> kangaru_x, kangaru_ifs >> kangaru_y)
	{
		kangaru_pos_x.push_back(kangaru_x);
		kangaru_pos_y.push_back(kangaru_y);
		Kangaru neww;
		gKangaru.push_back(neww);
		neww.free();
	}
	for (int i = 0; i < gKangaru.size(); ++i)
	{
		success = min(success, gKangaru[i].LoadFromFile("enemies/kangaru.png", gRenderer));
		success = min(success, gKangaru[i].LoadHPFromFile("heartpoint/HeartPointEnemies.png", gRenderer));
		gKangaru[i].SetPosition(kangaru_pos_x[i] * TILE_SIZE, kangaru_pos_y[i] * TILE_SIZE);
	}

	//load control game
	success = min (success, gControlGameManage.Load(gRenderer));

	//load coins
	success = min (success, gCoins.LoadFromFile("coins/coins.png",gRenderer));

	//load font
	gScore.LoadFont("font/PEPSI.ttf");

	//delete weapon
	while (Weapon.size())
	{
		Weapon.pop_back();
	}

	return success;

}

bool Load_Menu()
{
	bool success = 1;

	//load background
	success = min(success, gBackground.LoadFromFile("background/MenuBackground.png",gRenderer));

	//load start button
	success = min(success, gStartButton.LoadFromFile("Button/StartButton.png", gRenderer));

	//load option button
	success = min(success, gOptionButton.LoadFromFile("Button/OptionButton.png", gRenderer));

	//load exit button
	success = min(success, gExitButton.LoadFromFile("Button/ExitButton.png", gRenderer));

	//load manage animation menu
	success = min(success, gMenuManage.Load(gRenderer));

	return success;
}

bool Load_Game_Over()
{
	bool success = 1;

	//load gameover background
	success = min(success, gBackground.LoadFromFile("background/GameOver.png", gRenderer));

	return success;
}

bool Load_Boss_Prehistory_Map()
{
	bool success = 1;

	//load boss action
	success = min(success, gPrehistoryBossManage.Load(gRenderer));
	gPrehistoryBossManage.SetMyHP(3);
	gPrehistoryBossManage.ResetStatus();

	//load hero
	success = min(success, gHero.LoadFromFile("hero/hero.png",gRenderer));
	gHero.SetRect(0, 64*8);

	//load spear
	success = min(success, gSpear.LoadFromFile("sword/spear.png",gRenderer));

	//load tree
	success = min(success, gSword.LoadFromFile("sword/sword3.png", gRenderer));

	//load hp
	success = min(success, gHP.LoadFromFile("heartpoint/myHP.png",gRenderer));
	gHP.SetRect(SCREEN_WIDTH - 3 * 64, 0);

	//load voidgate
	success = min(success, gGate.LoadFromFile("gate/voidgate.png",gRenderer	));
	gGate.SetRect(18*64, 8*64);

	//load background
	success = min(success, gBackground.LoadFromFile("background/meadow.png",gRenderer));

	//load gamemap
	gGamemap.StartAgain();
	gGamemap.LoadMap("tile/PrehistoricBossTile/boss.txt",20,11);
	gGamemap.LoadTileTexture(gRenderer, "tile/PrehistoricBossTile/", 16);

	//load control game
	success = min(success, gControlGameManage.Load(gRenderer));

	return success;
}

#endif