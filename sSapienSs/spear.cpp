#include "CommonFunction.h"
#include "spear.h"

Spear::Spear()
{
	status = 1;
	status2 = 1;
	dk = 0;
}

Spear::~Spear()
{
	free();
}

void Spear::HandleEvent(SDL_Renderer* screen, int st2)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_C] > 0 && dk == 0)
	{
		status2 = st2;
		dk = 1;
		if (status2 == 1)status = 1;
		else status = 5;
	}
	if (dk == 1)
	{
		if (status2 == 1)
		{
			dem++;
			if (dem >= 5)
			{
				status++, dem = 0;
			}
			if (status > 5) status = 1, dk = 0;
		}
		if (status2 == 2)
		{
			dem++;
			if (dem >= 5)
			{
				status--, dem = 0;
			}
			if (status < 1) status = 5, dk = 0;
		}
	}
	else
	{
		status2 = st2;
		if (status2 == 1)status = 1;
		else status = 5;
	}
	Motion(screen);
}

void Spear::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = (status - 1) * 128;
	clip->y = (status2 - 1) * 64;
	clip->w = 128;
	clip->h = 64;
	if (status2 == 1)Render(screen, hero_start_x, hero_start_y, clip);
	else if(status2 == 2)Render(screen, hero_start_x - 64, hero_start_y, clip);
}
