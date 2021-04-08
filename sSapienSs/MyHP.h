#ifndef MYHP_H_
#define MYHP_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class MyHP : public BaseTexture
{
public:
	MyHP();

	~MyHP();

	void HandleEvent(SDL_Renderer *screen, int HP_dispear);
};

#endif