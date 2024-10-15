#include "AnimationUtils.h"

bool AnimationUtils::loadSpriteFrameCache(std::string path, std::string fileName)
{
    if (!FileUtils::getInstance()->isFileExist(path + fileName + ".plist")) {
        cocos2d::log((path + fileName + ".plist").c_str());
        return false;
    }

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile(path + fileName + ".plist");
    return true;
}

std::pair<Animation*, int> AnimationUtils::createAnimation(std::string animName, float duration)
{
    std::pair<Animation*, int> result;

    Vector<SpriteFrame*> frames;
    char str[100] = { 0 };

    int count = 1;
    while (true)
    {
        sprintf(str, "./%s (%d)", animName.c_str(), count);
        log(str);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        if (frame == nullptr) {
            break;
        }
        else {
            frames.pushBack(frame);
            count++;
        }
    }

    Animation* anim = Animation::createWithSpriteFrames(frames, duration / (float)count);
    result.first = anim;
    result.second = count;
    return result;
}
