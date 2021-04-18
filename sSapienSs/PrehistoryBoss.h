#ifndef PREHISTORY_BOSS_H_
#define PREHISTORY_BOSS_H_

#include "BaseTexture.h"
#include "CommonFunction.h"

// class chung
class PrehistoryBoss : public BaseTexture
{

};

//Boss HP
class HP : public PrehistoryBoss
{
public:
	HP();

	~HP();

	void HandleEvent(SDL_Renderer* screen, int x);

	void Motion(SDL_Renderer* screen);

private:

	int my_hp;
};

//warnign ở đầu game 
class BigWarning : public PrehistoryBoss
{
public:
	BigWarning();

	~BigWarning();

	void HandleEvent(SDL_Renderer* screen, int &manage_status);

	void Motion(SDL_Renderer* screen);

	void LoadSound()
	{
		mSound = Mix_LoadWAV("Music/BigWarning.wav");

		mScream = Mix_LoadWAV("Music/BossScream.wav");
	}

	void freeSound()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;

		Mix_FreeChunk(mScream);
		mScream = NULL;
	}

private:

	int so_luot;
	
	int dem;

	int status;

	Mix_Chunk* mSound;

	Mix_Chunk* mScream;
};

// biển báo warning
class Warning : public PrehistoryBoss
{
public:

	Warning();

	~Warning();

	void HandleEvent(SDL_Renderer* screen, int &manage_status);

	void Motion(SDL_Renderer * screen);

	void loadSound()
	{
		mSound = Mix_LoadWAV("Music/Warning.wav");
	}

	void freeSound()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;
	}

	void reset();

private:

	int status;
   
	int dem_status;

	int dem = 0;

	Mix_Chunk* mSound;
};

// kiểu đánh water1
class Water1 : public PrehistoryBoss
{
public:

	Water1();

	~Water1();

	void HandleEvent(SDL_Renderer* screen, int &manage_status);

	void Motion(SDL_Renderer * screen);

	void reset();

private:

	int dem;

	int dem_status;

	int status;

};

// kiểu đánh water2
class Water2 : public PrehistoryBoss
{
public:

	Water2();

	~Water2();

	void HandleEvent(SDL_Renderer* screen, int & manage_status);

	void Motion(SDL_Renderer* screen);

	void reset();

private:

	int dem = 0;
};

//kiểu đánh sand
class Sand : public PrehistoryBoss
{
public:

	Sand();

	~Sand();

	void HandleEvent(SDL_Renderer* screen, int &manage_status, int &so_luot_manage);

	void Motion(SDL_Renderer* screen);

	void reset();

private:

	int status;
};

// class boss 
class Boss : public PrehistoryBoss
{
public:

	Boss();

	~Boss();

	void HandleEvent(SDL_Renderer* screen, int& boss_action_status, int& last_manage_status);

	void Motion(SDL_Renderer* screen);

	void GoLeft(int *boss_action_status);

	void LoadSound()
	{
		mAngrySound = Mix_LoadWAV("Music/BossAngry.wav");
		mDizzySound = Mix_LoadWAV("Music/BossDizzy.wav");
	}

	void freeSound()
	{

		Mix_FreeChunk(mAngrySound);
		mAngrySound = NULL;

		Mix_FreeChunk(mDizzySound);
		mDizzySound = NULL;
	}

private:

    int status;

	int status2;

	int dem = 0;

	int so_luot = 0;

	Mix_Chunk* mAngrySound = NULL;

	Mix_Chunk* mDizzySound = NULL;

};

//class dieu kien
class PrehistoryBossManage : public PrehistoryBoss
{
public:
	PrehistoryBossManage();

	~PrehistoryBossManage();

	bool Load(SDL_Renderer* screen);

	void HandleEvent(SDL_Renderer *screen);

	void Motion(SDL_Renderer *screen);

	void SetWeaponStatus(int loaivukhi, int status1, int status2);

	int GetHP()
	{
		return my_hp;
	}

	void SetMyHP(int x)
	{
		my_hp = x;
	}

	void ResetStatus()
	{
		manage_status = 10;
	}

private:

	Boss mBoss;

	Water1 mWater1[10];

    Water2 mWater2[40];

    Warning mWarning[10];

    Sand mSand;

	BigWarning mBigWarning;

	HP mHP;

	int manage_status;

	int last_manage_status;

	int dem;

	int water1_pos1, water1_pos2, water1_pos3, water1_pos4;

	int so_luot;

	int luot_angry;

	int last_attack;

	int my_hp;

	int is_attacked;

	int dem_score;

	int water2sound_dem;

	Mix_Chunk* mWater1Sound;

	Mix_Chunk* mWater2Sound;
};

#endif
