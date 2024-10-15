#include "SplashScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

bool SplashScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto MainMenu1 = Sprite::create("Map/LocationPortraits/MainMenu1.png");
    MainMenu1->setPosition(visibleSize.width / 1.5, visibleSize.height / 2);
    MainMenu1->setContentSize(visibleSize);
    this->addChild(MainMenu1, 0);

    auto MainMenuVignette = Sprite::create("UI/MainMenuVignette.png");
    MainMenuVignette->setPosition(visibleSize.width / 4.5, visibleSize.height / 2);
    MainMenuVignette->setScale(0.3);
    this->addChild(MainMenuVignette, 1);

    auto labelSystemFont = Label::createWithSystemFont("LOADING...", "Roboto-Thin", 48);
    labelSystemFont->setPosition(Vec2(visibleSize / 2));
    this->addChild(labelSystemFont, 5);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::goToMainMenu), 1.5f);

    return true;
}

void SplashScene::goToMainMenu(float dt)
{
    auto scene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
}