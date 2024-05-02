#include "CommonFUNCTION.h"
#include "BaseObject.h"
#include "MouseObject.h"
  BaseObject g_background;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_window = SDL_CreateWindow("Game Cpp SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window==NULL)
    {
        success=false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen ==NULL)
            success= false;
        else
        {
            SDL_SetRenderDrawColor(g_screen,255,255,255,255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success= false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret = g_background.LoadImg("C:\\Users\\Admin\\Desktop\\img\\background.png", g_screen);
    if(ret==false)
        return false;
    return true;
}
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen= NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{
    if(InitData()==false)
        return -1;
    if(LoadBackground()==false)
        return -1;

        MouseObject p_player;
        p_player.LoadImg("C:\\Users\\Admin\\Desktop\\img\\mousedownright.png",g_screen);
        p_player.set_clips();
        p_player.HandleInputAction(g_event, g_screen); // Xử lý sự kiện đầu vào
        p_player.Show(g_screen); // Hiển thị đối tượng chuột
        SDL_RenderPresent(g_screen);

    bool isquit=false;
    while(!isquit)
    {
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type==SDL_QUIT)
            {
                isquit=true;
            }
            p_player.HandleInputAction(g_event,g_screen);
        }
        SDL_SetRenderDrawColor(g_screen,255,255,255,255);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,NULL);
        p_player.Show(g_screen);
        SDL_RenderPresent(g_screen);

    }
    close();
    return 0;
}
