#ifndef __ANIM_DIRECTIONAL_H__
#define __ANIM_DIRECTIONAL_H__

#include "Anim_Base.hpp"
#include "Directions.hpp"

class Anim_Directional : public Anim_Base
{
    void FrameStep();
    void CropSprite();
    void ReadIn(std::stringstream& l_stream);
};


#endif // __ANIM_DIRECTIONAL_H__