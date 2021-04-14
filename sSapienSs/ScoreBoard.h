#ifndef SCORE_BOARD_H_
#define SCORE_BOARD_H_

#include "CommonFunction.h"
#include "BaseTexture.h"

class ScoreBoard : public BaseTexture
{

};

class StartButton : public ScoreBoard
{
public:
	StartButton();

	~StartButton();

	void HandleEvent(SDL_Renderer* screen, SDL_Event* e);

	void Motion(SDL_Renderer* screen);

	int ReturnPress()
	{
		return press;
	}

private:
	int status;

	bool press;
};

class Name : public ScoreBoard
{
public:

	Name();

	~Name();

	void HandeEvent(SDL_Renderer* screen, int x);
private:

	std::string last_name;
};

class VerticalBar : public ScoreBoard
{
public:
	VerticalBar();

	~VerticalBar();

	void HandleEvent(SDL_Renderer* screen);

private:
	int status;

	int dem = 0;
};

class TypingManage : public ScoreBoard
{
public:

	TypingManage();

	~TypingManage();

	void HandleEvent(SDL_Renderer* screen, bool key[200], SDL_Event *e);

	bool Load(SDL_Renderer* screen);

	bool ReturnOver()
	{
		return over;
	}
private:
	
	Name mName;

	VerticalBar mVerticalBar;

	StartButton mStartButton;

	bool over;
};

#endif