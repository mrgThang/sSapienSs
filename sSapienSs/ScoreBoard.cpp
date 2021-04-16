#include "CommonFunction.h"
#include "ScoreBoard.h"

enum
{
	increase_score = 1,
	new_member_motion = 2,
	stay = 3,
	move_left = 4,
	move_down = 5,
	move_right = 6,
	out = 7,
	move_up = 8,
	angry = 9, 
	done = 10,
	congratulations = 11
};

//start button manage
StartButton::StartButton()
{
	status = 1;
	press = 0;
}

StartButton::~StartButton()
{
	free();
}

void StartButton::HandleEvent(SDL_Renderer* screen, SDL_Event* e)
{
	press = 0;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < my_rect.x || x > my_rect.x + my_rect.w || y < my_rect.y || y > my_rect.y + my_rect.h)
		{
			status = 1;
		}
		else
		{
			status = 2;
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				press = 1;
			}
		}
	}
	Motion(screen);
}

void StartButton::Motion(SDL_Renderer* screen)
{
	SDL_Rect* clip = new SDL_Rect;
	clip->w = 64 * 10;
	clip->h = 64 * 2;
	clip->x = 0;
	clip->y = 64*2*(status - 1);

	Render(screen, my_rect.x, my_rect.y, clip);
}

//name manage
Name::~Name()
{
	free();
}

Name::Name()
{
	last_name = "";
}

void Name::HandeEvent(SDL_Renderer* screen, int x)
{
	if (NAME.size() < 20)
	{
		if (97 <= x && x <= 122)
		{
			char neww = x;
			NAME += x;
			SDL_Color textColor = { 0,0,0,255 };
			LoadFromRenderedText(NAME, textColor, screen);
		}
	}
	if (NAME.size() > 0)
	{
		if (x == 8)
		{
			NAME.erase(NAME.size() - 1, 1);
			SDL_Color textColor = { 0,0,0,255 };
			LoadFromRenderedText(NAME, textColor, screen);
		}
	}
	Render(screen, 64 * 6, 64 * 5+32);
}

//vertical bar manage
VerticalBar::VerticalBar()
{
	status = 0;
}

VerticalBar::~VerticalBar()
{
	free();
}

void VerticalBar::HandleEvent(SDL_Renderer* screen)
{
	int x = NAME.size();
	dem++;
	if (dem > 20)
	{
		status = 1 - status;
		dem = 0;
	}
	if (status == 1)Render(screen, 64 * 6 + x * 28, 64 * 5+32);
}

//typing manage
TypingManage::TypingManage()
{
	over = 0;
}

TypingManage::~TypingManage()
{
	mName.free();

	mVerticalBar.free();

	Mix_FreeChunk(mButtonSound);
	mButtonSound = NULL;
}

bool TypingManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	over = 0;

	success = min(success, mName.LoadFont("font/Kingthings.ttf", 48));

	success = min(success, mVerticalBar.LoadFont("font/Kingthings.ttf", 48));

	SDL_Color textColor = { 0,0,0,255 };

	success = min(success, mVerticalBar.LoadFromRenderedText("|", textColor, screen));

	success = min(success, mStartButton.LoadFromFile("coins/StartButton.png", screen));
	mStartButton.SetRect(64 * 5, 64 * 7);

	mButtonSound = Mix_LoadWAV("Music/Button.wav");

	return success;
}

void TypingManage::HandleEvent(SDL_Renderer* screen, bool key[200],SDL_Event *e)
{
	
	for (int i = 1; i <= 122; ++i)
	{
		if (key[i] == 1)
		{
			mName.HandeEvent(screen, i);
		}
	}

	mName.HandeEvent(screen, 0);

	mVerticalBar.HandleEvent(screen);

	mStartButton.HandleEvent(screen,e);

	over = mStartButton.ReturnPress();

	if (over == 1)Mix_PlayChannel(-1, mButtonSound, 0);
}

//current score manage
CurrentScore::CurrentScore()
{

}

CurrentScore::~CurrentScore()
{
	free();
}

void CurrentScore::HandleEvent(SDL_Renderer* screen)
{
	Render(screen, my_rect.x, my_rect.y);
}

//current name manage
CurrentName::CurrentName()
{

}

CurrentName::~CurrentName()
{
	free();
}

void CurrentName::HandleEvent(SDL_Renderer* screen)
{
	Render(screen, my_rect.x, my_rect.y);
}

