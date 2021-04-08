#include "CommonFunction.h"
#include "MyHP.h"

MyHP::MyHP()
{
	my_rect.x = SCREEN_WIDTH - 3 * 64;
	my_rect.y = 0;
}

MyHP::~MyHP()
{
	free();
}

void MyHP::HandleEvent(SDL_Renderer* screen, int hp)
{

	SDL_Rect* clip = new SDL_Rect;

	clip->h = 64;
	clip->w = 64 * 3;
	clip->x = (hp - 1) * 64 * 3;
	clip->y = 0;
	Render(screen, my_rect.x, my_rect.y, clip);
}