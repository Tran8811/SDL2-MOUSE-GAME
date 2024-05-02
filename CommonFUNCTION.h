#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED
#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window =NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;

const int COLOR_KEY_R=167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B =180;
typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;

};

#endif // COMMONFUNCTION_H_INCLUDED
