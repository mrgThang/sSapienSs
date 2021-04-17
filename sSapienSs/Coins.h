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

	void Reset();

	void FreeSound()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;
	}

	void LoadSound()
	{
		mSound = Mix_LoadWAV("Music/Coins.wav");
	}

private:

	int status;

	int dem = 0;

	Mix_Chunk* mSound;
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