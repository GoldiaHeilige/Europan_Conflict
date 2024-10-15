#include "MainMenuScene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

int _mainMenuAudio = -1;

MainMenuScene* MainMenuScene::create()
{
    auto newObject = new MainMenuScene();
    if (newObject != nullptr && newObject->init()) {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /**********
    *
    *  FIRST GAME LABEL 
    * 
    ***********/

    auto menuNode1 = Sprite::create("UI/InventoryUIAtlas.png", Rect(1000, 690, 280, 250));
    menuNode1->setPosition(140, 620);
    menuNode1->setScale(0.45);
    this->addChild(menuNode1, 10);

    auto menuNodeShadow1 = Sprite::create("UI/InventoryUIAtlas.png", Rect(200, 1050, 500, 180));
    menuNodeShadow1->setPosition(400, 580);
    menuNodeShadow1->setScale(0.8);
    this->addChild(menuNodeShadow1, 9);

    auto menuCampaign = Label::createWithSystemFont("CAMPAIGN", "Roboto-Black", 20);
    menuCampaign->setPosition(Vec2(visibleSize / 2));
    menuCampaign->setTextColor(Color4B::BLACK);
    menuCampaign->setPosition(255, 640);
    this->addChild(menuCampaign, 15);

    auto startGameLabel = Label::createWithTTF("START GAME", "fonts/Roboto-Medium.ttf", 18);
    startGameLabel->setTextColor(Color4B::GREEN);
    auto startGameButton = MenuItemLabel::create(startGameLabel, CC_CALLBACK_1(MainMenuScene::switchToGameScene, this));
    startGameButton->setPosition(255, 610);
    auto startLabel = Menu::create(startGameButton, nullptr);
    startLabel->setPosition(Vec2::ZERO);
    this->addChild(startLabel, 15);

    /**********
    * 
    *  SECOND GAME LABEL
    * 
    **********/

    auto menuNode2 = Sprite::create("UI/InventoryUIAtlas.png", Rect(755, 690, 280, 250));
    menuNode2->setPosition(120, 120);
    menuNode2->setScale(0.45);
    this->addChild(menuNode2, 10);

    auto menuNodeShadow2 = Sprite::create("UI/InventoryUIAtlas.png", Rect(200, 1050, 500, 180));
    menuNodeShadow2->setPosition(400, 360);
    menuNodeShadow2->setScale(0.8);
    this->addChild(menuNodeShadow2, 9);

    /**********
    * 
    *  THIRD GAME LABEL
    * 
    **********/

    auto menuNode3 = Sprite::create("UI/InventoryUIAtlas.png", Rect(755, 690, 280, 250));
    menuNode3->setPosition(120, 120);
    menuNode3->setScale(0.45);
    this->addChild(menuNode3, 10);

    auto settingGameLabel = Label::createWithTTF("SETTINGS", "fonts/Roboto-Medium.ttf", 18);
    settingGameLabel->setTextColor(Color4B::GREEN);
    this->addChild(settingGameLabel, 15);

    auto quitGameLabel = Label::createWithTTF("QUIT", "fonts/Roboto-Medium.ttf", 18);
    quitGameLabel->setTextColor(Color4B::GREEN);
    auto quitGameButton = MenuItemLabel::create(quitGameLabel, CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    quitGameButton->setPosition(200, 110);
    auto quitLabel = Menu::create(quitGameButton, nullptr);
    quitLabel->setPosition(Vec2::ZERO);
    this->addChild(quitLabel, 15);

    /**********
    * 
    *  GAME TITLE AND OTHERS
    * 
    **********/

    _background = Sprite::create("Map/LocationPortraits/MainMenu1.png");
    _background->setPosition(visibleSize.width / 1.5, visibleSize.height / 2);
    _background->setContentSize(visibleSize);
    this->addChild(_background, 0);

    auto menuLeft = MoveBy::create(5.0f, Vec2(-70, 0)); 
    auto menuRight = MoveBy::create(5.0f, Vec2(70, 0)); 
    auto menuDelay = DelayTime::create(3);
    auto menuSequence = Sequence::create(menuDelay, menuLeft, menuDelay->clone(), menuRight, nullptr);

    auto menuRepeat = RepeatForever::create(menuSequence);
    _background->runAction(menuRepeat);

    auto MainMenuVignette = Sprite::create("UI/MainMenuVignette.png");
    MainMenuVignette->setPosition(visibleSize.width / 4.5, visibleSize.height / 2);
    MainMenuVignette->setScale(0.3);
    this->addChild(MainMenuVignette, 1);

    auto gameTitle = Sprite::create("UI/titleText.png", Rect(20, 720, 1300, 350));;
    gameTitle->setPosition(visibleSize.width / 1.41, 125);
    gameTitle->setScale(0.5);
    this->addChild(gameTitle, 20);

    return true;
}

void MainMenuScene::switchToGameScene(Ref* pSender)
{
    AudioEngine::play2d("Sounds/UI/UI_labelSelect.ogg");

    auto scene = IntroScene::createIntroScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
}

void MainMenuScene::onExit()
{
    Scene::onExit();
    AudioEngine::stop(_mainMenuAudio);
}

void MainMenuScene::onEnter()
{
    Scene::onEnter();

    // Restart the background music if it is not currently playing
    if (_mainMenuAudio == -1 || AudioEngine::getState(_mainMenuAudio) != AudioEngine::AudioState::PLAYING) {
        _mainMenuAudio = AudioEngine::play2d("Sounds/Music/Main Menu Music.ogg", true);
    }
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
