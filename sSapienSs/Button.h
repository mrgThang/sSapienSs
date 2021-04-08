#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunction.h"
#include "BaseTexture.h"

class Button : public BaseTexture
{
public:
	Button();

	~Button();

	void HandleEvent(SDL_Renderer* screen, SDL_Event *e);

	int ReturnPressState()
	{
		return press;
	}

private:
	int status;

	bool press;
};

#endif