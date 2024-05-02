#include "MouseObject.h"
MouseObject::MouseObject()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    width_frame_=0;
    height_frame_=0;
    status_=-1;
    input_type_.left_ =0;
    input_type_.right_=0;
    input_type_.down_=0;
    input_type_.up_=0;

}
MouseObject::~MouseObject()
{

}
bool MouseObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret =BaseObject::LoadImg(path, screen);
    if(ret==true)
    {
        width_frame_ = rect_.w/4;
        height_frame_ = rect_.h;
    }
    return ret;
}
void MouseObject::set_clips()
{
    if(width_frame_>0 && height_frame_ >0)
    {
        frame_clip_[0].x=0;
        frame_clip_[0].y=0;
        frame_clip_[0].w= width_frame_;
        frame_clip_[0].h= height_frame_;

        frame_clip_[1].x=width_frame_;
        frame_clip_[1].y=0;
        frame_clip_[1].w= width_frame_;
        frame_clip_[1].h= height_frame_;


        frame_clip_[2].x=2*width_frame_;
        frame_clip_[2].y=0;
        frame_clip_[2].w= width_frame_;
        frame_clip_[2].h= height_frame_;

        frame_clip_[3].x=3*width_frame_;
        frame_clip_[3].y=0;
        frame_clip_[3].w= width_frame_;
        frame_clip_[3].h= height_frame_;

    }
}
void MouseObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type_.right_=1;
                input_type_.left_=0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type_.left_=1;
                input_type_.right_=0;
            }
            break;
        case SDLK_UP:
            {
                // Xử lý hành động đi lên ở đây
                input_type_.up_ = 1;
            }
            break;
        case SDLK_DOWN:
            {
                // Xử lý hành động đi xuống ở đây
                input_type_.down_ = 1;
            }
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type_.right_=0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type_.left_=0;
            }
            break;
        case SDLK_UP:
            {
                input_type_.up_ = 0;
            }
            break;
        case SDLK_DOWN:
            {
                input_type_.down_ = 0;
            }
            break;
        }
    }
}
void MouseObject::Show(SDL_Renderer* des)
{
    // Load the appropriate image based on the direction of movement
    if (status_ == WALK_LEFT)
    {
        LoadImg("C:\\Users\\Admin\\Desktop\\img\\mousedownleft.png", des);
    }
    else if (status_ == WALK_RIGHT)
    {
        LoadImg("C:\\Users\\Admin\\Desktop\\img\\mousedownright.png", des);
    }

    // Update horizontal position based on left or right movement
    if (input_type_.left_ == 1)
    {
        x_pos_ -= 0.95; // Move left
    }
    else if (input_type_.right_ == 1)
    {
        x_pos_ += 0.95; // Move right
    }

    // Update the frame for animation
    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if (frame_ >= 4)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_;
    rect_.y = y_pos_;

    // Load the appropriate image for upward or downward movement
    if (input_type_.up_ == 1)
    {
        LoadImg("C:\\Users\\Admin\\Desktop\\img\\mouseup.png", des);
        y_pos_ -= 0.95; // Move up
    }
    else if (input_type_.down_ == 1)
    {
        LoadImg("C:\\Users\\Admin\\Desktop\\img\\mousedown.png", des);
        y_pos_ += 0.95; // Move down
    }

    // Select frame clip based on the direction of movement
    SDL_Rect* current_clip;
    if (input_type_.up_ == 1 || input_type_.down_ == 1)
    {
        current_clip = &frame_clip_[frame_];
    }
    else
    {
        current_clip = &frame_clip_[frame_ % 4]; // Use horizontal frame clips for left/right movement
    }

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}
