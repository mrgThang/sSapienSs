#ifndef GATE_H_
#define GATE_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Gate : public BaseTexture
{
public:
	Gate();

	~Gate();

	void HandleEvent(SDL_Renderer* screen, int status_mov, SDL_Event *e);

	void Motion(SDL_Renderer* screen);

	void GetPosition(int x, int y)
	{
		my_rect.x = x;
		my_rect.y = y;
	}

	bool ChangeMap()
	{
		return change_map;
	}

	void Start()
	{
		change_map = 0;
	}

private:
	int status;
	int dem = 0;
	bool change_map;
};

#endif