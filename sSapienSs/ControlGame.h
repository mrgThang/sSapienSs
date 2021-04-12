#ifndef CONTROL_GAME_H_
#define CONTROL_GAME_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class ControlGame :public BaseTexture
{

};

class PauseButton:public ControlGame
{
public:

	PauseButton();
	
	~PauseButton();

	void HandleEvent(SDL_Renderer* screen);

private:

	int status;
};

class Guide : public ControlGame
{
public:

	Guide();

	~Guide();

	void HandleEvent(SDL_Renderer* screen);
private:

	int status;
};

class ControlGameManage : public ControlGame
{
public:
	ControlGameManage();

	~ControlGameManage();

	void HandleEvent(SDL_Renderer* screen, bool key_space);

	bool Load(SDL_Renderer* screen);

	bool GetStatus()
	{
		return status;
	}

private:
	bool status;

	PauseButton mPauseButton;

	Guide mGuide;
};

#endif