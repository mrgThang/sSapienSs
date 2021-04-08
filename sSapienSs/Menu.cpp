#include "CommonFunction.h"
#include "Menu.h"

//manage caveman
Caveman::Caveman()
{
	dem = 0;
	status = 1;
	Vel = -4;
	stay = 0;
	statusVel = 1;
}

Caveman::~Caveman()
{
	free();
}

void Caveman::HandleEvent(SDL_Renderer* screen)
{
	my_rect.y += Vel;
	if (my_rect.y >= 64 * 13)
	{
		Vel = -4;
	}
	if (my_rect.y <= 64 * 8)
	{
		stay++;
		Vel = 0;
	}
	if (stay > 40)
	{
		stay = 0;
		Vel = 4;
	}
	dem++;
	if (dem > 12)
	{
		status += statusVel;
		if (status == 4)statusVel = -1;
		else if (status == 1)statusVel = 1;
		dem = 0;
	}
	Motion(screen);
}

void Caveman::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->h = 192;
	clip->w = 384;
	clip->x = 0;
	clip->y = 192 * (status - 1);
	Render(screen, my_rect.x, my_rect.y, clip);
}

//manage farmer
Farmer::Farmer()
{
	dem = 0;
	status = 1;
	Vel = 4;
	stay = 0;
}

Farmer::~Farmer()
{
	free();
}

void Farmer::HandleEvent(SDL_Renderer* screen)
{
	my_rect.x += Vel;
	if (my_rect.x <= 64*-10)
	{
		Vel = 4;
	}
	if (my_rect.x >= 0)
	{
		stay++;
		Vel = 0;
	}
	if (stay > 40)
	{
		stay = 0;
		Vel = -4;
	}
	dem++;
	if (dem > 12)
	{
		status += statusVel;
		if (status == 3)statusVel = -1;
		else if (status == 1)statusVel = 1;
		dem = 0;
	}
	Motion(screen);
}

void Farmer::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->w = 320;
	clip->h = 320;
	clip->x = 320 * (status - 1);
	clip->y = 0;
	Render(screen, my_rect.x, my_rect.y, clip);
}

//manage scientist
Scientist::Scientist()
{
	dem = 0;
	status = 1;
	Vel = -4;
	stay = 0;
}

Scientist::~Scientist()
{
	free();
}

void Scientist::HandleEvent(SDL_Renderer* screen)
{
	my_rect.x += Vel;
	if (my_rect.x >= 64 * 16)
	{
		Vel = -4;
	}
	if (my_rect.x <= 64 * 10)
	{
		stay++;
		Vel = 0;
	}
	if (stay > 40)
	{
		stay = 0;
		Vel = 4;
	}

	dem++;
	if (dem > 12)
	{
		if (status == 4)status = 1;
		else status++;
		dem = 0;
	}
	Motion(screen);
}

void Scientist::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = 0;;
	clip->y = 64 * 6 * (status - 1);
	clip->h = 64 * 6;
	clip->w = 64 * 10;
	Render(screen, my_rect.x, my_rect.y, clip);
}

//manage chung
MenuManage::MenuManage()
{

}

MenuManage::~MenuManage()
{
	mCaveman.free();
	mFarmer.free();
	mScientist.free();
}

bool MenuManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	//load caveman
	success = min(success, mCaveman.LoadFromFile("MenuAnimation/caveman.png", screen));
	mCaveman.SetRect(64*1, 64*13);
	

	//load farmer
	success = min(success, mFarmer.LoadFromFile("MenuAnimation/farmer.png", screen));
	mFarmer.SetRect(64*-10, 64*1);

	//load scientist
	success = min(success, mScientist.LoadFromFile("MenuAnimation/scientist.png", screen));
	mScientist.SetRect(64*16, 64*0);

	return success;
}

void MenuManage::HandleEvent(SDL_Renderer* screen)
{
	mCaveman.HandleEvent(screen);

	mFarmer.HandleEvent(screen);

	mScientist.HandleEvent(screen);
}