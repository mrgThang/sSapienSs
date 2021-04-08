#include "CommonFunction.h"
#include "NormalEnemies.h"

bool ChCollision(SDL_Rect rect, std::string s)
{
    if (s == "right")
    {
        int x = (rect.x + rect.w) / FOOT_DISTANT;
        int y = (rect.y) / FOOT_DISTANT;
        if (detect[y][x][1] == 1)return false;
        return true;
    }

    if (s == "left")
    {
        int x = (rect.x - TILE_SIZE) / FOOT_DISTANT;
        int y = (rect.y) / FOOT_DISTANT;
        if (detect[y][x][1] == 1)return false;
        return true;
    }

    if (s == "down")
    {
        int x = rect.x / FOOT_DISTANT;
        int y = (rect.y + rect.h) / FOOT_DISTANT;
        if (detect[y][x][2] == 1)return false;
        return true;
    }

    return true;
}

SkeletonEnemies::SkeletonEnemies()
{
    BaseTexture();
	my_rect.w = 64;
	my_rect.h = 64;
	my_HP_rect.w = 64;
	my_HP_rect.h = 16;
	status = 0;
    dk = 0;
    dem = 0;
    HP = 2;
    tick = 0;
    tick2 = 0;
}

SkeletonEnemies::~SkeletonEnemies()
{
	free();
}

void SkeletonEnemies::SetPosition(int x, int y)
{
    my_rect.x = x;
    my_rect.y = y;
}

void SkeletonEnemies::HandldeEvent(SDL_Renderer* screen, int status_mov, int sword_status, int sword_status2, int spear_status, int spear_status2)
{
    Attacked(sword_status, sword_status2,spear_status, spear_status2);

    if (my_rect.y > 13 * TILE_SIZE || HP <= 0)
    {
        free();
        return;
    }
    
    if (status_mov == 1)
    {
        my_rect.x += FOOT_DISTANT;
    }
    if (status_mov == 2)
    {
        my_rect.x -= FOOT_DISTANT;
    }
    
    MoveLeft();
    
	MoveRight();

	if(my_rect.x >= 0 && my_rect.x < SCREEN_WIDTH)MoveDown();

    Attack();

    if (dk == 0)
    {
        dem++;
        if (dem >= 12)
        {
            status++;
            dem = 0;
        }
        if (status < 1 || status > 2)status = 1;
    }

    dk = 0;

    HPMotion(screen);

    Motion(screen);
}

void SkeletonEnemies::HPMotion(SDL_Renderer* screen)
{
    SDL_Rect* clipz = new SDL_Rect;
    clipz->w = 64;
    clipz->h = 16;
    clipz->x = (HP-1) * 64;
    clipz->y = 0;
    HPRender(screen, my_rect.x + 16, my_rect.y - 8, clipz);
}

void SkeletonEnemies::Motion(SDL_Renderer* screen)
{
	SDL_Rect* zclip = new SDL_Rect;
	zclip->x = 64 * (status - 1);
	zclip->y = 0;
	zclip->w = 64;
	zclip->h = 64;
	Render(screen, my_rect.x, my_rect.y, zclip);
}

void SkeletonEnemies::MoveDown()
{
    bool x = ChCollision(my_rect, "down");
    if(x == 1 && my_rect.x >= 0)my_rect.y += FOOT_DISTANT;
}

void SkeletonEnemies::MoveLeft()
{
    bool x = ChCollision(my_rect, "left");

    if (my_rect.x - ATK_DISTANT <= hero_start_x + 64 && my_rect.x > hero_start_x + 64)
    {
        if(x > 0)
        {
            my_rect.x -= FOOT_DISTANT/2;
            dem++;
            if (dem >= 12)
            {
                status++;
                dem = 0;
            }
            if (status < 3 || status > 4)status = 3;
            dk = 1;
        }
    }
}

void SkeletonEnemies::MoveRight()
{
    bool x = ChCollision(my_rect, "right");

    if (my_rect.x + 64 + ATK_DISTANT >= hero_start_x - 64 && my_rect.x < hero_start_x - 64)
    {
        if (x > 0)
        {
            my_rect.x += FOOT_DISTANT/2;
            dem++;
            if (dem >= 12)
            {
                status++;
                dem = 0;
            }
            if (status < 3 || status > 4)status = 3;
            dk = 1;
        }
    }
}

