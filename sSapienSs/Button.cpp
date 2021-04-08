#include "Button.h"

Button::Button()
{
	status = 1;
	press = 0;
}

Button::~Button()
{
	free();
}

void Button::HandleEvent(SDL_Renderer* screen, SDL_Event *e)
{
	press = 0;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < my_rect.x || x > my_rect.x + my_rect.w || y < my_rect.y || y > my_rect.y + my_rect.h)
		{
			status = 1;
		}
		else
		{
			status = 2;
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				press = 1;
			}
		}
	}

	SDL_Rect* clip = new SDL_Rect;
	clip->x = (my_rect.w) / 2 * (status - 1);
    clip->y = 0;
	clip->h = my_rect.h;
	clip->w = my_rect.w/2;
	Render(screen, my_rect.x, my_rect.y, clip);
}