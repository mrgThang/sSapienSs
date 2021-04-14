#include "CommonFunction.h"
#include "Coins.h"

bool dk[20][150];

Coins::Coins()
{
	status = 1;

	dem = 0;
}

Coins::~Coins()
{
	free();
}

void Coins::Reset()
{
	memset(dk, 0, sizeof(dk));
}

void Coins::HandleEvent(SDL_Renderer* screen, int mmap)
{
	dem++;
	if (dem >= 12)
	{
		status++;
		if (status >= 5)status = 1;
		dem = 0;
	}
	if(mmap == 1)
	{ 
		std::ifstream ifs("coins/coins.txt");

		for (int i = 0; i < 11; ++i)
		{
			for (int j = 0; j < 125; ++j)
			{
				int x;
				ifs >> x;
				if (x == 20 && dk[i][j] == 0)
				{
					Motion(screen, j, i);
				}
			}
		}
	}
}

void Coins::Motion(SDL_Renderer* screen, int x, int y)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->h = 64;
	clip->w = 64;
	clip->x = 64 * (status - 1);
	clip->y = 0;

	if(-128 <= x*64 -screen_mov && x*64 - screen_mov <= SCREEN_WIDTH + 128)
	Render(screen, x * 64 - screen_mov, y * 64, clip);

	if (hero_start_x >= x * 64 - screen_mov - 32 && hero_start_x <= x * 64 - screen_mov + 32)
	{
		if (hero_start_y >= y * 64 - 32 && hero_start_y <= y * 64 + 32)
		{
			SCORE += 1;
			dk[y][x] = 1;
		}
	}
}

Score::Score() {}

Score::~Score()
{
	free();
}

void Score::HandleEvent(SDL_Renderer* screen)
{
	Render(screen,64 * 3, 0);
}
