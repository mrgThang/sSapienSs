#include"CommonFunction.h";
#include"BaseTexture.h";
#include"Bullet.h";

using namespace std;

Bullet::Bullet()
{
	//position of bullet
	my_rect.x = 0;
	my_rect.y = 0;
	status = 0;
	max_pos_bullet = 0;
}

Bullet::~Bullet()
{
	free();
}

void Bullet::HandleEvent(SDL_Renderer* screen,SDL_Rect hero_rect)
{
	const Uint8* CurrentKeyState = SDL_GetKeyboardState(NULL);

	Move(screen,CurrentKeyState,hero_rect);
}

void Bullet::Move(SDL_Renderer* screen,const Uint8* CurrentKeyState, SDL_Rect hero_rect)
{
	if (status == 1 && my_rect.x >= max_pos_bullet)
	{
		status = 0;
	}
	else if (status == 1)
	{
		my_rect.x += 32;
		Render(screen, my_rect.x, my_rect.y);
	}
	else if (CurrentKeyState[SDL_SCANCODE_A])
	{
		my_rect.x = hero_rect.x + hero_rect.w;
		my_rect.y = hero_rect.y + hero_rect.h / 2 - my_rect.h / 2;
		Render(screen, my_rect.x, my_rect.y);
		status = 1;
		max_pos_bullet = my_rect.x + SCREEN_WIDTH;
	}
}

