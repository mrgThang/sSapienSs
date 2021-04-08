#include "chest.h"
#include"CommonFunction.h"

Chest::Chest()
{
	status = 1;
	dk = 0;
	dem = 0;
}

Chest::~Chest()
{
	free();
}

void Chest::HandleEvent(SDL_Renderer* screen, int status_mov)
{
	
	if (status_mov == 1)
	{
		my_rect.x += FOOT_DISTANT;
	}
	if (status_mov == 2)
	{
		my_rect.x -= FOOT_DISTANT;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_E])
	{
		if (hero_start_x >= my_rect.x  && hero_start_x <= my_rect.x + 128 && hero_start_y == my_rect.y + 64)
		{
			dk = 1;
		}
	}

	if (dk == 1)
	{
		dem++;
		if (dem >= 12)
		{
			if (status < 3)status++;
			dem = 0;
		}
	}

	Motion(screen);
}

void Chest::Motion(SDL_Renderer* screen)
{
	SDL_Rect *clip = new SDL_Rect;
	clip->x = (status - 1) * 128;
	clip->y = 0;
	clip->w = 128;
	clip->h = 128;
	Render(screen, my_rect.x, my_rect.y, clip);
}

WeaponInChest::WeaponInChest()
{
	dem = 0;
}

WeaponInChest::~WeaponInChest()
{
	free();
}

void WeaponInChest::HandleEvent(SDL_Renderer* screen, int status_mov)
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
	if (dem < 24)
	{
		Render(screen, my_rect.x, my_rect.y, NULL);
	}
	else if (dem < 48)
	{
		my_rect.y -= 4;
		Render(screen, my_rect.x, my_rect.y, NULL);
	}
	else if (dem < 48+24)
	{
		if (angle < 360)angle += 5;
		else angle = 0.0;
		Render(screen, my_rect.x, my_rect.y, NULL, angle);
	}
	else if (dem < 48+48+12)
	{
		if (angle > 0)angle -= 5;
		else angle = 360;
		Render(screen, my_rect.x, my_rect.y, NULL, angle);
	}
	else if (dem < 48 + 48 + 24)
	{
		if (angle < 360)angle += 5;
		else angle = 0.0;
		Render(screen, my_rect.x, my_rect.y, NULL, angle);
	}
	else if(dem < 150)Render(screen, my_rect.x, my_rect.y, NULL, angle);
}