#ifndef BULLET_H_
#define BULLET_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Bullet : public BaseTexture
{
public:
	//initialize variable 
	Bullet();

    //delete variable
	~Bullet();

	void HandleEvent(SDL_Renderer* screen,SDL_Rect hero_rect);

	void Move(SDL_Renderer* screen,const Uint8* CurrentKeyState, SDL_Rect hero_rect);

private:
	int status = 0;
	int max_pos_bullet = 0;
};

#endif