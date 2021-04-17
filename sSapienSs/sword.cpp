#include "CommonFunction.h"
#include "sword.h"

Sword::Sword()
{
	status = 1;
	status2 = 1;
	dk = 0;
	BaseTexture();
}

Sword::~Sword()
{
	free();
}

void Sword::HandleEvent(SDL_Renderer *screen, int st2)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_C] > 0 && dk == 0)
	{
		status2 = st2;
		dk = 1;
		if (status2 == 1)status = 1;
		else status = 11;
		Mix_PlayChannel(-1, mSound, 0);
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
			if (status > 11) status = 1, dk = 0;
		}
		if (status2 == 2)
		{
			dem++;
			if (dem >= 5)
			{
				status--, dem = 0;
			}
			if (status < 1) status = 11, dk = 0;
		}
	}
	else
	{
		status2 = st2;
		if (status2 == 1)status = 1;
		else status = 11;
	}
	Motion(screen);
}

void Sword::Motion(SDL_Renderer* screen)
{
	SDL_Rect *clip = new SDL_Rect;
	clip->x = (status-1) * 128;
	clip->y = (status2 - 1) * 64;
	clip->w = 128;
	clip->h = 64;
	if(status2 == 1)Render(screen, hero_start_x, hero_start_y, clip);
	else Render(screen, hero_start_x - 64, hero_start_y, clip);
}
