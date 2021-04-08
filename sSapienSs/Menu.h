#ifndef MENU_H_
#define MENU_H_

#include "BaseTexture.h"
#include "CommonFunction.h"

// class chung
class Menu : public BaseTexture
{

};

//class Caveman
class Caveman : public Menu
{
public:

	Caveman();

	~Caveman();

	void HandleEvent(SDL_Renderer* screen);

	void Motion(SDL_Renderer* screen);

	void Reset();

private:

	int dem;

	int status;

	int Vel;

	int stay;

	int statusVel;
};

//class Farmer
class Farmer : public Menu
{
public:

	Farmer();

	~Farmer();

	void HandleEvent(SDL_Renderer* screen);

	void Motion(SDL_Renderer* screen);

	void Reset();

private:

	int dem;
	
	int status;

	int Vel;

	int stay;

	int statusVel;
};

//class Scientist
class Scientist : public Menu
{
public:

	Scientist();

	~Scientist();

	void HandleEvent(SDL_Renderer* screen);

	void Motion(SDL_Renderer* screen);

	void Reset();

private:

	int dem;

	int status;

	int Vel;

	int stay;
};

//class dieu kien
class MenuManage : public Menu
{
public:
	MenuManage();

	~MenuManage();

	bool Load(SDL_Renderer* screen);

	void HandleEvent(SDL_Renderer* screen);

private:
	Scientist mScientist;

	Farmer mFarmer;

	Caveman mCaveman;
};

#endif
