#include "CommonFunction.h"
#include "Spider.h"

Spider::Spider()
{
    BaseTexture();
    my_rect.w = 64;
    my_rect.h = 64*5;
    status = 1;
    dk = "down";
    dem = 0;
    my_tooth_status = 1;
}

Spider::~Spider()
{
    free();
}

void Spider::SetPosition(int x, int y)
{
    my_rect.x = x;
    my_rect.y = y;
}

void Spider::HandldeEvent(SDL_Renderer* screen, int status_mov)
{
    if (status_mov == 1)
    {
        my_rect.x += FOOT_DISTANT;
    }
    if (status_mov == 2)
    {
        my_rect.x -= FOOT_DISTANT;
    }

    //stay motion
    
    if (dk == "down")
    {
            
        dem++;
        if (dem >= speed)
        {
            status++;
            if (status >= 6)status = 4, dk = "up";
            dem = 0;
        }
    }
    if (dk == "up")
    {
        dem++;
        if (dem >= speed)
        {
            status--;
            if (status <= 0)status = 1, dk = "down";
            dem = 0;
        }
    }

    //attack motion
    if (hero_start_x >= my_rect.x - 32 && hero_start_x <= my_rect.x + 32)
    {
        if ((status == 1 || status == 2) && hero_start_y == my_rect.y + 64)
        {
            if ("attack" != dk)
            {
                lastdk = dk;
                dk = "attack";
                dem = 0;
                my_tooth_status = 1;
            }
        }
        else if (status == 3 && hero_start_y == my_rect.y + 128)
        {
            if ("attack" != dk)
            {
                lastdk = dk;
                dk = "attack";
                dem = 0;
                my_tooth_status = 1;
            }
        }
        else if ((status == 4 || status == 5) && hero_start_y == my_rect.y + 128 + 64)
        {
            if ("attack" != dk)
            {
                lastdk = dk;
                dk = "attack";
                dem = 0;
                my_tooth_status = 1;
            }
        }
    }
    else
    {
        if (dk == "attack" && my_tooth_status == 3)
        {
            dk = lastdk;
        }
    }
    
    if (dk == "attack")
    {
        Attack(screen);
    }

    Motion(screen);
}

void Spider::Motion(SDL_Renderer* screen)
{
    SDL_Rect* zclip = new SDL_Rect;
    zclip->x = 64 * (status - 1);
    zclip->y = 0;
    zclip->w = 64;
    zclip->h = 64*5;
    Render(screen, my_rect.x, my_rect.y, zclip);
}

void Spider::Attack(SDL_Renderer* screen)
{
    dem++;
    if (dem >= 20)
    {
        my_tooth_status++;
        if (my_tooth_status >= 4)my_tooth_status = 1;
        if (my_tooth_status == 3)
        {
            tick_immortal = SDL_GetTicks();
            if (tick_immortal > last_tick_immortal + 5000)
            {
                MYHP--;
                last_tick_immortal = tick_immortal;
            }
        }
        dem = 0;
    }

    SDL_Rect* tooth_clip = new SDL_Rect;
    tooth_clip->x = 64 * (my_tooth_status - 1);
    tooth_clip->y = 0;
    tooth_clip->w = 64;
    tooth_clip->h = 64;
    ToothRender(screen, hero_start_x, hero_start_y, tooth_clip);
}

bool Spider::LoadToothFromFile(std::string path, SDL_Renderer* screen)
{
    SDL_DestroyTexture(tooth);
    tooth = NULL;

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
            my_tooth_rect.w = LoadedSurface->w;
            my_tooth_rect.h = LoadedSurface->h;
        }

        //get rid from Loaded Texture
        SDL_FreeSurface(LoadedSurface);
    }

    tooth = FinalTexture;
    return tooth != NULL;
}

void Spider::ToothRender(SDL_Renderer* screen, int x, int y, SDL_Rect* Clip, double angle, SDL_Point* Center, SDL_RendererFlip flip)
{
    // setting render space and update to the screen
    SDL_Rect renderQuad{ x, y, my_tooth_rect.w, my_tooth_rect.h };
    if (Clip != NULL)
    {
        renderQuad.w = Clip->w;
        renderQuad.h = Clip->h;
    }
    SDL_RenderCopyEx(screen, tooth, Clip, &renderQuad, angle, Center, flip);
}