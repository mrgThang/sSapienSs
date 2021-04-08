#include "CommonFunction.h";
#include "Hero.h";

bool CheckCollision(SDL_Rect rect, std::string s)
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

    if (s == "up")
    {
        int x = rect.x / FOOT_DISTANT;
        int y = (rect.y - TILE_SIZE) / FOOT_DISTANT;
        if (detect[y][x][2] == 1)return false;
        return true;
    }

    if (s == "down")
    {
        int x = rect.x / FOOT_DISTANT;
        int y = (rect.y + rect.h) / FOOT_DISTANT;
        if (detect[y][x][2] == 1)return false;
        return true;
    }
}

Hero::Hero()
{
    my_texture = NULL;
    my_rect.x = 0;
    my_rect.y = 0;
    my_rect.w = 64;
    my_rect.h = 64;
    status2 = 1;                                                                                                          
    status = 1;
    dem = 0;
    dk = 0;
    hp = 3;
    dem_immortal = 0;
    immortal_status = 0;
    tick = 0;
}

Hero::~Hero()
{
    free();
}

void Hero::MoveLeft(const Uint8* currentKeyStates)
{
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        bool x = CheckCollision(my_rect, "left");
        if (my_rect.x > 0 && x > 0)
        {
            if (screen_mov > 0 && my_rect.x == SCREEN_WIDTH / 2 - FOOT_DISTANT)screen_mov -= FOOT_DISTANT;
            else my_rect.x -= FOOT_DISTANT;                                        
        }
        status2 = 2;
        dem++;
        if (dem >= 8)status--, dem = 0;
        if (status < 1 || status > 2)status = 2;
        dk = 1;
    }
}

void Hero::MoveRight(const Uint8* currentKeyStates, const int max_map_move)
{
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        bool x = CheckCollision(my_rect, "right");
        if (my_rect.x < SCREEN_WIDTH  - 64 && x > 0)
        {
            if(screen_mov < max_map_move && my_rect.x == SCREEN_WIDTH / 2 - FOOT_DISTANT)screen_mov += FOOT_DISTANT;
            else my_rect.x += FOOT_DISTANT;
        }
        status2 = 1;
        dem++;
        if(dem >= 8)status++,dem = 0;
        if (status < 2 || status > 3)status = 2;
        dk = 1;
    }
}

void Hero::MoveUp(const Uint8* currentKeyStates, int& hero_jump_condition, int& hero_jump_max)
{
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        if (hero_jump_condition == 0)
        {
            hero_jump_condition = 1;
            hero_jump_max = max(0, my_rect.y - 20 * FOOT_DISTANT);
        }
    }
    if (hero_jump_condition == 1 && my_rect.y > hero_jump_max)
    {
        if (CheckCollision(my_rect, "up") == 0)hero_jump_condition = 2;
        else my_rect.y -= FOOT_DISTANT;
    }
    if (hero_jump_condition == 1 && my_rect.y == hero_jump_max)
    {
        hero_jump_condition = 2;
    }
}

void Hero::MoveDown(int& hero_jump_condition)
{
    if (hero_jump_condition == 2)
    {
        if (CheckCollision(my_rect, "down") == 1)my_rect.y += FOOT_DISTANT;
        else hero_jump_condition = 0;
    }
    else if (hero_jump_condition == 0)
    {
        if (CheckCollision(my_rect, "down") == 1)my_rect.y += FOOT_DISTANT;
    }
}

void Hero::HandleEvent(int& hero_jump_condition, int &hero_jump_max, const int max_map_move)
{
    //get current ket state
    if (my_rect.y > 13 * TILE_SIZE || hp <= 0)
    {
        free();
    }
    else
    {
        my_rect.w = 64;
        my_rect.h = 64;

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        MoveLeft(currentKeyStates);

        MoveRight(currentKeyStates, max_map_move);

        MoveUp(currentKeyStates, hero_jump_condition, hero_jump_max);

        MoveDown(hero_jump_condition);

        if (dk == 0)
        {
            if (status2 == 1)
            {
                dem++;
                if (dem >= 12)
                {
                    status++;
                    dem = 0;
                }
                if (status < 1 || status > 2)status = 1;
            }
            else
            {
                dem++;
                if (dem >= 12)
                {
                    status--;
                    dem = 0;
                }
                if (status < 2 || status > 3)status = 3;
            }
        }

        dk = 0;
    }
}

void Hero::Motion(SDL_Renderer* screen)
{    
    SDL_Rect* clipz = new SDL_Rect;
    clipz->h = 64;
    clipz->w = 64;
    clipz->x = (status - 1) * 64;
    clipz->y = (status2 - 1)*64;
    hero_start_x = my_rect.x;
    hero_start_y = my_rect.y;

    if (immortal_status == 1)
    {
        dem_immortal++;
        if((dem_immortal / 12)%2 == 0)Render(screen, my_rect.x, my_rect.y, clipz);
        if (SDL_GetTicks() > tick + 4900)
        {
            dem_immortal = 0;
            immortal_status = 0;
            tick = 0;
        }
    }
    else Render(screen, my_rect.x, my_rect.y, clipz);
}

int Hero::GetStatus2()
{
    return status2;
}