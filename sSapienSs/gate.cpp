#include "gate.h"
#include "CommonFunction.h"

Gate::Gate()
{
	status = 1;
	dem = 0;
	change_map = 0;
}

Gate::~Gate()
{
	free();
}

void Gate::HandleEvent(SDL_Renderer* screen, int status_mov, SDL_Event *e)
{
	change_map = 0;

	if (status_mov == 1)
	{
		my_rect.x += FOOT_DISTANT;
	}
	if (status_mov == 2)
	{
		my_rect.x -= FOOT_DISTANT;
	}

	if (hero_start_x >= my_rect.x && hero_start_x <= my_rect.x + 32 * 3)
	{
		if (hero_start_y >= my_rect.y && hero_start_y <= my_rect.y + 32 * 3)
		{
			const Uint8* CurrentKeyState = SDL_GetKeyboardState(NULL);
			if (CurrentKeyState[SDL_SCANCODE_E])
			{
				change_map = 1;
			}
		}
	}

	dem++;
	if (dem >= 12)
	{
		status++;
		if (status > 4)status = 1;
		dem = 0;
	}

	Motion(screen);
}

void Gate::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->x = (status - 1) * 128;
	clip->y = 0;
	clip->w = 128;
	clip->h = 128;
	Render(screen, my_rect.x, my_rect.y, clip);
}