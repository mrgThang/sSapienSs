#ifndef SPEAR_H_
#define SPEAR_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Spear : public BaseTexture
{
public:
	Spear();

	~Spear();

	void HandleEvent(SDL_Renderer* screen, int st2);

	void Motion(SDL_Renderer* screen);

	int GetSpearStatus()
	{
		return status;
	}

	int GetSpearStatus2()
	{
		return status2;
	}
	void LoadSound()
	{
		mSound = Mix_LoadWAV("Music/Attack.wav");
	}

	void freeSound()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;
	}

private:
	int status;
	int status2;
	int dem = 0;
	bool dk = 0;
	Mix_Chunk* mSound;
};

#endif