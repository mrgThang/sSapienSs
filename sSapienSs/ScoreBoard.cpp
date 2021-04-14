#include "CommonFunction.h"
#include "ScoreBoard.h"

//start button manage
StartButton::StartButton()
{
	status = 1;
	press = 0;
}

StartButton::~StartButton()
{
	free();
}

void StartButton::HandleEvent(SDL_Renderer* screen, SDL_Event* e)
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
	Motion(screen);
}

void StartButton::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->w = 64 * 10;
	clip->h = 64 * 2;
	clip->x = 0;
	clip->y = 64*2*(status - 1);

	Render(screen, my_rect.x, my_rect.y, clip);
}

//name manage
Name::~Name()
{
	free();
}

Name::Name()
{
	last_name = "";
}

void Name::HandeEvent(SDL_Renderer* screen, int x)
{
	if (NAME.size() < 20)
	{
		if (97 <= x && x <= 122)
		{
			char neww = x;
			NAME += x;
			SDL_Color textColor = { 0,0,0,255 };
			LoadFromRenderedText(NAME, textColor, screen);
		}

		if (x == 32)
		{
			NAME += ' ';
			SDL_Color textColor = { 0,0,0,255 };
			LoadFromRenderedText(NAME, textColor, screen);
		}
	}
	if (NAME.size() > 0)
	{
		if (x == 8)
		{
			NAME.erase(NAME.size() - 1, 1);
			SDL_Color textColor = { 0,0,0,255 };
			LoadFromRenderedText(NAME, textColor, screen);
		}
	}
	Render(screen, 64 * 6, 64 * 5+32);
}

//vertical bar manage
VerticalBar::VerticalBar()
{
	status = 0;
}

VerticalBar::~VerticalBar()
{
	free();
}

void VerticalBar::HandleEvent(SDL_Renderer* screen)
{
	int x = NAME.size();
	dem++;
	if (dem > 20)
	{
		status = 1 - status;
		dem = 0;
	}
	if (status == 1)Render(screen, 64 * 6 + x * 28, 64 * 5+32);
}

//typing manage
TypingManage::TypingManage()
{
	over = 0;
}

TypingManage::~TypingManage()
{
	mName.free();

	mVerticalBar.free();
}

bool TypingManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	over = 0;

	success = min(success, mName.LoadFont("font/Kingthings.ttf", 48));

	success = min(success, mVerticalBar.LoadFont("font/Kingthings.ttf", 48));

	SDL_Color textColor = { 0,0,0,255 };

	success = min(success, mVerticalBar.LoadFromRenderedText("|", textColor, screen));

	success = min(success, mStartButton.LoadFromFile("coins/StartButton.png", screen));
	mStartButton.SetRect(64 * 5, 64 * 7);

	return success;
}

void TypingManage::HandleEvent(SDL_Renderer* screen, bool key[200],SDL_Event *e)
{
	
	for (int i = 1; i <= 122; ++i)
	{
		if (key[i] == 1)
		{
			mName.HandeEvent(screen, i);
		}
	}

	mName.HandeEvent(screen, 0);

	mVerticalBar.HandleEvent(screen);

	mStartButton.HandleEvent(screen,e);

	over = mStartButton.ReturnPress();	
}