#include "IntroScene.h"

Scene* IntroScene::createIntroScene()
{
    return IntroScene::create();
}

bool IntroScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _physicsWorld->setGravity(Vec2::ZERO);
    /*_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);*/

    _map = TMXTiledMap::create("Chapter_Intro.tmx");
    this->addChild(_map);

    auto charInfo = new EntityInfo();
    charInfo->_type = "Character";
    charInfo->_name = "Hero";

    auto enemy1Info = new EntityInfo();
    enemy1Info->_type = "Enemy";
    enemy1Info->_name = "Enemy4_Rifle";

    auto stat2 = new EntityStat();
    stat2->_spd = 10;
    stat2->_hp = 100;
    stat2->_atk = 50;

    auto heroStat = new EntityStat();
    heroStat->_spd = 3;
    heroStat->_hp = 100;
    WeaponManager* weaponManager = WeaponManager::getInstance();

    if (heroStat->_weaponStats) {
        delete heroStat->_weaponStats; 
    }
    heroStat->_weaponStats = weaponManager->getCurrentWeaponStats();

    // Ensure ammo stats are synchronized with the weapon manager
    heroStat->_currentAmmo = weaponManager->getCurrentWeaponStats()->_currentAmmo;
    heroStat->_totalAmmo = weaponManager->getCurrentWeaponStats()->_totalAmmo;
    heroStat->_currentMag = weaponManager->getCurrentWeaponStats()->_currentMag;
    CCLOG("EntityStat Ammo: %f, WeaponManager Ammo: %f", heroStat->_currentAmmo, WeaponManager::getInstance()->getCurrentWeaponStats()->_currentAmmo);

    auto enemy2 = Enemy::create(enemy1Info, stat2);
    auto hero = Character::create(charInfo, heroStat);

    _character = Character::create(charInfo, heroStat);
    _character->setPosition(visibleSize / 2);
    _character->setName("Hero");
    this->addChild(_character);
    this->addChild(KeyboardInput::getInstance());

    auto uiManager = UIManager::getInstance();
    uiManager->setCharacterNode(_character); 
    this->addChild(uiManager);

    enemy2->setPosition(visibleSize / 2);
    enemy2->setName("Enemy Rifle Soldier");
    this->addChild(enemy2);

    auto followPlayer = cocos2d::Follow::create(_character, Rect(0, 0, _map->getMapSize().width * _map->getTileSize().width, _map->getMapSize().height * _map->getTileSize().height));
    this->runAction(followPlayer);

    auto mouseEvent = EventListenerMouse::create();
    mouseEvent->onMouseMove = CC_CALLBACK_1(IntroScene::onMouseMove, this);
    mouseEvent->onMouseDown = CC_CALLBACK_1(IntroScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);

    // Events



    // Spawn Objects
    SpawnObjects spawnObjects(this);
    spawnObjects.spawnCarsFromTiled(_map);
    spawnObjects.spawn_Building_Industrial_Normal(_map);
    spawnObjects.spawn_Building_Industrial_Broken(_map);
    spawnObjects.spawn_Industrial_Elements_Broken(_map);
    spawnObjects.spawnFiresFromTiled(_map);

    this->scheduleUpdate();
    return true;
}

void IntroScene::update(float dt)
{
    Vec2 worldMousePos = this->convertToNodeSpace(_currentMousePos);
    _character->move(KeyboardInput::getInstance()->getDirection());

    if (worldMousePos != Vec2::ZERO) {
        Vec2 direction = worldMousePos - _character->getPosition();
        float angle = atan2(direction.y, direction.x);
        _character->rotateBody(angle);
    }
}

Sprite* IntroScene::addSpriteAtPosition(Vec2 position, int zOrder)
{
    return nullptr;
}

void IntroScene::onMouseMove(Event* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    _currentMousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

void IntroScene::onMouseDown(Event* event) {
    auto mouseEvent = static_cast<EventMouse*>(event);
    Vec2 mousePos = this->convertToNodeSpace(Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
    Vec2 direction = mousePos - _character->getPosition();
    direction.normalize();

    _character->shoot(direction);
}

//void IntroScene::onMouseDown(Event* event)
//{
//    auto mouseEvent = static_cast<EventMouse*>(event);
//
//    Vec2 mousePos = this->convertToNodeSpace(Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
//    Vec2 direction = mousePos - _character->getPosition();
//
//    direction.normalize();
//    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
//
//    Vec2 spawnOffset = direction * 10;
//    Vec2 spawnPosition = _character->getPosition() + spawnOffset;
//
//    Bullet* bullet = Bullet::create(_character, 500.0f, "pistol1");
//    bullet->setPosition(spawnPosition);
//    bullet->setName("Pistol Bullet");
//    bullet->setRotation(-angle + 90);
//
//    this->addChild(bullet);
//    bullet->fire(direction);
//}