//manage score board name
ScoreBoardName::ScoreBoardName()
{

}

ScoreBoardName::~ScoreBoardName()
{
	free();
}

void ScoreBoardName::HandleEvent(SDL_Renderer* screen)
{
	Render(screen, my_rect.x, my_rect.y);
}

//manage member
Member::Member()
{

}

Member::~Member()
{
	free();
}

void Member::HandleEvent(SDL_Renderer* screen, int &move, int &line)
{
	if (move == move_right)
	{
		if (my_rect.x < line)my_rect.x += 8;
		else move = stay;
	}
	else if (move == move_left)
	{
		if (my_rect.x > line)my_rect.x -= 8;
		else
		{
			move = move_down;
			line = my_rect.y + 64*2;
		}
	}
	else if (move == move_down)
	{
		if (my_rect.y < line)my_rect.y += 4;
		else
		{
			move = move_right;
			line = my_rect.x + 64 * 5;
		}
	}
	else if (move == move_up)
	{
		if (my_rect.y > line)my_rect.y -= 4;
		else move = stay;
	}
	else if (move == out)
	{
		if (my_rect.y < line) my_rect.y += 4;
	}
	else if (move == angry)
	{
		dem++;
		if ((dem / 10) % 3 == 0)my_rect.y += 4;
		else if ((dem / 10) % 3 == 1)1;
		else my_rect.y -= 4;
		if (dem == 109)
		{
			dem = 0;
			move = done;
			my_rect.y = line;
		}
	}

	Render(screen, my_rect.x, my_rect.y);

	status = move;
}

// score board manage
ScoreBoardManage::ScoreBoardManage()
{
	status = increase_score;

	current_score = -50;
}

ScoreBoardManage::~ScoreBoardManage()
{
	for (int i = 0; i < 4; ++i)
	{
		mMember[i].free();
		mScoreBoardName[i].free();
	}
	mCurrentScore.free();
	mCurrentName.free();
}

bool ScoreBoardManage::Load(SDL_Renderer* screen)
{
	bool success = 1;

	press_esc = 0;

	up_member = 2;

	new_member_status = move_up;

	status = increase_score;

	current_score = -50;

	for(int i = 0; i < 3; ++i)
	up_member_status[i] = stay;

	SDL_Color textColor = { 200, 200, 0, 255 };

	data_dem = 0;
	
	for (int i = 0; i < 4; ++i)
	{
		//load score board name font
		success = min(success, mScoreBoardName[i].LoadFont("font/Kingthings.ttf",32));

		//load member
		success = min(success, mMember[i].LoadFromFile("coins/ScoreContent.png", screen));
	}

	//read file
	std::ifstream ifs("Data/data.txt");
	while (data.size())data.pop_back();
	while (ifs >> lastscore >> lastname)
	{
		data.push_back(std::pair<int, std::string>(lastscore, lastname));
	}

	//load score board name
	for (int i = 0; i < data.size(); ++i)
	{
		std::stringstream lastdata;

		lastdata.str("");

		lastdata <<" " <<  data[i].second  << " " << data[i].first;

		success = min(success, mScoreBoardName[i].LoadFromRenderedText(lastdata.str().c_str(), textColor, screen));
	}

	//set rect
	for (int i = 0; i < 3; ++i)
	{
		mMember[i].SetRect(64 * 6 - 32, 128 * (i + 2) + 32);
		SDL_Rect member_rect = mMember[i].GetRect();
		mScoreBoardName[i].SetRect(member_rect.x + 32, member_rect.y + 24);
	}

	//set font current score + name
	success = min(success, mCurrentScore.LoadFont("font/Kingthings.ttf", 64));
	success = min(success, mCurrentName.LoadFont("font/Kingthings.ttf", 64));
	success = min(success, mCurrentName.LoadFromRenderedText(NAME, textColor, screen));

    //set rect new_member
	mMember[3].SetRect(64 * 6 - 32, 64 * 11);
	SDL_Rect member_rect3 = mMember[3].GetRect();
	mScoreBoardName[3].SetRect(member_rect3.x + 32, member_rect3.y + 24);

	//load name new_meber
	std::stringstream currentdata;
	currentdata.str("");
	currentdata << " " << NAME << " " << SCORE;
	success = min(success, mScoreBoardName[3].LoadFromRenderedText(currentdata.str().c_str(), textColor, screen));

	new_member_line = mMember[2].GetRect().y + 32*3;

	return success;
}

