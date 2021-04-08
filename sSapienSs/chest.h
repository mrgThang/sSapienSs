#ifndef CHEST_H_
#define CHEST_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Chest : public BaseTexture
{
public:
	Chest();

	~Chest();

	void HandleEvent(SDL_Renderer* screen, int status_mov);

	void Motion(SDL_Renderer* screen);

	void GetPosition(int x, int y)
	{
		my_rect.x = x;
		my_rect.y = y;
	}

	bool Getdk()
	{
		return dk;
	}

private:
	int status;
	bool dk = 0;
	int dem = 0;
};

class WeaponInChest : public BaseTexture
{
public:
	WeaponInChest();

	~WeaponInChest();

	void HandleEvent(SDL_Renderer* screen, int status_mov);

private:
	int dem = 0;
	double angle = 0.0;
};

#endif