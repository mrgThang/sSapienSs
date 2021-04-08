#include "WaterFall.h"
#include "CommonFunction.h"

WaterFall::WaterFall()
{
	status = 1;
	dem = 0;
}

WaterFall::~WaterFall()
{
	free();
}

void WaterFall::HandleEvent(SDL_Renderer* screen, int status_mov)
{
	if (status_mov == 1)
	{
		my_rect.x += FOOT_DISTANT;
	}
	if (status_mov == 2)
	{
		my_rect.x -= FOOT_DISTANT;
	}

	dem++;
	if (dem >= 12)
	{
	    status++;
		if (status == 4)status = 1;
		dem = 0;
	}

	Motion(screen);
}

void WaterFall::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = (status - 1) * 64*4;
	clip->y = 0;
	clip->w = 64*4;
	clip->h = 64*9;
	Render(screen, my_rect.x, my_rect.y, clip);
}