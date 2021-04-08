#ifndef RHINO_H_
#define RHINO_H_

#include"CommonFunction.h"
#include"BaseTexture.h"

class Rhino : public BaseTexture
{
public:
	Rhino();

	~Rhino();

	void HandldeEvent(SDL_Renderer* screen, int status_mov, int sword_status, int sword_status2, int spear_status, int spear_status2);

	void Motion(SDL_Renderer* screen);

	void HPMotion(SDL_Renderer* screen);

	void MoveLeft();

	void MoveRight();

	void MoveDown();

	void Attack();

	void Attacked(int sword_status, int sword_status2, int spear_status, int spear_status2);

	void SetPosition(int x, int y);

	bool LoadHPFromFile(std::string path, SDL_Renderer* screen);

	void HPRender(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* Center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

	int GetStatus()
	{
		return status;
	}

private:
	SDL_Rect my_rect;

	SDL_Rect my_HP_rect;

	int status;

	int status2;

	int dk = 0;

	int dem;

	int HP;

	Uint32 tick;

	Uint32 tick2;

	SDL_Texture* my_HP;
};

#endif