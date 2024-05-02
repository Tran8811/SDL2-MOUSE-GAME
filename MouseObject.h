#ifndef MOUSEOBJECT_H_INCLUDED
#define MOUSEOBJECT_H_INCLUDED

#include "CommonFUNCTION.h"
#include "BaseObject.h"

class MouseObject : public BaseObject
{
public:
    MouseObject();
    ~MouseObject();
    enum Walktype
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[4];
    Input input_type_;
    int frame_;
    int status_;
};

#endif // MOUSEOBJECT_H_INCLUDED
