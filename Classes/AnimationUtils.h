#ifndef __ANIMATION_UTILS_H__
#define __ANIMATION_UTILS_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtils
{
public:
    static bool loadSpriteFrameCache(std::string path, std::string fileName);
    static std::pair<Animation*, int> createAnimation(std::string animName, float duration);
};

#endif // !__ANIMATION_UTILS_H__
