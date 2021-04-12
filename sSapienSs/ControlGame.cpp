#include "CommonFunction.h"
#include "ControlGame.h"

PauseButton::PauseButton()
{
	status = 0;
}

PauseButton::~PauseButton()
{
	free();
}

void PauseButton::HandleEvent(SDL_Renderer* screen)
{
	Render(screen, 0, 0);
}

Guide::Guide()
{
	status = 0;
}

Guide::~Guide()
{
	free();
}

void Guide::HandleEvent(SDL_Renderer* screen)
{
	Render(screen,0,0);
}

ControlGameManage::ControlGameManage()
{
	status = 0;
}

ControlGameManage::~ControlGameManage()
{
	// delete pause button
	mPauseButton.free();

	//delete guide
	mGuide.free();
}

bool ControlGameManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	//load pausebutton
	success = min(success,mPauseButton.LoadFromFile("Button/pause.png",screen));

	//load guide
	success = min(success,mGuide.LoadFromFile("Button/guide.png",screen));

	return success;
}

void ControlGameManage::HandleEvent(SDL_Renderer *screen, bool key_space)
{
	if (key_space == 1)
	{
		if(status == 1)status = 0;
		else status = 1;
	}

	if(status == 1)
	{
		mGuide.HandleEvent(screen);
	}

	else 
	{
		mPauseButton.HandleEvent(screen);
	}
}