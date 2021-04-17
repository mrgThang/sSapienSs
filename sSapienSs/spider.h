#ifndef SPIDER_H_
#define SPIDER_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Spider : public BaseTexture
{
public:
	Spider();

	~Spider();

	void HandldeEvent(SDL_Renderer* screen, int status_mov );

	void Motion(SDL_Renderer* screen);

	void Attack(SDL_Renderer* screen);

	void SetPosition(int x, int y);

	bool LoadToothFromFile(std::string path, SDL_Renderer* screen);

	void ToothRender(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* Center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

	int GetStatus()
	{
		return status;
	}

	void SetSpeed(int x)
	{
		speed = x;
	}

	void LoadSound()
	{
		mSound = Mix_LoadWAV("Music/Spider.wav");
	}

	void freeSound()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;
	}

private:
	SDL_Rect my_rect;

	int status;

	std::string dk;

	std::string lastdk;

	int dem;

	int speed;

	SDL_Texture* tooth;

	SDL_Rect my_tooth_rect;

	int my_tooth_status;

	Mix_Chunk* mSound;

	int dem_sound;

};

#endif