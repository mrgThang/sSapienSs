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

class CurrentScore : public ScoreBoard
{
public:
	CurrentScore();

	~CurrentScore();

	void HandleEvent(SDL_Renderer* screen);
};

class CurrentName : public ScoreBoard
{
public:
	CurrentName();

	~CurrentName();

	void HandleEvent(SDL_Renderer* screen);
};

class ScoreBoardName : public ScoreBoard
{
public:
	ScoreBoardName();

	~ScoreBoardName();

	void HandleEvent(SDL_Renderer* screen);
};

class Member:public ScoreBoard
{
public:
	Member();

	~Member();

	void HandleEvent(SDL_Renderer* screen, int &move, int &line);

	int ReturnStatus()
	{
		return status;
	}

private:
	int status;

	int dem = 0;
};

class ScoreBoardManage : public ScoreBoard
{
public:
	ScoreBoardManage();

	~ScoreBoardManage();

	void HandleEvent(SDL_Renderer* screen);

	bool Load(SDL_Renderer* screen);

	bool ReturnPressESC()
	{
		return press_esc;
	}

private:
	Member mMember[11];

	ScoreBoardName mScoreBoardName[11];

	CurrentScore mCurrentScore;

	CurrentName mCurrentName;

	int current_score;

	std::string lastname;

	int lastscore;

	int data_dem;

	std::vector<std::pair<int, std::string>> data;

	int status;

	int up_member;

	int new_member_status;

	int up_member_status[4];

	int up_member_line[4];

	int new_member_line;
	
	bool press_esc;
};

#endif