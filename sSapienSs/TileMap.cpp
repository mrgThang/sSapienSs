#include "CommonFunction.h"
#include "BaseTexture.h"
#include "TileMap.h"

GameMap::GameMap()
{
    game_map.start_x = 0;
    game_map.start_y = 0;
    memset(game_map.tile, 0, sizeof(game_map.tile));
    game_map.file_name = "";
}

GameMap::~GameMap()
{
    game_map.start_x = 0;
    game_map.start_y = 0;
    memset(game_map.tile, 0, sizeof(game_map.tile));
    game_map.file_name = "";
    status_mov = 0;
    for (int i = 1; i <= 10; ++i)
    {
        tile_map[i].free();
    }
}

void GameMap::StartAgain()
{
    game_map.start_x = 0;
    game_map.start_y = 0;
    memset(game_map.tile, 0, sizeof(game_map.tile));
    game_map.file_name = "";
    status_mov = 0;
    screen_start_x = 0;
    screen_mov = 0;
}

void GameMap::LoadMap(const char* path, const int MAX_MAP_X, const int MAX_MAP_Y)
{
    std::ifstream ifs(path);

    int dem = 0;

    for (int j = 0; j < MAX_MAP_Y; ++j)
    {
        for (int i = 0; i < MAX_MAP_X; ++i)
        {
            ifs >> game_map.tile[j][i];
        }
    }

    game_map.file_name = path;
}

bool GameMap::LoadTileTexture(SDL_Renderer* screen, std::string s, int s_size)
{

    for (int i = 1; i <= s_size; ++i)
    {
        std::string t = s + char(i+'0') + ".png";
        if (i >= 10)
        {
            t = s + '1' + char(i % 10 + '0') + ".png";
        }
        tile_map[i].LoadFromFile(t, screen);
    }
    
    return true;
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    
    memset(detect, 0, sizeof(detect));
    screen_start_x = game_map.start_x;

    int render_start_x = (game_map.start_x/TILE_SIZE) * TILE_SIZE;
    int render_start_y = (game_map.start_y/TILE_SIZE) * TILE_SIZE;

    int render_end_x = render_start_x + SCREEN_WIDTH + TILE_SIZE * (game_map.start_x % TILE_SIZE != 0);
    int render_end_y = render_start_y + SCREEN_HEIGHT + TILE_SIZE * (game_map.start_y % TILE_SIZE != 0);

    for (int i = render_start_y; i < render_end_y; i = i + TILE_SIZE)
    {
        for (int j = render_start_x; j < render_end_x; j = j + TILE_SIZE)
        {
            int x = game_map.tile[i/TILE_SIZE][j/TILE_SIZE];

            if (x > 0)
            {
                tile_map[x].Render(screen, j - game_map.start_x, i - game_map.start_y);
                int x1 = j - game_map.start_x;
                int y1 = i - game_map.start_y;
                for (int k = -7; k <= 7; ++k)
                {
                    if(y1 / FOOT_DISTANT + k >= 0)detect[y1 / FOOT_DISTANT + k][x1 / FOOT_DISTANT][1] = 1;
                    if(x1 / FOOT_DISTANT + k >= 0)detect[y1 / FOOT_DISTANT][x1 / FOOT_DISTANT + k][2] = 1;
                }
            }
        }
    }

}

void GameMap::HandleEvent(const int MAX_MAP_X)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    status_mov = 0;

    if (screen_mov < screen_last)
    MoveLeft(currentKeyStates);

    if(screen_mov > screen_last)
    MoveRight(currentKeyStates,MAX_MAP_X);

    screen_last = screen_mov;
}

void GameMap::MoveLeft(const Uint8* currentKeyStates)
{
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (game_map.start_x > 0)
        {
            status_mov = 1;
            game_map.start_x -= FOOT_DISTANT;
        }
    }
}

void GameMap::MoveRight(const Uint8* currentKeyStates, const int MAX_MAP_X)
{
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (game_map.start_x < MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH)
        {
            game_map.start_x += FOOT_DISTANT;
            status_mov = 2;
        }
    }
}