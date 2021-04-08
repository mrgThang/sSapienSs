#ifndef WATER_FALL_H_
#define WATER_FALL_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class WaterFall : public BaseTexture
{
public:
	WaterFall();

	~WaterFall();

	void HandleEvent(SDL_Renderer* screen, int status_mov);

	void Motion(SDL_Renderer* screen);

	void GetPosition(int x, int y)
	{
		my_rect.x = x;
		my_rect.y = y;
	}

private:
	int status;
	int dem = 0;
};

#endif