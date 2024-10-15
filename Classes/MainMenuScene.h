#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class MainMenuScene : public Scene
{
public:
    static MainMenuScene* create();

    virtual bool init();
private:
    Sprite* _background;

    void switchToGameScene(Ref* sender);
    void onExit();
    void onEnter();
    void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif // __MAIN_MENU_SCENE_H__