void SkeletonEnemies::Attack()
{
    if_attack_hero = 0;

    //attack left
    if (my_rect.x <= hero_start_x + 64 && my_rect.x >= hero_start_x && my_rect.y == hero_start_y)
    {
        if (status != 1 && status != 6)status = 1;
        dem++;
        if (dem >= 20)
        {
            if (status == 1)status = 6;
            else if (status == 6)status = 1;
            dem = 0;
        }
        dk = 1;
        if (status == 6)
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick2 + 200)
            {
                if_attack_hero = 1;
            }
            tick2 = current_tick;
        }
    }

    //attack right
    else if (my_rect.x +64 >= hero_start_x && my_rect.x <= hero_start_x && my_rect.y == hero_start_y)
    {
        if (status != 1 && status != 5)status = 1;
        dem++;
        if (dem >= 20)
        {
            if (status == 1)status = 5;
            else if (status == 5)status = 1;
            dem = 0;
        }
        dk = 1;
        if (status == 5)
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick2 + 200)
            {
                if_attack_hero = 1;
            }
            tick2 = current_tick;
        }
    }
}

void SkeletonEnemies::Attacked(int sword_status, int sword_status2, int spear_status, int spear_status2)
{
    if (my_rect.x < hero_start_x + 128 && my_rect.x >= hero_start_x && my_rect.y == hero_start_y)
    {
        if (sword_status2 == 1 && (sword_status == 3|| sword_status == 4|| sword_status == 5 || sword_status == 6 || sword_status == 7))
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick + 200)
            {
                HP--;
            }
            tick = current_tick;
        }

        if (spear_status2 == 1 && spear_status == 4)
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick + 200)
            {
                HP--;
            }
            tick = current_tick;
        }
    }

    if (my_rect.x > hero_start_x - 128 && my_rect.x <= hero_start_x && my_rect.y == hero_start_y)
    {
        if (sword_status2 == 2 && (sword_status == 5 || sword_status == 6 || sword_status == 7 || sword_status == 8 || sword_status == 9))
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick + 200)
            {
                HP--;
            }
            tick = current_tick;
        }

        if (spear_status2 == 2 && spear_status == 2)
        {
            Uint32 current_tick = SDL_GetTicks();
            if (current_tick > tick + 200)
            {
                HP--;
            }
            tick = current_tick;
        }
    }
}

bool SkeletonEnemies::LoadHPFromFile(std::string path, SDL_Renderer* screen)
{
    SDL_DestroyTexture(my_HP);
    my_HP = NULL;
    
    //final texture
    SDL_Texture* FinalTexture = NULL;

    //load image from path
    SDL_Surface* LoadedSurface = IMG_Load(path.c_str());

    if (LoadedSurface == NULL)
    {
        std::cout << "failed to load image from path \n IMG Error:" << IMG_GetError();
    }
    else
    {

        //color key
        SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        //create texture from surface
        FinalTexture = SDL_CreateTextureFromSurface(screen, LoadedSurface);
        if (FinalTexture == NULL)
        {
            std::cout << "failed to create texture from surface \n SDL Error:" << SDL_GetError();
        }
        else
        {
            my_HP_rect.w = LoadedSurface->w;
            my_HP_rect.h = LoadedSurface->h;
        }

        //get rid from Loaded Texture
        SDL_FreeSurface(LoadedSurface);
    }

    my_HP= FinalTexture;
    return my_HP != NULL;
}

void SkeletonEnemies::HPRender(SDL_Renderer* screen, int x, int y, SDL_Rect* Clip, double angle, SDL_Point* Center, SDL_RendererFlip flip)
{
    // setting render space and update to the screen
    SDL_Rect renderQuad{ x, y, my_HP_rect.w, my_HP_rect.h };
    if (Clip != NULL)
    {
        renderQuad.w = Clip->w;
        renderQuad.h = Clip->h;
    }
    SDL_RenderCopyEx(screen, my_HP, Clip, &renderQuad, angle, Center, flip);
}