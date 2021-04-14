#ifndef COINS_H_
#define COINS_H_

#include "CommonFunction.h"
#include "BaseTexture.h"

class Coins : public BaseTexture
{
public:

	Coins();

	~Coins();

	void HandleEvent(SDL_Renderer* screen, int mmap);

	void Motion(SDL_Renderer* screen, int x, int y);

private:

	int status;

	int dem = 0;
};

class Score : public BaseTexture
{
public:
	Score();

	~Score();

	void HandleEvent(SDL_Renderer* screen);

private:
};

#endif