void ScoreBoardManage::HandleEvent(SDL_Renderer* screen)
{
	if (status == increase_score)
	{
		//if(current_score < SCORE)
		for (int i = 0; i < 3; ++i)
		{
			mMember[i].HandleEvent(screen,up_member_status[i],up_member_line[i]);
			mScoreBoardName[i].HandleEvent(screen);
		}

		if (current_score < SCORE)
		{
			current_score++;

			std::stringstream current;
			current.str("");
			current << current_score;

			SDL_Color textColor = { 200, 200, 0, 255 };

			mCurrentScore.LoadFromRenderedText(current.str().c_str(), textColor, screen);
		}
		else
		{
			current_score++;
			if (current_score == SCORE + 50)status = new_member_motion;
		}
		
	}

	if (status == new_member_motion)
	{
		mMember[3].HandleEvent(screen, new_member_status,new_member_line);
		mScoreBoardName[3].SetRect(mMember[3].GetRect().x + 32, mMember[3].GetRect().y + 24);
		mScoreBoardName[3].HandleEvent(screen);

		if (new_member_status == stay)
		{
			if (up_member >= 0 && SCORE > data[up_member].first)
			{
				up_member--;
				new_member_status = move_up;
				if(up_member >= 0)new_member_line = mMember[up_member].GetRect().y + 32 * 3;
				else new_member_line = mMember[up_member + 1].GetRect().y;
				up_member_status[up_member+1] = move_left;
				up_member_line[up_member+1] = mMember[up_member + 1].GetRect().x - 64 * 5;
			}
			else if (up_member >= 0)
			{
				new_member_status = angry; 
				new_member_line = mMember[up_member].GetRect().y + 128;
			}
			else
			{
				new_member_status = done;
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			mMember[i].HandleEvent(screen, up_member_status[i], up_member_line[i]);
			mScoreBoardName[i].SetRect(mMember[i].GetRect().x + 32, mMember[i].GetRect().y + 24);
			mScoreBoardName[i].HandleEvent(screen);
		}

		if (new_member_status == done)
		{
			status = done;
		}
	}

	else if (status == done)
	{
		if (SCORE > data[2].first)
		{
			up_member_status[2] = out;
			up_member_line[2] = 64 * 12;
			up_member_status[3] = stay;
			if (mMember[2].GetRect().y == 64 * 12)status = congratulations;
		}
		else
		{
			up_member_status[3] = out;
			up_member_line[3] = 64 * 12;
			if (mMember[3].GetRect().y == 64 * 12)status = congratulations;
		}
		for (int i = 0; i < 4; ++i)
		{
			mMember[i].HandleEvent(screen, up_member_status[i], up_member_line[i]);
			mScoreBoardName[i].SetRect(mMember[i].GetRect().x + 32, mMember[i].GetRect().y + 24);
			mScoreBoardName[i].HandleEvent(screen);
		}
	}

	else if (status == congratulations)
	{
		if (SCORE > data[2].first)
		{
			std::ofstream ofs("Data/data.txt");
			if (SCORE > data[0].first)
			{
				ofs << SCORE << " " << NAME << std::endl;
				ofs << data[0].first << " " << data[0].second << std::endl;
				ofs << data[1].first << " " << data[1].second;
			}
			else if (SCORE > data[1].first)
			{
				ofs << data[0].first << " " << data[0].second << std::endl;
				ofs << SCORE << " " << NAME << std::endl;
				ofs << data[1].first << " " << data[1].second;
			}
			else
			{
				ofs << data[0].first << " " << data[0].second << std::endl;
				ofs << data[1].first << " " << data[1].second << std::endl;
				ofs << SCORE << " " << NAME;
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			mMember[i].HandleEvent(screen, up_member_status[i], up_member_line[i]);
			mScoreBoardName[i].SetRect(mMember[i].GetRect().x + 32, mMember[i].GetRect().y + 24);
			mScoreBoardName[i].HandleEvent(screen);
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_ESCAPE])press_esc = 1;

	}

	mCurrentScore.SetRect(64 * 16 + 32, 64 * 4);
	mCurrentName.SetRect(64 * 15, 64 * 2);
	mCurrentScore.HandleEvent(screen);
	mCurrentName.HandleEvent(screen);
}